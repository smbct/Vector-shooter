/*!
 * \file TextureManager.cpp
 * \brief implementation of TextureManager
 * \author Samuel Buchet
 * \date 08.09.2016
 */

#include "TextureManager.hpp"

using namespace std;
using namespace sf;

/*----------------------------------------------------------------------------*/
TextureManager::TextureManager() {

}

/*----------------------------------------------------------------------------*/
const Texture& TextureManager::getTexture(string fileName) {

    auto it = _textures.find(fileName);

    Texture* query;

    /* if the texture hasn't been loaded yet, its loaded */
    if(it == _textures.end()) {
        query = new Texture();
        query->loadFromFile(fileName);
        _textures.insert(pair<string, Texture*>(fileName, query));
    } else {
        query = _textures.at(fileName);
    }

    return *query;
}

/*----------------------------------------------------------------------------*/
TextureManager::~TextureManager() {

    for(auto it : _textures) {
        delete it.second;
    }

}
