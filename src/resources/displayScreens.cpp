#include "displayScreens.h"

/**
 * @brief Macro to define screen lines
 * 
 * @param name the name of the screen (used to generate string line variable names)
 * @param line1 string constant for the first line
 * @param line2 string constant for the second line
 */
#define SCREEN_LINES(name, line1, line2) \
  static const char name ## Line1[] PROGMEM = line1; \
  static const char name ## Line2[] PROGMEM = line2;

/**
 * @brief Macro to use defined screen lines for Screen initialization.
 * This macro is meant to be used together with SCREEN_LINES and the name parameter should be identical.
 * 
 * @param name the name of the screen (used to generate string line variable names)
 */
#define SCREEN_DEF(name) { name ## Line1, name ## Line2 }

/**
 * @brief Declare and initialize a Screen in program memory.
 * 
 * @param name the name of the screen
 * @param line1 string constant for the first line
 * @param line2 string constant for the second line
 */
#define PROGMEM_SCREEN(name, line1, line2) \
  SCREEN_LINES(name, line1, line2) \
  const Screen name PROGMEM = SCREEN_DEF(name);


PROGMEM_SCREEN(welcomeScreen, "     Maze      ", "    Escape     ")
PROGMEM_SCREEN(lostGameScreen, "You lost :(", "Try again      >")
PROGMEM_SCREEN(wonGameScreen, "You won :)", "               >")

SCREEN_LINES(aboutScreen1, "- Maze Escape -", "  version 1.1  ")
SCREEN_LINES(aboutScreen2, "-    Author   -", " Tudor Butufei ")
SCREEN_LINES(aboutScreen3, "- Github user -", "     i2002     ")

const Screen aboutScreens[aboutScreensSize] PROGMEM = {
  SCREEN_DEF(aboutScreen1),
  SCREEN_DEF(aboutScreen2),
  SCREEN_DEF(aboutScreen3)
};

SCREEN_LINES(helpScreen1, "Survive and", "escape the maze")
SCREEN_LINES(helpScreen2, "Move around", "using joystick")
SCREEN_LINES(helpScreen3, "Press button to", "fire bullet")
SCREEN_LINES(helpScreen4, "Intermitent bli", "nking dots are")
SCREEN_LINES(helpScreen5, "enemies who can", "move or fire")
SCREEN_LINES(helpScreen6, "Maze exit is", "marked with")
SCREEN_LINES(helpScreen7, "rapidly blink-", "ing dot")

const Screen helpScreens[helpScreensSize] PROGMEM = {
  SCREEN_DEF(helpScreen1),
  SCREEN_DEF(helpScreen2),
  SCREEN_DEF(helpScreen3),
  SCREEN_DEF(helpScreen4),
  SCREEN_DEF(helpScreen5),
  SCREEN_DEF(helpScreen6),
  SCREEN_DEF(helpScreen7)
};
