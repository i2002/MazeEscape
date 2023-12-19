#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "Position.h"
#include "Direction.h"
#include "Bullet.h"
#include "Enemy.h"

/**
 * @brief The current state of the game.
 */
enum class GameState {
  NOT_STARTED, RUNNING, LOST, WON
};


/**
 * @brief Represents the type of game matrix cell.
 */
enum class CellType {
  EMPTY, WALL, PLAYER, BULLET, ENEMY, FINISH
};


struct Level {
  byte enemyCount;
  byte movementChance;
  byte fireChance;
};

/**
 * @brief Manage the game state and actions.
 */
class Game {
  // Game configuration
public:
  static constexpr int matrixHeight = 16;
  static constexpr int matrixWidth = 16;

private:
  static constexpr int maxBullets = 5;
  static constexpr int maxEnemies = 15;
  static constexpr int fireDistance = 5;
  static constexpr float minWalls = 0.4;
  static constexpr float maxWalls = 0.6;
  static constexpr int minFinishDistance = 10;
  static constexpr int minPlayerDistance = 2;
  static constexpr int minEnemyDistance = 5;
  static constexpr int randomPathChance = 20;
  // static constexpr int movementChance = 80;
  // static constexpr int fireChance = 20;
  static constexpr int destroyWallChance = 1;
  static constexpr int maxEnemyMoveTries = 10;
  static constexpr int enemyKillPoints = 2;
  static constexpr int remainingHealthPoints = 4;

  static constexpr int maxLevels = 3;
  static const Level levels[maxLevels];


  // Game state
  GameState gameState = GameState::NOT_STARTED;
  
  CellType gameMatrix[matrixHeight][matrixWidth];

  Position playerPos;
  Position finishPos;
  Bullet bullets[maxBullets];
  Enemy enemies[maxEnemies];
  
  Direction lastMoveDir = Direction::RIGHT;
  byte points = 0;
  byte lives = 3;
  byte level = 0;

public:
  /**
   * @brief Initialize game matrix and player position.
   * The walls and player position are randomly generated.
   */
  void startGame();

  /**
   * @brief Move the current player position on the game map.
   * 
   * @param pos the direction of the movement
   * @return true the player position changed
   * @return false the player position could not be changed (wall intersection)
   */
  bool playerMove(Direction dir);

  /**
   * @brief Player fire bullet action.
   */
  void fireBullet();

  /**
   * @brief Update bullet positions.
   */
  void updateBullets();

  /**
   * @brief Process enemy movement.
   */
  void processEnemyActions();

  /**
   * @brief Get the type of a game matrix cell.
   * 
   * @param pos the position in game matrix
   * @return CellType 
   */
  CellType getCellType(Position pos) const;

  /**
   * @brief Get the offset position of the game matrix relative to the game matrix.
   * The viewport is determined based on current player position.
   *
   * @return CellType 
   */
  Position getViewportOffset() const;

  /**
   * @brief Get the player position.
   * 
   * @return player position
   */
  Position getPlayerPos() const;

  /**
   * @brief Get the game state.
   * 
   * @return GameState
   */
  GameState getState();

  /**
   * @brief Get the current game points.
   * 
   * @return byte 
   */
  byte getPoints();

  /**
   * @brief Get current game level.
   * 
   * @return byte
   */
  byte getLevel();

  /**
   * @brief Get current game lives.
   * 
   * @return byte
   */
  byte getLives();

private:
  /**
   * @brief Set the tyep of a game matrix cell.
   * 
   * @param pos the position in game matrix
   * @param type the new type of the cell
   */
  void setCellType(Position pos, CellType type);

  /**
   * @brief Randomly initialize walls in game matrix and initial player position.
   */
  void generateMatrix();

  /**
   * @brief Place a new bullet on the map
   * 
   * @param start start position
   * @param dir bullet direction
   */
  void placeBullet(Position start, Direction dir);

  /**
   * @brief Checks if the current game matrix state is a winning condition.
   * 
   * @return true if the player won the game
   * @return false if the player hasn't yet won the game
   */
  bool checkWinCondition();

  /**
   * @brief Player level up.
   */
  void levelUp();

  /**
   * @brief Start level runtime.
   */
  void levelStartup();

  /**
   * @brief Compute player collision and apply all effects of that collision.
   * 
   * Collision cases:
   * - When the player intersects a wall (no effect).
   * - When the player hits a bullet, the player loses a life.
   * - When the player hits an enemy, the player loses a life.
   * 
   * @param pos the new player position
   * @return true if a player collision has occurred, false otherwise
   */
  bool playerCollision(Position pos);

  /**
   * @brief Compute enemy collision and apply all effects.
   * 
   * Collision cases:
   * - When the enemy intersects a wall (no effect).
   * - When the enemy hits a bullet, the enemy dies.
   * - When the enemy hits another enemy (no effect).
   * - When the enemy hits the player, the player loses a life.
   * 
   * @param pos the new enemy position
   * @return true if an enemy collision as occurred, false otherwise
   */
  bool enemyCollision(Position pos);

  /**
   * @brief Compute bullet collision and apply all effects of that collision.
   * 
   * Collision cases:
   * - When two bullets meet, they disable each other.
   * - When the bullet hits a wall it is disabled.
   * - When the bullet hits the player, the player loses a life.
   * - When the bullet hits an enemy, the enemy dies.
   * 
   * @param index the index of the bullet
   * @return true if a bullet collision has occurred, false otherwise
   */
  bool bulletCollision(byte index);

  /**
   * @brief Process enemy random movement.
   * 
   * @param index the index of the enemy
   */
  void enemyMove(byte index);

  /**
   * @brief Process enemy fire action.
   * If the player is in range, the enemy places a bullet in player direction.
   * 
   * @param index the index of the enemy
   */
  void enemyFire(byte index);

  /**
   * @brief Process enemy hit.
   * 
   * @param pos the position of the enemy
   */
  void enemyHit(Position pos);

  /**
   * @brief Process player hit.
   */
  void playerHit();
};

#endif // GAME_H
