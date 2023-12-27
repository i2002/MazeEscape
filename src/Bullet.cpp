#include "Bullet.h"


Bullet::Bullet() : Bullet{{0, 0}, Direction::UP, false} {}

Bullet::Bullet(Position _pos, Direction _dir, bool _active) : pos{_pos}, dir{_dir}, active{_active} {}

void Bullet::advance() {
  pos = pos.nextPos(dir);

  if (!pos.isValid()) {
    disable();
  }
}

Position Bullet::getPos() const {
  return pos;
}

void Bullet::disable() {
  active = false;
}

bool Bullet::isActive() const {
  return active;
}
