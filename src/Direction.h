#ifndef DIRECTION_H
#define DIRECTION_H

#include <Arduino.h>

enum class Direction : byte {
  UP, DOWN, LEFT, RIGHT, NEUTRAL
};

inline Direction randomDir() {
  return (Direction) random(0, 5);
}

#endif // DIRECTION_H
