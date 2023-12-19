#include "Game.h"
#include "context.h"


void Game::startGame() {
  generateMatrix();
  gameState = GameState::RUNNING;
  points = 0;
  statusDisp.setupGameInfo(1);
}

bool Game::playerMove(Direction dir) {
  if (dir == Direction::NEUTRAL) {
    return true;
  }

  Position newPos = playerPos.nextPos(dir);

  if (!validatePos(newPos)) {
    return false;
  }

  playerPos = newPos;
  return true;
}

void Game::placeBomb(unsigned long time) {
  if (bombActive) {
    return;
  }

  bombPos = playerPos;
  setCellType(bombPos, CellType::BOMB);
  bombPlacementTime = time;
  bombActive = true;
}

bool Game::bombTick(unsigned long time) {
  if (!bombActive || time - bombPlacementTime < bombExplodeTime) {
    return false;
  }

  explodeBomb();

  if (checkWinCondition()) {
    gameState = GameState::WON;
  }

  return true;
}

CellType Game::getCellType(Position pos) const {
  CellType res = gameMatrix[pos.getY()][pos.getX()];
  if (res == CellType::EMPTY && pos == playerPos) {
    res = CellType::PLAYER;
  }

  return res;
}

Position Game::getViewportOffset() const {
  int offsetX = min(max(0, playerPos.getX() - (GameDisplay::matrixSize / 2)), GameDisplay::matrixSize);
  int offsetY = min(max(0, playerPos.getY() - (GameDisplay::matrixSize / 2)), GameDisplay::matrixSize);
  return Position{offsetX, offsetY};
}

Position Game::getPlayerPos() const {
  return playerPos;
}

Position Game::getBombPosition() const {
  return bombPos;
}

void Game::setCellType(Position pos, CellType type) {
  gameMatrix[pos.getY()][pos.getX()] = type;
}

GameState Game::getState() {
  return gameState;
}

int Game::getPoints() {
  return points;
}

void Game::generateMatrix() {
  int wallsNr = random(0.5 * matrixHeight * matrixWidth, 0.75 * matrixHeight * matrixWidth + 1);
  playerPos = Position::randomPos();

  for (int i = 0; i < matrixHeight; i++) {
    for (int j = 0; j < matrixWidth; j++) {
      setCellType({j, i}, CellType::EMPTY);
    }
  }

  for (int i = 0; i < wallsNr; i++) {
    Position wallPos = Position::randomPos();

    // do not generate walls over player
    if (abs(playerPos.getX() - wallPos.getX()) < 2 && abs(playerPos.getY() - wallPos.getY()) < 2) {
      i--;
      continue;
    }

    setCellType(wallPos, CellType::WALL);
  }
}

void Game::explodeBomb() {
  bombActive = false;
  int nrDestroyed = 0;
  for (int row = 0; row < matrixHeight; row++) {
    Position pos = {bombPos.getX(), row};
    if (getCellType(pos) == CellType::WALL) {
      nrDestroyed++;
    }
    setCellType(pos, CellType::EMPTY);

    if (pos == playerPos) {
      gameState = GameState::LOST;
    }
  }

  for (int col = 0; col < matrixWidth; col++) {
    Position pos = {col, bombPos.getY()};
    if (getCellType(pos) == CellType::WALL) {
      nrDestroyed++;
    }
    setCellType(pos, CellType::EMPTY);

    if (pos == playerPos) {
      playerHit();
    }
  }

  points += nrDestroyed;
  gameDisp.displayAnimation(AnimationType::BOMB_EXPLODE_ANIMATION, true);
  statusDisp.updatePoints(points);
}

bool Game::checkWinCondition() {
  for (int row = 0; row < matrixHeight; row++) {
    for (int col = 0; col < matrixWidth; col++) {
      Position pos = {col, row};
      if (pos != playerPos && getCellType(pos) != CellType::EMPTY) {
        return false;
      }
    }
  }

  return true;
}

bool Game::validatePos(Position pos) {
  if (!pos.isValid()) {
    return false;
  }

  if (getCellType(pos) != CellType::EMPTY) {
    return false;
  }

  return true;
}

void Game::playerHit() {
  // TODO: decrease lives
  // TODO: check death
  gameState = GameState::LOST;
}


