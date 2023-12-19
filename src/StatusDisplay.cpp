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


void StatusDisplay::setup() {
  lcd.begin(16, 2);
  setBrightness(getBrightness());

  lcd.createChar(UP_DOWN_ARROW, upDownArrow);
  lcd.createChar(UP_ARROW, upArrow);
  lcd.createChar(DOWN_ARROW, downArrow);
  lcd.createChar(LEFT_ARROW, leftArrow);
  lcd.createChar(RIGHT_ARROW, rightArrow);
}

void StatusDisplay::setBrightness(byte level, bool save) {
  const byte brightnessStep = 255 / RangeInput::maxSteps;
  analogWrite(pinA, level * brightnessStep);

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
  byte start = (16 - strlen(name)) / 2;
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

  printBlank(pos, 15);
  lcd.write(RIGHT_ARROW);
}

void StatusDisplay::printScreen(const Screen screen)  {
  resetDisplay();
  if (screen[0]) {
    lcd.print(screen[0]);
  }
  lcd.setCursor(0, 1);

  if (screen[1]) {
    lcd.print(screen[1]);
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
  printBlank(pos, 15);
}

void StatusDisplay::printInputChar(byte cursor, char inputChar) {
  lcd.noCursor();
  lcd.setCursor(cursor, 1);
  lcd.print(inputChar);
  lcd.setCursor(cursor, 1);
  lcd.cursor();
}

void StatusDisplay::printMenuArrow(bool canPrev, bool canNext) {
  lcd.setCursor(15, 1);
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

void StatusDisplay::setupGameInfo(byte level, byte lives, byte points) {
  resetDisplay();

  lcd.print(F("Lv "));
  lcd.setCursor(0, 1);
  lcd.print(F("Points:"));

  updateLevel(level + 1);
  updatePoints(points);
  updateLives(lives);
}

void StatusDisplay::updatePoints(byte points) {
  lcd.setCursor(8, 1);
  lcd.print(points);
}

void StatusDisplay::updateLevel(byte level) {
  lcd.setCursor(3, 0);
  lcd.print(level);
}

void StatusDisplay::updateLives(byte lives) {
  printBlank(13, 16, 0);
  lcd.setCursor(13, 0);
  for (int i = 0; i < lives; i++) {
    lcd.print('#');
  }
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
