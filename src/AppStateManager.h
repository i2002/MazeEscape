#ifndef APP_STATE_MANAGER_H
#define APP_STATE_MANAGER_H

#include <Arduino.h>


/**
 * @brief Enum to define app states.
 *
 * @param UNCHANGED app state didn't change
 * @param STARTUP app startup animation and sound
 * @param MAIN_NAVIGATION display / resume main menu
 * @param GAME_START prepare game for start
 * @param LEVEL_START level start animation and sound
 * @param GAME_RUNNING game level in progress
 * @param SCORE_REVIEW display score review after game won / lost (delay for skip)
 * @param SCORE_REVIEW_SKIP allow button press to continue
 * @param HIGHSCORE_REVIEW show the highscore place earned and redirect to leaderboard name input
 * @param SAVE_HIGHSCORE save the highscore to leaderbord
 * @param ENDED game run ended, return to MAIN_NAVIGATION
 */
enum class AppState : byte {
  UNCHANGED,
  STARTUP,
  MAIN_NAVIGATION,
  GAME_START,
  LEVEL_START,
  GAME_RUNNING,
  SCORE_REVIEW,
  SCORE_REVIEW_SKIP,
  HIGHSCORE_REVIEW,
  SAVE_HIGHSCORE,
  ENDED
};


/**
 * @brief Enum to define app input contexts.
 * 
 * @param NONE no input handlers
 * @param UI_INPUT input manager runtime
 * @param GAME_INPUT game runtime
 * @param SKIP_INPUT wait for button press to change to next state
 */
enum class AppInputContext : byte {
  NONE,
  UI_INPUT,
  GAME_INPUT,
  SKIP_INPUT
};


/**
 * @brief App state change handlers.
 */
class AppStateManager {
public:
  // Timing constants
  static const int startupDelay = 2000;
  static const int levelStartupDelay = 3000;
  static const int scoreReviewSkipDelay = 500;
  static const int highscoreReviewDelay = 3000;

private:
  AppState currentState = AppState::UNCHANGED;
  AppInputContext inputContext = AppInputContext::NONE;
  unsigned long transitionTimer = 0;
  unsigned long transitionTimerDuration = 0;

public:
  /**
   * @brief Manually change app state.
   * This triggers the state change handlers.
   * 
   * @param newState the new state
   */
  void changeState(AppState newState);

  /**
   * @brief Apply state transition based on current state.
   */
  void stateTransition();

  /**
   * @brief Update transition timer.
   */
  void tickTimer();

  /**
   * @brief Get the current input context.
   *
   * @return AppInputContext 
   */
  AppInputContext getInputContext();

private:
  /**
   * @brief Change the current input context.
   * 
   * @param newContext the new context
   */
  void setInputContext(AppInputContext newContext);

  /**
   * @brief Start transition timer.
   * State transition will be triggered after the timer expires.
   * 
   * @param timerDuration the duration (in ms) of the state transition delay
   */
  void setTransitionTimer(unsigned long timerDuration);
};

#endif // APP_STATE_MANAGER_H
