#include "Game.h"
#include "context.h"
#include "utils.h"
#include "resources/sounds.h"


const Level Game::levels[maxLevels] = {
  { 5, 50, 15 },
  { 7, 60, 25 },
  { 10, 65, 40 }
};

void Game::startGame() {
  level = 0;
  points = 0;
  lives = 3;
  gameState = GameState::RUNNING;
  levelStartup();
}

bool Game::playerMove(Direction dir) {
  if (dir == Direction::NEUTRAL) {
    return true;
  }

  Position newPos = playerPos.nextPos(dir);

  if (!newPos.isValid() || playerCollision(newPos)) {
    return false;
  }

  setCellType(playerPos, CellType::EMPTY);
  setCellType(newPos, CellType::PLAYER);
  playerPos = newPos;
  lastMoveDir = dir;

  if (checkWinCondition()) {
    levelUp();
  }
  return true;
}

void Game::fireBullet() {
  Position bulletPos = playerPos.nextPos(lastMoveDir);
  placeBullet(bulletPos, lastMoveDir);
}

void Game::updateBullets() {
  for (int i = 0; i < maxBullets; i++) {
    // inactive bullet
    if (!bullets[i].isActive()) {
      continue;
    }

    setCellType(bullets[i].getPos(), CellType::EMPTY);
    bullets[i].advance();

    // bullet flew off the map
    if (!bullets[i].isActive()) {
      continue;
    }

    if (bulletCollision(i)) {
      bullets[i].disable();
      continue;
    }

    setCellType(bullets[i].getPos(), CellType::BULLET);
  }
}

void Game::processEnemyActions() {
  for (int i = 0; i < levels[level].enemyCount; i++) {
    if (!enemies[i].isAlive()) {
      continue;
    }

    if (randomChance(levels[level].movementChance)) {
      enemyMove(i);
    } else if (randomChance(levels[level].fireChance)) {
      enemyFire(i);
    }
  }
}

CellType Game::getCellType(Position pos) const {
  CellType res = gameMatrix[pos.getY()][pos.getX()];
  if (res == CellType::EMPTY && pos == finishPos) {
    return CellType::FINISH;
  }

  return res;
}

Position Game::getViewportOffset() const {
  char offsetX = min(max(0, playerPos.getX() - (GameDisplay::matrixSize / 2) + 1), GameDisplay::matrixSize);
  char offsetY = min(max(0, playerPos.getY() - (GameDisplay::matrixSize / 2) + 1), GameDisplay::matrixSize);
  return Position{offsetX, offsetY};
}

Position Game::getPlayerPos() const {
  return playerPos;
}

void Game::setCellType(Position pos, CellType type) {
  gameMatrix[pos.getY()][pos.getX()] = type;
}

GameState Game::getState() {
  return gameState;
}

byte Game::getPoints() {
  return points;
}

byte Game::getLevel() {
  return level;
}

byte Game::getLives() {
  return lives;
}

void Game::generateMatrix() {
  // reset map
  for (char i = 0; i < matrixHeight; i++) {
    for (char j = 0; j < matrixWidth; j++) {
      setCellType({j, i}, CellType::EMPTY);
    }
  }

  // player position
  playerPos = Position::randomPos();
  setCellType(playerPos, CellType::PLAYER);

  // place walls
  byte wallsNr = random(minWalls * matrixHeight * matrixWidth, maxWalls * matrixHeight * matrixWidth + 1);
  for (byte i = 0; i < wallsNr; i++) {
    Position wallPos = Position::randomPos();

    // do not generate walls over player
    if (playerPos.distance(wallPos) < minPlayerDistance) {
      i--;
      continue;
    }

    setCellType(wallPos, CellType::WALL);
  }

  // generate finish position
  finishPos = Position::randomPos();
  while(playerPos.distance(finishPos) < minFinishDistance) {
    finishPos = Position::randomPos();
  }
  setCellType(finishPos, CellType::FINISH);

  // ensure winning path
  Position pathPos = playerPos;
  Position next;
  Direction optimumDir;
  byte minDistance;
  Direction currentDir;
  while (pathPos != finishPos) {
    optimumDir = Direction::NEUTRAL;
    minDistance = finishPos.distance(pathPos);

    // find optimal direction
    for (byte i = 0; i < 4; i++) {
      currentDir = (Direction) i;
      if (finishPos.distance(pathPos.nextPos(currentDir)) < minDistance) {
        optimumDir = currentDir;
        minDistance = finishPos.distance(pathPos.nextPos(optimumDir));
      }
    }

    // randomize the path a little
    if (randomChance(randomPathChance)) {
      optimumDir = randomDir();
    }
  
    next = pathPos.nextPos(optimumDir);

    if (!next.isValid()) {
      continue;
    }

    if (getCellType(next) == CellType::WALL) {
      setCellType(next, CellType::EMPTY);
    }

    pathPos = next;
  }

  // place enemies
  Position enemyPos;
  for (byte i = 0; i < levels[level].enemyCount; i++) {
    enemyPos = Position::randomPos();

    // invalid position
    if (getCellType(enemyPos) != CellType::EMPTY) {
      i--;
      continue;
    }

    // distance enemies
    bool distanceNotGood = false;
    for (byte j = 0; j < i; j++) {
      if (enemyPos.distance(enemies[j].getPos()) < minEnemyDistance) {
        distanceNotGood = true;
      }
    }

    if (distanceNotGood) {
      i--;
      continue;;
    }

    // do not place enemies around player
    if (playerPos.distance(enemyPos) < minPlayerDistance) {
      i--;
      continue;
    }

    enemies[i] = Enemy{enemyPos, true};
    setCellType(enemyPos, CellType::ENEMY);
  }
}

