#include "StatusDisplay.h"
#include <EEPROM.h>
#include "context.h"

// custom chars
uint8_t upDownArrow[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte upArrow[8] = {
  0b00100,
  0b01110,
  0b11111,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte downArrow[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

byte leftArrow[8] = {
	0b00010,
	0b00110,
	0b01110,
	0b11110,
	0b01110,
	0b00110,
	0b00010,
	0b00000
};

byte rightArrow[8] = {
  0b01000,
	0b01100,
	0b01110,
	0b01111,
	0b01110,
	0b01100,
	0b01000,
	0b00000
};

byte heart[8] = {
	0b00000,
	0b00000,
	0b01010,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000
};


void StatusDisplay::setup() {
  lcd.begin(dispCols, dispRows);
  setBrightness(getBrightness());

  lcd.createChar(UP_DOWN_ARROW, upDownArrow);
  lcd.createChar(UP_ARROW, upArrow);
  lcd.createChar(DOWN_ARROW, downArrow);
  lcd.createChar(LEFT_ARROW, leftArrow);
  lcd.createChar(RIGHT_ARROW, rightArrow);
  lcd.createChar(HEART, heart);
}

void StatusDisplay::setBrightness(byte level, bool save) {
  analogWrite(pinA, map(level, 0, RangeInput::maxSteps, 0, maxBrightness));

  if (save) {
    EEPROM.put(lcdBrightnessStoreIndex, level);
  }
}

byte StatusDisplay::getBrightness() {
  byte level;
  EEPROM.get(lcdBrightnessStoreIndex, level);
  return level;
}

void StatusDisplay::printTitle(const char *name) {
  resetDisplay();
  byte start = (dispCols - strlen(name)) / 2;
  lcd.setCursor(start, 0);
  lcd.print(name);
}

void StatusDisplay::printMenuOption(const char *name) {
  lcd.setCursor(0, 1);
  byte pos = 0;
  pos += lcd.write('>');
  pos += lcd.write(' ');
  pos += lcd.print(name);
  printBlank(pos, 15);
}

void StatusDisplay::printRange(int step) {
  lcd.setCursor(0, 1);
  byte pos = 0;
  pos += lcd.write(LEFT_ARROW);
  for (int i = 0; i < step; i++) {
    pos += lcd.write(0b11111111);
  }

  printBlank(pos, dispCols - 1);
  lcd.write(RIGHT_ARROW);
}

void StatusDisplay::printScreen(const Screen &screen)  {
  resetDisplay();

  // copy screen line pointers from program memory
  Screen screenBuf;
  memcpy_P(screenBuf, &screen, sizeof(Screen));

  if (screenBuf[0]) {
    lcd.print(FPTR(screenBuf[0]));
  }
  lcd.setCursor(0, 1);

  if (screenBuf[1]) {
    lcd.print(FPTR(screenBuf[1]));
  }
}

void StatusDisplay::printLeaderboard(byte place, byte score, const char* name) {
  lcd.setCursor(0, 1);
  byte pos = 0;

  // leaderboard position
  pos += lcd.print(place);
  pos += lcd.write('.');

  // highscore name
  for (int i = 0; i < leaderboardNameSize; i++) {
    pos += lcd.print(name[i]);
  }
  
  pos += lcd.print(' ');
  pos += lcd.print('-');
  pos += lcd.print(' ');

  // highscore points
  pos += lcd.print(score);
  printBlank(pos, dispCols - 1);
}

void StatusDisplay::printInputChar(byte cursor, char inputChar) {
  lcd.noCursor();
  lcd.setCursor(cursor, 1);
  lcd.print(inputChar);
  lcd.setCursor(cursor, 1);
  lcd.cursor();
}

void StatusDisplay::printMenuArrow(bool canPrev, bool canNext) {
  lcd.setCursor(dispCols - 1, 1);
  if (canPrev && canNext) {
    lcd.write(UP_DOWN_ARROW);
  } else if (canPrev) {
    lcd.write(UP_ARROW);
  } else if (canNext) {
    lcd.write(DOWN_ARROW);
  } else {
    lcd.write(' ');
  }
}

void StatusDisplay::printHighscoreMessage(byte position) {
  resetDisplay();

  lcd.print(F("Congratulations "));
  lcd.setCursor(0, 1);
  lcd.print(F("You are top "));
  lcd.print(position + 1);
}

void StatusDisplay::setupGameInfo(byte level, byte lives, byte points, byte enemies) {
  resetDisplay();
  updateLevel(level + 1);
  updateLives(lives);
  updatePoints(points);
  updateEnemies(enemies);
}

void StatusDisplay::updateLevel(byte level) {
  lcd.setCursor(levelCol, levelRow);
  lcd.print(F("Lv "));
  lcd.print(level);
}

void StatusDisplay::updateLives(byte lives) {
  byte pos = livesCol;
  lcd.setCursor(livesCol, livesRow);
  for (int i = 0; i < lives; i++) {
    pos += lcd.write(HEART);
  }
  printBlank(pos, dispCols, livesRow);
}

void StatusDisplay::updatePoints(byte points) {
  lcd.setCursor(pointsCol, pointsRow);
  lcd.print(F("Pts: "));
  lcd.print(points);
}

void StatusDisplay::updateEnemies(byte enemies) {
  lcd.setCursor(enemiesCol, enemiesRow);
  byte pos = enemiesCol;
  pos += lcd.print(F("En: "));
  pos += lcd.print(enemies);
  printBlank(pos, dispCols, enemiesRow);
}

void StatusDisplay::resetDisplay() {
  lcd.clear();
  lcd.home();
  lcd.noCursor();
}

void StatusDisplay::printBlank(byte from, byte to, byte line) {
  lcd.setCursor(from, line);
  for (byte i = from; i < to; i++) {
    lcd.write(' ');
  }
}
