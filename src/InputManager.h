#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Direction.h"
#include "InputAction.h"
#include "SelectInput.h"
#include "RangeInput.h"
#include "TextInput.h"


/**
 * @brief UI input type enum.
 * 
 * @param SELECT_INPUT move between options with joystick up and down, select current option on button press
 * @param RANGE_INPUT select value in range with joystick left and right, select current value on button press
 * @param TEXT_INPUT input text using joystick, apply action on button press
 */
enum class InputType : byte {
  SELECT_INPUT,
  RANGE_INPUT,
  TEXT_INPUT
};


/**
 * @brief Union to store input state, based on UI input type.
 */
union InputState {
  SelectInput selectInput;
  RangeInput rangeInput;
  TextInput textInput;

  InputState() {
    memset(this, 0, sizeof(*this));
  }
};


/**
 * @brief UI Input Manager.
 * Handle joystick movement and button press and update input states.
 */
class InputManager {
  InputType inputType;
  InputState state;
  InputAction actions;

public:
  /**
   * @brief Setup and display input.
   * 
   * @param type input action handlers type
   */
  void setupInput(InputActionType type);

  /**
   * @brief Process joystick movement based on current UI type and input action handlers.
   * 
   * @param dir joystick direction
   */
  void processMovement(Direction dir);

  /**
   * @brief Process action button press based on current input action handlers.
   */
  void processActionBtn();

private:
  friend class InputAction;
  friend class MenuManager;

  /**
   * @brief Setup a Select UI Input.
   * 
   * @param title input title
   * @param optionsSize number of select options
   * @param initialSelection initial selected option
   */
  void setupSelectInput(const char* title, byte optionsSize, byte initialSelection = 0);

  /**
   * @brief Setup a Range UI Input.
   * 
   * @param title input title
   * @param initialValue initial input value
   */
  void setupRangeInput(const char* title, byte initialValue = 0);

  /**
   * @brief Setup a Text UI Input.
   * 
   * @param title input title
   * @param maxLen maximum number of input characters
   * @param initialValue pointer to initial text (can be nullptr for empty initial text)
   */
  void setupTextInput(const char* title, byte maxLen, const char* initialValue = nullptr);

  /**
   * @brief Preview input state based on current input action handlers.
   */
  void previewInputState();

  /**
   * @brief Update select input state based on joystick movement.
   * 
   * @param dir joystick direction
   * @return true if input state changed, false otherwise
   */
  bool processSelectInputMovement(Direction dir);

  /**
   * @brief Update range input state based on joystick movement.
   * 
   * @param dir joystick direction
   * @return true if input state changed, false otherwise
   */
  bool processRangeInputMovement(Direction dir);

  /**
   * @brief Update text input state based on joystick movement.
   * 
   * @param dir joystick direction
   * @return true if input state changed, false otherwise
   */
  bool processTextInputMovement(Direction dir);
};

#endif // INPUT_MANAGER_H
