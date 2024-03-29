/*!
* \file Player.cpp
* \brief Player class implementation
* \author smbct
* \date 08.10.2016
*/

#include "Player.hpp"
#include "EntityManager.hpp"
#include "Bullet.hpp"
#include "Utils.hpp"

#include <iostream>

using namespace sf;
using namespace std;

/*----------------------------------------------------------------------------*/
Player::Player(EntityManager& entityManager, sf::Window& input) :
Entity(entityManager, entityManager.getTextureManager().getTexture("Art/Player.png"), 10.),
_input(input),
_speed(600.),
_root2(sqrt(2.)),
_fire(false)
{
    _type = Entity::Player;
}

/*----------------------------------------------------------------------------*/
void Player::update(double elapsedTime) {

    // double angle = getRotation();

    Vector2f dir(0., 0.);

    if(Keyboard::isKeyPressed(Keyboard::Z)) {
        dir.y = -1.;
    } else if(Keyboard::isKeyPressed(Keyboard::S)) {
        dir.y = 1.;
    }
    if(Keyboard::isKeyPressed(Keyboard::Q)) {
        dir.x = -1.;
    } else if(Keyboard::isKeyPressed(Keyboard::D)) {
        dir.x = 1.;
    }

    double length = sqrt(dir.x*dir.x+dir.y*dir.y);
    if(abs(dir.x) >= 0.5) {
        dir.x *= _speed/length;
    }
    if(abs(dir.y) >= 0.5) {
        dir.y *= _speed/length;
    }

    _velocity += dir;

    /* update orientation */
    if(dir.x*dir.x + dir.y*dir.y > 1e-4) {
        double angle = atan2(dir.y,dir.x);
        angle *= 180. / 3.1415; /* TODO : pi constant */
        setRotation(angle);
    }

    /* update position */
    Entity::update(elapsedTime);

    /* create particles if it's moving */
    if(Utils::lengthSq(_velocity) > 0.1) {
        createExhaustFire();
    }

    /* reset the velocity */
    _velocity = Vector2f(0., 0.);

    /* manage firing */
    if(Mouse::isButtonPressed(Mouse::Left)) {
        if(!_fire) {
            _fire = true;
            createBullets();
            _clock.restart();
        } else {
            if(_clock.getElapsedTime().asSeconds() > 0.1) {
                createBullets();
                _clock.restart();
            }
        }
    } else if(_fire) {
        _fire = false;
    }

}

/*----------------------------------------------------------------------------*/
void Player::collideWith(const Entity& entity) {
    if(entity.type() != Entity::Bullet) {
        // _alive = false;
        createExplosion();
        _entityManager.getGrid().applyDirectedForce(sf::Vector3f(0,0,2000), sf::Vector3f(getPosition().x, getPosition().y, 0.), 50);
    }
}

/*----------------------------------------------------------------------------*/
void Player::createBullets() {

    Vector2f pos = getPosition();
    Vector2f dir = static_cast<Vector2f>(Mouse::getPosition(_input));
    dir -= pos;

    /* normalize the vector */
    double len = sqrt(dir.x*dir.x + dir.y*dir.y);
    dir.x /= len;
    dir.y /= len;

    Vector2f center(pos);
    center.x += dir.x * 50.;
    center.y += dir.y * 50.;

    /* orthogonal vector, used to create a gap between the bullets */
    Vector2f ortho(dir.y, -dir.x);
    ortho.x *= 10.;
    ortho.y *= 10.;

    Vector2f posA(center - ortho);
    Vector2f posB(center + ortho);

    /* bullets creation */
    class Bullet* bulletA = new class Bullet(_entityManager, posA, dir);
    class Bullet* bulletB = new class Bullet(_entityManager, posB, dir);

    _entityManager.addEntity(bulletA);
    _entityManager.addEntity(bulletB);
}

/*----------------------------------------------------------------------------*/
void Player::createExplosion() {

    Color yellow(0.8*255, 0.8*255, 0.4*255);

    for (int i = 0; i < 1200; i++)
    {
        float speed = 450. * (1. - 1. / Utils::randRange(1., 10.));
        Color color = Utils::colorLerp(Color::White, yellow, Utils::randRange(0., 1.));
        ParticleState state;

        state.velocity = Utils::vectorFromLengthAngle(speed, Utils::randRange(-Utils::PI(), Utils::PI()));
        state.type = ParticleState::None;
        state.lengthMultiplier = 1.;

        const Texture& texture = _entityManager.getTextureManager().getTexture("Art/Laser.png");
        Vector2f scale(1.5, 1.5);

        _entityManager.getParticleManager().createParticle(texture, getPosition(), color, 1.3, scale, state);
    }

}

/*----------------------------------------------------------------------------*/
void Player::createExhaustFire() {

        ParticleState state;
        state.type = ParticleState::Enemy;
        state.lengthMultiplier = 1.;

        double orientation = Utils::vectorToAngle(_velocity);
        double t = _particleClock.getElapsedTime().asSeconds();

        Vector2f baseVel = _velocity;
        double length = Utils::length(_velocity);
        baseVel.x *= -100. / length;
        baseVel.y *= -100. / length;

        Vector2f perpVel(baseVel.y, -baseVel.x);
        double coef = 0.6 * sin(t*10.);
        perpVel.x *= coef;
        perpVel.y *= coef;

        const double alpha = 0.7;
        Color sideColor(200.*alpha, 38.*alpha, 9.*alpha), midColor(255.*alpha, 187.*alpha, 30.*alpha);

        Vector2f pos = getPosition() - Utils::vectorFromLengthAngle(25., orientation);

        const Texture& line = _entityManager.getTextureManager().getTexture("Art/Laser.png");
        const Texture& glow = _entityManager.getTextureManager().getTexture("Art/Glow.png");

        /* middle particle system */
        Color col(255.*alpha, 255.*alpha, 255.*alpha);
        Vector2f velMid = baseVel + Vector2f(Utils::randRange(0., 10.), Utils::randRange(0., 10.));
        state.velocity = velMid;
        _entityManager.getParticleManager().createParticle(line, pos, col, 0.8, Vector2f(0.5, 1.), state);
        _entityManager.getParticleManager().createParticle(glow, pos, midColor, 0.8, Vector2f(0.5, 1.), state);

        /* side particle system */
        Vector2f vel1 = baseVel + perpVel + Vector2f(Utils::randRange(0., 3.), Utils::randRange(0., 3.));
        Vector2f vel2 = baseVel - perpVel + Vector2f(Utils::randRange(0., 3.), Utils::randRange(0., 3.));
        state.velocity = vel1;
        _entityManager.getParticleManager().createParticle(line, pos, col, 0.8, Vector2f(0.5, 1.), state);
        _entityManager.getParticleManager().createParticle(glow, pos, sideColor, 0.8, Vector2f(0.5, 1.), state);
        state.velocity = vel2;
        _entityManager.getParticleManager().createParticle(line, pos, col, 0.8, Vector2f(0.5, 1.), state);
        _entityManager.getParticleManager().createParticle(glow, pos, sideColor, 0.8, Vector2f(0.5, 1.), state);

}
