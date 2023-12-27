#ifndef INPUT_HANDLERS_H
#define INPUT_HANDLERS_H

#include <Arduino.h>


/**
 * @brief Input action types for UI input handlers.
 * 
 * @param MENU_INPUT navigate through menu options and select menu action
 * @param LCD_BRIGHTNESS_SETTING change the lcd brightness
 * @param MATRIX_BRIGHTNESS_SETTING change the matrix brightness
 * @param SOUND_SETTING enable / disable sounds setting
 * @param LEADERBOARD_VIEW navigate through leaderboard positions
 * @param HIGHSCORE_NAME input the leaderboard name to save along highscore
 * @param HELP_SCREENS navigate through help screens
 * @param ABOUT_SCREENS navigate through about screens
 */
enum class InputActionType : byte {
  NONE,
  MENU_INPUT,
  LCD_BRIGHTNESS_SETTING,
  MATRIX_BRIGHTNESS_SETTING,
  SOUND_SETTING,
  LEADERBOARD_VIEW,
  HIGHSCORE_NAME,
  HELP_SCREENS,
  ABOUT_SCREENS
};


union InputState;


/**
 * @brief Input manager handlers.
 */
class InputAction {
  InputActionType type;

public:
  /**
   * @brief Construct a new Input Action object.
   * 
   * @param type the type of the input action handlers
   */
  InputAction(InputActionType type = InputActionType::NONE);

  /**
   * @brief Setup input type based on current action type.
   */
  void setupInput();

  /**
   * @brief Handle input action.
   * 
   * @param state current input state
   */
  void action(const InputState &state);

  /**
   * @brief Handle input preview.
   * 
   * @param state current input state
   */
  void preview(const InputState &state);

  /**
   * @brief Whether the input action closes the input.
   * 
   * @param state current input state
   * @return true if the input action closes the input (state transition is called), false otherwise (the input remains active)
   */
  bool inputReturn(const InputState &state);

private:
  // Input action handlers
  void lcdBrightnessPreview(byte step);
  void lcdBrightnessAction(byte step);

  void matrixBrightnessPreview(byte step);
  void matrixBrightnessAction(byte step);

  void soundSettingPreview(byte option);
  void soundSettingAction(byte option);

  void leaderboardPreview(byte option);
  bool leaderboardClose(byte option);

  void highscoreNameAction(const char* input);

  void helpPreview(byte option);

  void aboutPreview(byte option);
};

#endif // INPUT_HANDLERS_H
