#pragma once

#include <SFML/System.hpp>
#include "Entity.hpp"

class Player : public Entity
{
private:
    float _speed;

public:
    Player();
    void update(double dt) override;
    void render(sf::RenderWindow &window) const override;
};
#include "Player.hpp"

Player::Player() : _speed(200.0f), Entity(std::make_unique<sf::CircleShape>(25.f))
{
    _shape->setFillColor(sf::Color::Magenta);
    _shape->setOrigin(sf::Vector2f(25.f, 25.f));
}

void Player::update(double dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move(sf::Vector2f(0, -_speed * dt));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move(sf::Vector2f(0, _speed * dt));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move(sf::Vector2f(-_speed * dt, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(sf::Vector2f(_speed * dt, 0));
    }

    Entity::update(dt);
}

void Player::render(sf::RenderWindow &window) const
{
    window.draw(*_shape);
}
