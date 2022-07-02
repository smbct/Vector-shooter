/*!
* \file QuadTree.hpp
* \brief QuadTree class definition
* \author smbct
*/

#include <vector>
#include "Entity.hpp"

/*!
 * \brief spatial data structure to optimize collision detection
 */
class QuadTree {

  public:

    /*!
     * \brief definition of the nodes
     */
    class Node {
      public:
        sf::Vector2i corner; // upper left corner of the node
        std::vector<Entity*> entities; // entities contained inside the node
        std::vector<Node*> suc; // successors in the tree
        Node* prec; // predecessor in the tree
        int level; // level of the node
        bool leaf; // indicate if the node is a leaf, i.e. the direct/indirect successors contain no entites
    };


  public:

    /*!
     * \brief definition of the nodes
     */
    QuadTree(sf::Vector2i size, int nLevels);

    /*!
     * \brief destructor
     */
    ~QuadTree();

    /*!
     * \brief clear all the entities
     */
    void clear();

    /*!
     * \brief insert an entity in the quadtree
     */
    void insert(Entity* entity);

    /*!
     * \brief get the rects of nonempty nodes
     */
    void getFilledRects(std::vector<sf::IntRect>& rects);

    /*!
     * perform the collision test between the entities in the same branch of the tree
     */
    void performCollisions();

  private:

    void build();

    void insertRec(Entity* entity, Node* node);

    /*!
     * \brief get the rects of nonempty nodes
     */
    void getFilledRectsRec(Node* node, std::vector<sf::IntRect>& rects);


  private:

    int _nLevels;

    std::vector<std::vector<Node*>> _nodes; // nodes for each level

    std::vector<sf::Vector2i> _dim; // dimensions for each level

    sf::Vector2i _size; // size of the world

};
