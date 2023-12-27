#ifndef DIRECTION_H
#define DIRECTION_H

#include <Arduino.h>


/**
 * @brief Enum for encoding direction information.
 */
enum class Direction : byte {
  UP, DOWN, LEFT, RIGHT, NEUTRAL
};


/**
 * @brief Utility to get a random direction.
 *
 * @return Direction 
 */
inline Direction randomDir() {
  return (Direction) random(0, 5);
}

#endif // DIRECTION_H
