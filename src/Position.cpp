#include "Position.h"
#include "Game.h"

static const char positionMovementMatrix[5][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {0, 0}};

Position::Position(): Position{0, 0} {}

Position::Position(char _x, char _y): x{_x}, y{_y} {}

Position Position::randomPos() {
  return {
    (char) random(0, Game::matrixWidth),
    (char) random(0, Game::matrixHeight)
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
    char(getX() + positionMovementMatrix[(int) dir][0]),
    char(getY() + positionMovementMatrix[(int) dir][1])
  };
}

byte Position::distance(const Position &other) const {
  return abs(getX() - other.getX()) + abs(getY() - other.getY());
}

bool Position::operator==(const Position &other) const {
  return getX() == other.getX() && getY() == other.getY();
}

bool Position::operator!=(const Position &other) const {
  return getX() != other.getX() || getY() != other.getY();
}

Position Position::operator+(const Position &other) const {
  Position res = {
    char(getX() + other.getX()),
    char(getY() + other.getY())
  };
  return res;
}

Position Position::operator-(const Position &other) const {
  Position res = {
    char(getX() - other.getX()),
    char(getY() - other.getY())
  };
  return res;
}
