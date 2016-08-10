/*!
 * \file TextureManager.hpp
 * \brief class definitation for managing all graphical assets fo the game
 * \author Samuel Buchet
 * \date 08.09.2016
 */

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

/*!
 * \class TextureManager
 * \brief manage all the textures of the game
 */
class TextureManager {

    public:

        /*!
         * \brief constructor
         */
        TextureManager();

        /*!
         * \brief get a texture from a file
         * \return the texture
         */
        const sf::Texture& getTexture(std::string fileName);

        /*!
         * \brief destructor, free the textures
         */
        ~TextureManager();

    private:
        std::map<std::string, sf::Texture*> _textures;

};

#endif
