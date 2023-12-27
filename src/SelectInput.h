#ifndef SELECT_INPUT_H
#define SELECT_INPUT_H

#include <Arduino.h>


/**
 * @brief Select UI input state.
 */
struct SelectInput {
  byte optionsSize = 0;
  byte currentOption = 0;

public:
  /**
   * @brief Construct a new Select UI input state.
   * 
   * @param title input title
   * @param optionsSize number of select options
   * @param initialSelection initial selected option
   */
  SelectInput(const char *title = nullptr, byte optionsSize = 0, byte initialSelection = 0);

  /**
   * @brief Go to next option if possible.
   * 
   * @return true if state changed, false otherwise
   */
  bool nextOption();

  /**
   * @brief Go to previous option if possible.
   * 
   * @return true if state changed, false otherwise
   */
  bool prevOption();

  /**
   * @brief Input preview handler.
   * Displays indicator arrows if the user can go to the next / previous option
   */
  void preview();

  /**
   * @brief Get input state.
   * 
   * @return byte
   */
  byte getCurrentOption() const;

private:
  /**
   * @brief Checks whether the state can be changed to next option.
   * 
   * @return true if the next option is available, false otherwise
   */
  bool canNext();

  /**
   * @brief Checks whether the state can be changed to previous option.
   * 
   * @return true if the previous option is available, false otherwise
   */
  bool canPrev();
};

#endif // SELECT_INPUT_H
