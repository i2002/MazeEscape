#ifndef RANGE_INPUT_H
#define RANGE_INPUT_H

#include <Arduino.h>


/**
 * @brief Range UI input state.
 */
class RangeInput {
  byte value = 0;

public:
  static const byte maxSteps = 14;
  
  /**
   * @brief Construct a new Range UI input state.
   * 
   * @param title input title
   * @param initialValue initial input value
   */
  RangeInput(const char *title = nullptr, byte initialValue = 0);

  /**
   * @brief Increment value if possible.
   * 
   * @return true if state changed, false otherwise
   */
  bool stepsIncrement();

  /**
   * @brief Decrement value if possible.
   * 
   * @return true if state changed, false otherwise
   */
  bool stepsDecrement();

  /**
   * @brief Input preview handler.
   * Displays bars representing current value
   */
  void preview();

  /**
   * @brief Get input state.
   * 
   * @return byte
   */
  byte getValue() const;
};

#endif // RANGE_INPUT_H
