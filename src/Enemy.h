#ifndef ENEMY_H
#define ENEMY_H

#include "Position.h"


/**
 * @brief Game enemy information.
 */
class Enemy {
  Position pos = {0, 0};
  bool alive = false;

public:
  /**
   * @brief Construct a new Enemy object with default parameters.
   * (position: 0, 0, and dead)
   */
  Enemy() {}

  /**
   * @brief Construct a new Enemy object
   * 
   * @param pos the current position of the enemy on the game map
   * @param alive whether the enemy is alive or dead
   */
  Enemy(Position pos, bool alive);

  /**
   * @brief Set enemy position on game map.
   * 
   * @param pos the new position
   */
  void setPos(Position pos);

  /**
   * @brief Get enemy position on game map.
   *
   * @return Position 
   */
  Position getPos() const;

  /**
   * @brief Set whether the enemy is alive or dead.
   * 
   * @param alive true if enemy alive, false if dead
   */
  void setAlive(bool alive);

  /**
   * @brief Check whether enemy is alive or dead
   * 
   * @return true if enemy is alive, false if it's dead
   */
  bool isAlive() const;
};

#endif // ENEMY_H
