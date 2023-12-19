#include "Position.h"
#include "Game.h"

static const int positionMovementMatrix[5][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {0, 0}};

Position::Position(): Position{0, 0} {}

Position::Position(int _x, int _y): x{_x}, y{_y} {}

Position Position::randomPos() {
  return {
    (int) random(0, Game::matrixWidth),
    (int) random(0, Game::matrixHeight)
  };
}

int Position::getX() const {
  return x;
}

int Position::getY() const {
  return y;
}

bool Position::isValid() const {
  if (getX() < 0 || getY() < 0 || getX() >= Game::matrixWidth || getY() >= Game::matrixHeight) {
    return false;
  }

  return true;
}

Position Position::nextPos(Direction dir) const {
  return {
    getX() + positionMovementMatrix[(int) dir][0],
    getY() + positionMovementMatrix[(int) dir][1],
  };
}

bool Position::operator==(const Position &other) const {
  return getX() == other.getX() && getY() == other.getY();
}

bool Position::operator!=(const Position &other) const {
  return getX() != other.getX() || getY() != other.getY();
}

Position Position::operator+(const Position &other) const {
  Position res = {
    getX() + other.getX(),
    getY() + other.getY()
  };
  return res;
}

Position Position::operator-(const Position &other) const {
  Position res = {
    getX() - other.getX(),
    getY() - other.getY()
  };
  return res;
}
