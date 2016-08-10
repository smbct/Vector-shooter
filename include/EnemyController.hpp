/*!
* \file EnemyController.hpp
* \brief class definitions for enemy control
* \author Samuel Buchet
* \date 08.10.2016
*/

#ifndef ENEMY_CONTROLLER_HPP
#define ENEMY_CONTROLLER_HPP

#include "Entity.hpp"

/*!
 * \class SeekeerController
 * \brief seeker controller
 */
class SeekerController {

    public:
        SeekerController(Entity* seeker);

    private:
        Entity* _seeker;

};

#endif /* ENEMY_CONTROLLER_HPP */
