#include "GameDisplay.h"
#include <EEPROM.h>
#include "utils.h"
#include "context.h"


GameDisplay::GameDisplay() : lc{dinPin, clockPin, loadPin, 1} {}

void GameDisplay::setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, getBrightness());
  lc.clearDisplay(0);
}

void GameDisplay::setBrightness(byte value, bool save) {
  lc.setIntensity(0, value);
  
  if (save) {
    EEPROM.put(matrixBrightnessStoreIndex, value);
  }
}

byte GameDisplay::getBrightness() {
  byte brightness;
  EEPROM.get(matrixBrightnessStoreIndex, brightness);
  return brightness;
}

void GameDisplay::renderGame() {
  if (animation.inProgress()) {
    return;
  }

  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      setLed(row, col, gameCellState(row, col));
    }
  }
}

void GameDisplay::renderAnimation() {
  animation.render(*this);
}

void GameDisplay::displayImage(MatrixImage image) {
  for (int i = 0; i < matrixSize; i++) {
    byte row = (image >> i * matrixSize) & 0xFF;
    for (int j = 0; j < matrixSize; j++) {
      setLed(i, j, bitRead(row, j));
    }
  }
}

void GameDisplay::displayAnimation(AnimationType animationType, bool sync) {
  if (animation.inProgress()) {
    return;
  }

  animation = animationType;

  if (sync) {
    while (animation.inProgress()) {
      animation.render(*this);
    }
  }
}

bool GameDisplay::gameCellState(char row, char col) {
  Position pos = Position{col, row} + game.getViewportOffset();
  CellType cell = game.getCellType(pos);
  switch (cell) {
    case CellType::EMPTY:
      return false;
    case CellType::FINISH:
      finishBlinkState = !finishBlinkState;
      return finishBlinkState;
    case CellType::WALL:
    case CellType::BULLET:
      return true;
    case CellType::ENEMY:
      if (delayedExec(lastEnemyBlink, enemyBlinkState ? enemyBlinkInterval * 3 : enemyBlinkInterval)) {
        enemyBlinkState = !enemyBlinkState;
      }
      return enemyBlinkState;
    case CellType::PLAYER:
      if (delayedExec(lastPlayerBlink, playerBlinkInterval)) {
        playerBlinkState = !playerBlinkState;
      }
      return playerBlinkState;
  }

  return false;
}

void GameDisplay::resetPlayerBlink() {
  playerBlinkState = true;
  lastPlayerBlink = millis();
}

void GameDisplay::resetEnemyBlink() {
  enemyBlinkState = false;
  lastEnemyBlink = millis();
}

void GameDisplay::setLed(char row, char col, bool state) {
  if (!matrixCommonAnode) {
    lc.setLed(0, row, col, state);
  } else {
    lc.setLed(0, col, row, state);
  }
}
