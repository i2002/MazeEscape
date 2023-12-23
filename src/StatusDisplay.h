#ifndef STATUS_DISPLAY_H
#define STATUS_DISPLAY_H

#include <Arduino.h>
#include "LedControl.h"
#include "LiquidCrystal.h"
#include "config.h"

const byte UP_DOWN_ARROW = 0;
const byte UP_ARROW = 1;
const byte DOWN_ARROW = 2;
const byte LEFT_ARROW = 3;
const byte RIGHT_ARROW = 4;
const byte HEART = 5;

typedef const char* (Screen)[2];

class StatusDisplay {
public:
  static const int dispCols = 16;
  static const int dispRows = 2;

private:
  static const int maxBrightness = 255;

  static const int livesCol = 13;
  static const int livesRow = 0;

  static const int levelCol = 0;
  static const int levelRow = 0;

  static const int pointsCol = 0;
  static const int pointsRow = 1;

  static const int enemiesCol = 9;
  static const int enemiesRow = 1;

  LiquidCrystal lcd;

public:
  StatusDisplay() : lcd{rs, en, d4, d5, d6, d7} {}

  void setup();
  void setBrightness(byte level, bool save = false);
  byte getBrightness();
  void printTitle(const char *name);
  void printMenuOption(const char *name);
  void printRange(int step);
  void printScreen(const Screen screen);
  void printLeaderboard(byte place, byte score, const char* name);
  void printInputChar(byte cursor, char inputChar);
  void printMenuArrow(bool canPrev = true, bool canNext = true);
  void printHighscoreMessage(byte position);

  void setupGameInfo(byte level, byte lives, byte points, byte enemies);
  void updateLevel(byte level);
  void updateLives(byte lives);
  void updatePoints(byte points);
  void updateEnemies(byte enemies);

private:
  void resetDisplay();
  void printBlank(byte from = 0, byte to = 16, byte line = 1);
};

#endif // STATUS_DISPLAY_H
