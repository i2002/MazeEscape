#ifndef BULLET_H
#define BULLET_H

#include "Position.h"
#include "Direction.h"


/**
 * @brief Contains bullet information.
 */
class Bullet {
  Position pos;
  Direction dir;
  bool active;

public:
  /**
   * @brief Construct a new Bullet object with default parameters;.
   * (position 0, 0, direction up and inactive)
   */
  Bullet();

  /**
   * @brief Construct a new Bullet object.
   * 
   * @param pos the current position of the bullet
   * @param dir the direction in which the bullet travels
   * @param active if the bullet is currently active
   */
  Bullet(Position pos, Direction dir, bool active);

  /**
   * @brief Change current position next in the bullet's direction.
   * 
   * @return Position 
   */
  void advance();

  /**
   * @brief Get the bullet's current position.
   * 
   * @return Position 
   */
  Position getPos() const;

  /**
   * @brief Disable bullet.
   */
  void disable();

  /**
   * @brief Query the bullet's active state
   * 
   * @return true 
   * @return false 
   */
  bool isActive() const;
};

#endif // BULLET_H
