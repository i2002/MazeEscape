#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include "Direction.h"


/**
 * @brief Manage joystick state.
 */
class Joystick {
  // Joystick behaviour config
  static const int joystickUpperThreshold = 650;
  static const int joystickLowerThreshold = 350;
  static const int joystickReturnThreshlold = 50;

  static const int repeatedInputTimeout = 1500;
  static const int repeatedInputInterval = 300;

  // Joystick config
  const byte joystickPinX;
  const byte joystickPinY;
  const bool invertX;
  const bool invertY;

  // Joystick state
  Direction currentJoystickState = Direction::NEUTRAL;
  unsigned long lastUpdate = 0;
  bool repeatedInput = false;

public:
  /**
   * @brief Construct a new Joystick object.
   * By default, the input value range is between 0 for upmost LEFT and UP and 1023 for upmost RIGHT and DOWN.
   * This can be configured by the invertX and invertY params depending on hardware orientation.
   * 
   * @param joystickPinX board pin for x axis input
   * @param joystickPinY board pin for y axis input
   * @param invertX if the x axis should be inverted
   * @param intertY if the y axis should be inverted
   */
  Joystick(const byte joystickPinX, const byte joystickPinY, const bool invertX = false, const bool invertY = false);

  /**
   * @brief Setup joystick input pins.
   */
  void setup();

  /**
   * @brief Process joystick movement.
   * Based on current values and previous joystick position, it computes whether the current joystick position changed.
   * It is considered a joystick position change if leaving from NEUTRAL to either direction or returning from any
   * direction to NEUTRAL.
   *
   * @return true if the joystick state changed, false otherwise
   */
  bool processMovement();

  /**
   * @brief Get current joystick state.
   *
   * @return Direction
   */
  Direction getState();

private:
  /**
   * @brief Check if the value passes the upper / lower threshold.
   * 
   * @param value joystick axis value
   * @param upper true for upper threshold, false for lower threshold
   * @param inverted whether the axis range is inverted or not
   * @return true if the joystick exceeds the threshold in the specified direction, false otherwise
   */
  bool checkThreshold(int value, bool upper);

  /**
   * @brief Check if the joystick axis value returned from the specified position
   * 
   * @param value joystick axis value
   * @param upper true for upper threshold, false for lower threshold
   * @param inverted whether the axis range is inverted or not
   * @return true if the joystick returned from the specified direction, false otherwise
   */
  bool checkReturn(int value, bool upper);

  /**
   * @brief Check if a joystick position is triggered on the upper or lower threshold of the value range.
   * 
   * @param pos the joystick position
   * @return true if the specified joystick position is triggered on upper threshold
   * @return false if the specified joystick position is triggered on lower threshold
   */
  bool isUpperThreshold(Direction pos);
};

#endif // JOYSTICK_H
