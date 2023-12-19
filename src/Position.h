#ifndef POSITION_H
#define POSITION_H
#include "Direction.h"

/**
 * @brief Represents a position in the game matrix
 */
class Position {
  char x;
  char y;

public:
  /**
   * @brief Construct a new Position object with default parameters (0, 0).
   */
  Position();

  /**
   * @brief Construct a new Position object.
   * 
   * @param x the column in the game matrix
   * @param y the row in the game matrix
   */
  Position(char x, char y);

  /**
   * @brief Generate a valid random position inside game matrix.
   * 
   * @return Position 
   */
  static Position randomPos();

  /**
   * @brief Get the stored x coordinate.
   * 
   * @return int
   */
  int getX() const;

  /**
   * @brief Get the storex y coordinate.
   * 
   * @return int 
   */
  int getY() const;

  /**
   * @brief Checks if the position is valid within the game matrix
   * (x and y values are within the game matrix range)
   * 
   * @return true if the position is valid, false otherwise
   */
  bool isValid() const;
  
  /**
   * @brief Get the next position from current position in direction dir
   * 
   * @param dir the direction of the new position
   * @return Position 
   */
  Position nextPos(Direction dir) const;

  /**
   * @brief Get the distance between two positions.
   * 
   * @param other the other position
   * @return byte 
   */
  byte distance(const Position &other) const;

  // Define comparison and arithmetic operators
  bool operator==(const Position &other) const;
  bool operator!=(const Position &other) const;
  Position operator+(const Position &other) const;
  Position operator-(const Position &other) const;
};

#endif // POSITION_H
