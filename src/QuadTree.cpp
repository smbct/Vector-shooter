#include "QuadTree.hpp"

#include <iostream>
#include <stack>
#include <list>

using namespace std;

/*----------------------------------------------------------------------------*/
QuadTree::QuadTree(sf::Vector2i size, int nLevels): _nLevels(nLevels), _size(size) {

  // build all the levels
  build();

}

/*----------------------------------------------------------------------------*/
QuadTree::~QuadTree() {
  for(int levelInd = 0; levelInd < _nLevels; levelInd ++) {
    for(Node* node: _nodes[levelInd]) {
      delete node;
    }
  }
}

/*----------------------------------------------------------------------------*/
void QuadTree::build() {

  _nodes.resize(_nLevels);

  // dimensions
  _dim.resize(_nLevels);
  _dim[0] = sf::Vector2i(_size.x, _size.y);
  for(int levelInd = 1; levelInd < _nLevels; levelInd ++) {
    _dim[levelInd] = sf::Vector2i(_dim[levelInd-1].x/2, _dim[levelInd-1].y/2);
  }

  // first level
  Node node;
  node.corner = sf::Vector2i(0,0);
  node.prec = nullptr;
  node.level = 0;
  node.leaf = true;

  _nodes[0].push_back(new Node(node));

  // following levels
  for(int levelInd = 1; levelInd < _nLevels; levelInd ++) {
    // create 4 successors for each node of the previous level
    for(Node *node: _nodes[levelInd-1]) {
      for(int i = 0; i <= 1; i ++) {
        for(int j = 0; j <= 1; j ++) {
          Node suc;
          suc.prec = node;
          suc.corner = sf::Vector2i(node->corner.x + i*_dim[levelInd].x, node->corner.y + j*_dim[levelInd].y);
          suc.level = levelInd;
          suc.leaf = true;
          _nodes[levelInd].push_back(new Node(suc));
          node->suc.push_back(_nodes[levelInd].back());
        }
      }
    }
  }


  // for(int levelInd = 0; levelInd < _nLevels; levelInd ++) {
  //   cout << "level " << levelInd << ": " << _dim[levelInd].x << " x " << _dim[levelInd].y << endl << endl;
  //   int nodeInd = 0;
  //   for(Node* node: _nodes[levelInd]) {
  //     cout << "node " << nodeInd << ", " << node->corner.x << ", " << node->corner.y << endl;
  //     nodeInd ++;
  //   }
  //   cout << endl << endl;
  // }

}


/*----------------------------------------------------------------------------*/
void QuadTree::clear() {
  stack<Node*> toClear;
  toClear.push(_nodes[0][0]);
  while(!toClear.empty()) {
    Node* node = toClear.top();
    toClear.pop();
    node->entities.clear();
    if(!node->leaf) {
      node->leaf = true;
      for(Node* suc: node->suc) {
        toClear.push(suc);
      }
    }
  }
}


/*----------------------------------------------------------------------------*/
void QuadTree::insert(Entity* entity) {
  insertRec(entity, _nodes[0][0]);
}


/*----------------------------------------------------------------------------*/
void QuadTree::insertRec(Entity* entity, Node* node) {

  bool found = false;

  for(int sucInd = 0; sucInd < node->suc.size(); sucInd ++) { // look for a sub node to insert the entity
    Node* suc = node->suc[sucInd];
    if(Entity::insideRect(*entity, suc->corner, _dim[suc->level])) {
      found = true;
      node->leaf = false; // the node is not a leafe anymore
      insertRec(entity, suc);
    }
  }

  if(!found) {
    node->entities.push_back(entity);
  }

}

/*----------------------------------------------------------------------------*/
void QuadTree::performCollisions() {

  /* collect all the nodes having leaves */
  list<Node*> toProcess;

  stack<Node*> temp;
  temp.push(_nodes[0][0]);

  while(!temp.empty()) {
    Node* node = temp.top();
    toProcess.push_back(node);
    temp.pop();
    if(!node->leaf) {
      for(Node* suc: node->suc) {
        temp.push(suc);
      }
    }
  }

  /* perform the collison test for each entity of each node */
  for(Node* node: toProcess) {
      for(Entity* entity: node->entities) {

        if(entity->alive()) { // make sure this entity is still alive

          temp.push(node);

          while(!temp.empty()) {

            Node* node = temp.top();
            temp.pop();

            // test collisions for this node
            for(Entity* other: node->entities) {
              if(other != entity) {
                if(other->alive() && Entity::collision(*entity, *other)) {
                  entity->collideWith(*other);
                  other->collideWith(*entity);
                }
              }
            }

            // add the successors
            if(!node->leaf) {
              for(Node* suc: node->suc) {
                temp.push(suc);
              }
            }

          }

        }

      }
  }

}


/*----------------------------------------------------------------------------*/
void QuadTree::getFilledRects(vector<sf::IntRect>& rects) {
  getFilledRectsRec(_nodes[0][0], rects);
}

/*----------------------------------------------------------------------------*/
void QuadTree::getFilledRectsRec(Node* node, vector<sf::IntRect>& rects) {
  if(!node->entities.empty()) {
    rects.push_back(sf::IntRect(node->corner.x, node->corner.y, _dim[node->level].x, _dim[node->level].y));
  }
  for(Node* suc: node->suc) {
    getFilledRectsRec(suc, rects);
  }
}
