#include "GameDisplayAnimation.h"
#include "GameDisplay.h"
#include "utils.h"
#include "context.h"

GameDisplayAnimation::GameDisplayAnimation(AnimationType _type) : type{_type}, currentFrame{0} {}

void GameDisplayAnimation::render(GameDisplay &disp) {
  if (!inProgress()) {
    return;
  }

  if (delayedExec(lastRender, animationInterval)) {
    for (byte row = 0; row < GameDisplay::matrixSize; row++) {
      for (byte col = 0; col < GameDisplay::matrixSize; col++) {
        disp.setLed(row, col, renderFrame(currentFrame, row, col));
      }
    }
  
    currentFrame++;
  }
}

bool GameDisplayAnimation::inProgress() {
  return currentFrame < getLength();
}

int GameDisplayAnimation::getLength() {
  switch(type) {
    case AnimationType::STARTUP_ANIMATION:
      return 4;

    case AnimationType::START_LEVEL_ANIMATION:
      return GameDisplay::matrixSize * GameDisplay::matrixSize + AppStateManager::levelStartupDelay / animationInterval;

    case AnimationType::NO_ANIMATION:
      return 0;
  }

  return 0;
}

bool GameDisplayAnimation::renderFrame(byte frame, byte row, byte col) {
  switch((AnimationType) type) {
    case AnimationType::STARTUP_ANIMATION:
      return renderStartupAnimation(frame, row, col);

    case AnimationType::START_LEVEL_ANIMATION:
      return renderLevelStartAnimation(frame, row, col);
    
    case AnimationType::NO_ANIMATION:
      return false;
  }

  return false;
}

bool GameDisplayAnimation::renderStartupAnimation(byte frame, byte row, byte col) {
  int mid = GameDisplay::matrixSize / 2;
  if ((row >= mid - 1 - frame && row <= mid + frame) && (col >= mid - 1 - frame && col <= mid + frame)) {
    return true;
  }

  return false;
}

bool GameDisplayAnimation::renderLevelStartAnimation(byte frame, byte row, byte col) {
  if (frame < Game::matrixHeight * Game::matrixWidth) {
    byte rows = frame / GameDisplay::matrixSize;
    byte cols = frame % GameDisplay::matrixSize;

    if ((row > rows) || (row == rows && col >= cols)) {
      return true;
    }
  }

  CellType type = game.getCellType(Position{(char)col, (char)row} + game.getViewportOffset());

  if (type == CellType::EMPTY) {
    return false;
  }

  if (type == CellType::PLAYER) {
    return frame / (GameDisplay::playerBlinkInterval / animationInterval) % 2;
  }

  if (type == CellType::ENEMY) {
    return frame / (GameDisplay::enemyBlinkInterval / animationInterval) % 4 != 0;
  }
  
  return true;
}
