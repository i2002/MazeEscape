#ifndef STATUS_DISPLAY_H
#define STATUS_DISPLAY_H

#include <Arduino.h>
#include "LiquidCrystal.h"


/**
 * @brief LCD custom characters ids
 */
enum LCDChars : byte {
  UP_DOWN_ARROW,
  UP_ARROW,
  DOWN_ARROW,
  LEFT_ARROW,
  RIGHT_ARROW,
  HEART
};


// Custom type definitions
typedef const char* (Screen)[2];


/**
 * @brief Control the LCD.
 */
class StatusDisplay {
public:
  // Display configuration
  static const int dispCols = 16;
  static const int dispRows = 2;

private:
  static const int maxBrightness = 255;

  // Game state info positions
  static const int livesCol = 13;
  static const int livesRow = 0;

  static const int levelCol = 0;
  static const int levelRow = 0;

  static const int pointsCol = 0;
  static const int pointsRow = 1;

  static const int enemiesCol = 9;
  static const int enemiesRow = 1;

  // LCD control state
  LiquidCrystal lcd;

public:
  /**
   * @brief Construct a new Status Display object.
   */
  StatusDisplay();

  /**
   * @brief Initialize LCD and register custom characters.
   */
  void setup();

  /**
   * @brief Update display brightness.
   * 
   * @param level the brightness level (0 ... RangeInput max steps)
   * @param save whether to save the brightness to EEPROM or not
   */
  void setBrightness(byte level, bool save = false);

  /**
   * @brief Get current display brightness.
   * 
   * @return byte
   */
  byte getBrightness();

  /**
   * @brief Print title string.
   * Resets the display and prints the string centered on the first display line.
   * 
   * @param name title string (program memory pointer)
   */
  void printTitle(const char *name);

  /**
   * @brief Print menu select option.
   * 
   * @param name option name (program memory pointer)
   */
  void printMenuOption(const char *name);

  /**
   * @brief Print range bars and arrows.
   * 
   * @param step number of filled bars
   */
  void printRange(int step);

  /**
   * @brief Print screen lines.
   * 
   * @param screen screen data (program memory pointer reference)
   */
  void printScreen(const Screen &screen);

  /**
   * @brief Print leaderboard position.
   * 
   * @param place leaderboard place
   * @param score leaderboard score
   * @param name leaderboard name (RAM memory pointer)
   */
  void printLeaderboard(byte place, byte score, const char* name);

  /**
   * @brief Print text input character and cursor position.
   * 
   * @param cursor cursor position index
   * @param inputChar character at cursor position
   */
  void printInputChar(byte cursor, char inputChar);

  /**
   * @brief Print menu select arrows (shown if the user can go next / previous).
   * 
   * @param canPrev previous option is available
   * @param canNext next option is available
   */
  void printMenuArrow(bool canPrev = true, bool canNext = true);

  /**
   * @brief Print new highscore message (shown after score review).
   * 
   * @param position the leaderboard position reached
   */
  void printHighscoreMessage(byte position);

  /**
   * @brief Setup game info state display.
   * Resets screen and prints all state values.
   * 
   * @param level game level
   * @param lives number of lives
   * @param points points earned
   * @param enemies enemies remaining
   */
  void setupGameInfo(byte level, byte lives, byte points, byte enemies);

  /**
   * @brief Update game info level without reseting the screen.
   * 
   * @param level game level
   */
  void updateLevel(byte level);

  /**
   * @brief Update game info lives without reseting the screen.
   * 
   * @param lives number of lives
   */
  void updateLives(byte lives);

  /**
   * @brief Update game info points without reseting the screen.
   * 
   * @param points points earned
   */
  void updatePoints(byte points);

  /**
   * @brief Update game info remaining enemies without reseting the screen.
   * 
   * @param enemies enemies remaining
   */
  void updateEnemies(byte enemies);

private:
  /**
   * @brief Clear display and reset cursor position.
   */
  void resetDisplay();

  /**
   * @brief Utility to print blank space from position to position on specified line.
   * 
   * @param from start position (inclusive)
   * @param to end position (inclusive)
   * @param line display line
   */
  void printBlank(byte from = 0, byte to = 16, byte line = 1);
};

#endif // STATUS_DISPLAY_H
