#include "Enemy.h"


Enemy::Enemy(Position _pos, bool _alive) : pos{_pos}, alive{_alive} {}

void Enemy::setPos(Position pos) {
  this->pos = pos;
}

Position Enemy::getPos() const {
  return pos;
}

void Enemy::setAlive(bool _alive)  {
  alive = _alive;
}

bool Enemy::isAlive() const {
  return alive;
}
