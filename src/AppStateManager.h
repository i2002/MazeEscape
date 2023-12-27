#ifndef APP_STATE_MANAGER_H
#define APP_STATE_MANAGER_H
#include <Arduino.h>

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

enum class AppInputContext : byte {
  NONE,
  UI_INPUT,
  GAME_INPUT,
  SKIP_INPUT
};

class AppStateManager {
public:
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
  void changeState(AppState newState);
  void stateTransition();
  void tickTimer();
  AppInputContext getInputContext();

private:
  void setInputContext(AppInputContext newContext);
  void setTransitionTimer(unsigned long timerDuration);
};

#endif // APP_STATE_MANAGER_H
