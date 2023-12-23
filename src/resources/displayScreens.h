#ifndef DISPLAY_SCREENS_H
#define DISPLAY_SCREENS_H
#include "../StatusDisplay.h"

const Screen welcomeScreen = {
  "     Maze      ",
  "    Escape     "
};

const Screen lostGameScreen = {
  "You lost :(",
  "Try again      >"
};

const Screen wonGameScreen = {
  "You won :)",
  "               >"
};

const int aboutScreensSize = 3;

const char aboutScreen1Line1[] PROGMEM = "- Maze Escape -";
const char aboutScreen1Line2[] PROGMEM = "  version 1.1  ";
const char aboutScreen2Line1[] PROGMEM = "-    Author   -";
const char aboutScreen2Line2[] PROGMEM = " Tudor Butufei ";
const char aboutScreen3Line1[] PROGMEM = "- Github user -";
const char aboutScreen3Line2[] PROGMEM = "     i2002     ";

const Screen aboutScreens[aboutScreensSize] PROGMEM = {
  {aboutScreen1Line1, aboutScreen1Line2},
  {aboutScreen2Line1, aboutScreen2Line2},
  {aboutScreen3Line1, aboutScreen3Line2}
};

const int helpScreensSize = 7;

const char helpLine1Screen1[] PROGMEM = "Survive and";
const char helpLine2Screen1[] PROGMEM = "escape the maze";

const char helpLine1Screen2[] PROGMEM = "Move around";
const char helpLine2Screen2[] PROGMEM = "using joystick";

const char helpLine1Screen3[] PROGMEM = "Press button to";
const char helpLine2Screen3[] PROGMEM = "fire bullet";

const char helpLine1Screen4[] PROGMEM = "Intermitent bli";
const char helpLine2Screen4[] PROGMEM = "nking dots are";

const char helpLine1Screen5[] PROGMEM = "enemies who can";
const char helpLine2Screen5[] PROGMEM = "move or fire";

const char helpLine1Screen6[] PROGMEM = "Maze exit is";
const char helpLine2Screen6[] PROGMEM = "marked with";

const char helpLine1Screen7[] PROGMEM = "rapidly blink-";
const char helpLine2Screen7[] PROGMEM = "ing dot";

const Screen helpScreens[] PROGMEM = {
  {helpLine1Screen1, helpLine2Screen1},
  {helpLine1Screen2, helpLine2Screen2},
  {helpLine1Screen3, helpLine2Screen3},
  {helpLine1Screen4, helpLine2Screen4},
  {helpLine1Screen5, helpLine2Screen5},
  {helpLine1Screen6, helpLine2Screen6},
  {helpLine1Screen7, helpLine2Screen7}
};

#endif // DISPLAY_SCREENS_H
