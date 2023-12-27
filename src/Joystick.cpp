#include "Joystick.h"


Joystick::Joystick(const byte _joystickPinX, const byte _joystickPinY, const bool _invertX, const bool _invertY) : 
  joystickPinX{_joystickPinX}, joystickPinY{_joystickPinY}, invertX{_invertX}, invertY{_invertY}
{}

void Joystick::setup() {
  pinMode(joystickPinX, INPUT);
  pinMode(joystickPinY, INPUT);
}

bool Joystick::processMovement() {
  // read joystick status
  int joystickX = analogRead(joystickPinX);
  int joystickY = analogRead(joystickPinY);
  bool stateChanged = false;

  // joystick returned to neutral
  bool returnedFromUp = currentJoystickState == Direction::UP && checkReturn(joystickY, isUpperThreshold(Direction::UP));
  bool returnedFromDown = currentJoystickState == Direction::DOWN && checkReturn(joystickY, isUpperThreshold(Direction::DOWN));
  bool returnedFromLeft = currentJoystickState == Direction::LEFT && checkReturn(joystickX, isUpperThreshold(Direction::LEFT));
  bool returnedFromRight = currentJoystickState == Direction::RIGHT && checkReturn(joystickX, isUpperThreshold(Direction::RIGHT));
  bool joystickReturned = returnedFromUp || returnedFromDown || returnedFromRight || returnedFromLeft;

  if (joystickReturned) {
    currentJoystickState = Direction::NEUTRAL;
    stateChanged = true;
  }

  // movement only from neutral position
  if (currentJoystickState == Direction::NEUTRAL || joystickReturned) {
    if (checkThreshold(joystickY, isUpperThreshold(Direction::UP))) {
      currentJoystickState = Direction::UP;
      stateChanged = true;
    } else if (checkThreshold(joystickY, isUpperThreshold(Direction::DOWN))) {
      currentJoystickState = Direction::DOWN;
      stateChanged = true;
    } else if (checkThreshold(joystickX, isUpperThreshold(Direction::LEFT))) {
      currentJoystickState = Direction::LEFT;
      stateChanged = true;
    } else if (checkThreshold(joystickX, isUpperThreshold(Direction::RIGHT))) {
      currentJoystickState = Direction::RIGHT;
      stateChanged = true;
    }
  }

  if (stateChanged) {
    repeatedInput = false;
  } else if (currentJoystickState != Direction::NEUTRAL) {
    if (!repeatedInput && (millis() - lastUpdate >= repeatedInputTimeout)) {
      repeatedInput = true;
    }

    if (repeatedInput && (millis() - lastUpdate >= repeatedInputInterval)) {
      stateChanged = true;
    }
  }

  if (stateChanged) {
    lastUpdate = millis();
  }

  return stateChanged;
}

Direction Joystick::getState() {
  return currentJoystickState;
}

bool Joystick::checkThreshold(int value, bool upper) {
  return upper ? (value > joystickUpperThreshold) : (value < joystickLowerThreshold);
}

bool Joystick::checkReturn(int value, bool upper) {
  return upper ? (value < joystickUpperThreshold - joystickReturnThreshlold) : (value > joystickLowerThreshold + joystickReturnThreshlold);
}

bool Joystick::isUpperThreshold(Direction pos) {
  switch(pos) {
    case Direction::UP:
      return invertY;
    case Direction::DOWN:
      return !invertY;
    case Direction::LEFT:
      return invertX;
    case Direction::RIGHT:
      return !invertX;
    default:
      return false;
  }
}
