#ifndef CONFIG_H
#define CONFIG_H
#include <Arduino.h>

// switch config between breadboard and pcb build
#define BREADBOARD_BUILD

const byte rs = 9;
const byte en = 13;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 4;
const byte d7 = 3;
const byte pinA = 5;

#ifdef BREADBOARD_BUILD
  const byte joystickPinX = A0;
  const byte joystickPinY = A1;
  const bool joystickInvertX = false;
  const bool joystickInvertY = false;
#else
  const byte joystickPinX = A1;
  const byte joystickPinY = A0;
  const bool joystickInvertX = true;
  const bool joystickInvertY = false;
#endif // BREADBOARD_BUILD

const byte dinPin = 12;
const byte clockPin = 11;
const byte loadPin = 10;

const byte triggerPin = A2;

const byte buzzerPin = 2;

#ifdef BREADBOARD_BUILD
  const bool matrixCommonAnode = true;
#else
  const bool matrixCommonAnode = false;
#endif // BREADBOARD_BUILD

const int leaderboardSize = 5;
const int leaderboardNameSize = 5;
const int maxHighscorePoints = 255;

const int lcdBrightnessStoreIndex = 2;
const int matrixBrightnessStoreIndex = 4;
const int soundSettingStoreIndex = 6;
const int leaderboardStoreIndex = 12;

#endif // CONFIG_H