void Game::placeBullet(Position startPos, Direction dir) {
  if (!startPos.isValid()) {
    return;
  }

  for (byte i = 0; i < maxBullets; i++) {
    if (!bullets[i].isActive()) {
      bullets[i] = {startPos, dir, true};

      if (bulletCollision(i)) {
        bullets[i].disable();
      } else {
        setCellType(bullets[i].getPos(), CellType::BULLET);
      }

      soundManager.playSound(SoundType::BULLET_FIRE);

      break;
    }
  }
}

bool Game::checkWinCondition() {
  if (playerPos == finishPos) {
    return true;
  }

  return false;
}

void Game::levelUp() {
  points += lives * remainingHealthPoints * (level + 1);
  statusDisp.updatePoints(points);

  level++;

  if (level == maxLevels) {
    gameState = GameState::WON;
    return;
  }

  levelStartup();
}

void Game::levelStartup() {
  generateMatrix();
  lives = 3;
  soundManager.playSound(SoundType::LEVEL_START);

  statusDisp.printTitle("Level setup");
  gameDisp.displayAnimation(AnimationType::START_LEVEL_ANIMATION);
  appStateManager.changeState(AppState::LEVEL_START);
}

bool Game::playerCollision(Position pos) {
  switch (getCellType(pos)) {
    case CellType::BULLET:
      playerHit();
      return true;

    case CellType::ENEMY:
      playerHit();
      return true;

    case CellType::WALL:
      return true;

    case CellType::EMPTY:
    case CellType::FINISH:
    case CellType::PLAYER: // should not happen
      return false;
  }

  return false;
}

bool Game::enemyCollision(Position pos) {
  switch (getCellType(pos)) {
    case CellType::BULLET:
      enemyHit(pos);
      return true;

    case CellType::PLAYER:
      playerHit();
      return true;

    case CellType::WALL:
      // random chance to destroy wall
      if (randomChance(destroyWallChance)) {
        setCellType(pos, CellType::EMPTY);
        return false;
      } else {
        return true;
      }
    case CellType::ENEMY:
    case CellType::FINISH:
      return true;

    case CellType::EMPTY:
      return false;
  }

  return false;
}

bool Game::bulletCollision(byte index) {
  Position pos = bullets[index].getPos();
  switch (getCellType(pos)) {
    case CellType::PLAYER:
      playerHit();
      return true;

    case CellType::ENEMY:
      enemyHit(pos);
      return true;

    case CellType::BULLET:
      for (int j = 0; j < index; j++) {
        if (bullets[j].isActive() && bullets[j].getPos() == pos) {
          bullets[j].disable();
        }
      }
      return true;

    case CellType::WALL:
      return true;

    case CellType::EMPTY:
    case CellType::FINISH:
      return false;
  }

  return false;
}

void Game::enemyMove(byte index) {
  for(int tries = 0; tries < maxEnemyMoveTries; tries++) {
    Position nextPos = enemies[index].getPos().nextPos(randomDir());
    if (nextPos.isValid() && !enemyCollision(nextPos)) {
      setCellType(enemies[index].getPos(), CellType::EMPTY);
      enemies[index].setPos(nextPos);
      if (enemies[index].isAlive()) {
        setCellType(enemies[index].getPos(), CellType::ENEMY);
      }

      return;
    }
  }
}

void Game::enemyFire(byte index) {
  Position enemyPos = enemies[index].getPos();

  if (playerPos.distance(enemyPos) <= fireDistance) {
    Direction dir = Direction::NEUTRAL;
    if(playerPos.getX() == enemyPos.getX()) {
      dir = playerPos.getY() > enemyPos.getY() ? Direction::DOWN : Direction::UP;
    } else if (playerPos.getY() == enemyPos.getY()) {
      dir = playerPos.getX() > enemyPos.getX() ? Direction::RIGHT : Direction::LEFT;
    }

    if (dir != Direction::NEUTRAL) {
      placeBullet(enemyPos.nextPos(dir), dir);
    }
  }
}

void Game::playerHit() {
  if (lives > 0) {
    lives--;
  }

  if (lives == 0) {
    gameState = GameState::LOST;
  }

  statusDisp.updateLives(lives);
  soundManager.playSound(SoundType::PLAYER_HIT);
}

void Game::enemyHit(Position pos) {
  setCellType(pos, CellType::EMPTY);

  for (int i = 0; i < levels[level].enemyCount; i++) {
    if (enemies[i].isAlive() && enemies[i].getPos() == pos) {
      enemies[i].setAlive(false);
      points += enemyKillPoints * (level + 1);
      statusDisp.updatePoints(points);
      soundManager.playSound(SoundType::ENEMY_HIT);
    }
  }
}
