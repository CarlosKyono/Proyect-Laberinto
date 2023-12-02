#pragma once

#include <Entity.hpp>
#include <SFML/Window/Keyboard.hpp>

class Player : public Entity
{
private:
  float _speed;

public:
  Player();
  void update(double dt) override;
  void render(RenderWindow &window) const override;
};

Player::Player() : _speed(200.0f), Entity(make_unique<CircleShape>(25.f))
{
  _shape->setFillColor(Color::Magenta);
  _shape->setOrigin(Vector2f(25.f, 25.f));
}

void Player::update(double dt)
{
  // Obtener la entrada del teclado o cualquier otro método que uses
  // para determinar qué teclas se están presionando

  // Pseudo código para mover en cuatro direcciones
  if (Keyboard::isKeyPressed(Keyboard::Up)) {
    // Mover hacia arriba
    move(Vector2f(0, -_speed * dt));
  }
  if (Keyboard::isKeyPressed(Keyboard::Down)) {
    // Mover hacia abajo
    move(Vector2f(0, _speed * dt));
  }
  if (Keyboard::isKeyPressed(Keyboard::Left)) {
    // Mover hacia la izquierda
    move(Vector2f(-_speed * dt, 0));
  }
  if (Keyboard::isKeyPressed(Keyboard::Right)) {
    // Mover hacia la derecha
    move(Vector2f(_speed * dt, 0));
  }

  // Lógica adicional para el jugador, si es necesario

  // Llamar al método update de la clase base (Entity)
  Entity::update(dt);
}

void Player::render(RenderWindow &window) const
{
  window.draw(*_shape);
}
