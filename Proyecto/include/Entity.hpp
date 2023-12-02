#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

class Entity
{
protected:
  unique_ptr<Shape> _shape;
  Vector2f _position;

public:
  Entity(unique_ptr<Shape> shp);
  virtual ~Entity() = default;

  virtual void update(double dt);
  virtual void render(RenderWindow &window) const = 0;

  const Vector2f getPosition() const;
  void setPosition(const Vector2f &pos);
  void move(const Vector2f &pos);
};

Entity::Entity(unique_ptr<Shape> shp) : _shape(std::move(shp)) {}

const Vector2f Entity::getPosition() const { return _position; }

void Entity::setPosition(const Vector2f &pos) { _position = pos; }

void Entity::move(const Vector2f &pos) { _position += pos; }

void Entity::update(double dt)
{
  _shape->setPosition(_position);
}
