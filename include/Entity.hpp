#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class Entity
{
protected:
    std::unique_ptr<sf::Shape> _shape;

public:
    Entity(std::unique_ptr<sf::Shape> shp);
    virtual ~Entity() = default;

    virtual void update(double dt);
    virtual void render(sf::RenderWindow &window) const = 0;

    const sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f &pos);
    void move(const sf::Vector2f &pos);
};
#include "Entity.hpp"

Entity::Entity(std::unique_ptr<sf::Shape> shp) : _shape(std::move(shp)) {}

const sf::Vector2f Entity::getPosition() const { return _shape->getPosition(); }

void Entity::setPosition(const sf::Vector2f &pos) { _shape->setPosition(pos); }

void Entity::move(const sf::Vector2f &pos) { _shape->move(pos); }

void Entity::update(double dt) {}

