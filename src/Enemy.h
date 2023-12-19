#ifndef ENEMY_H
#define ENEMY_H

#include "Position.h"

class Enemy {
  Position pos = {0, 0};
  bool alive = false;

public:
  Enemy(Position pos, bool alive): pos{pos}, alive{alive} {}
  Enemy() {}

  void setPos(Position pos) {
    this->pos = pos;
  }

  Position getPos() const {
    return pos;
  }

  void setAlive(bool alive) {
    this->alive = alive;
  }

  bool isAlive() const {
    return alive;
  }
};

#endif // ENEMY_H
