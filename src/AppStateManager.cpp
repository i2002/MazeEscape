#include "AppStateManager.h"
#include "context.h"
#include "utils.h"
#include "resources/menuDefinitions.h"
#include "resources/matrixImages.h"
#include "resources/displayScreens.h"
#include "resources/sounds.h"


void AppStateManager::changeState(AppState newState) {
  if (newState == AppState::UNCHANGED) {
    return;
  }

  currentState = newState;

  switch (newState) {
    case AppState::UNCHANGED:
      break;
  
    case AppState::STARTUP:
      statusDisp.printScreen(welcomeScreen);
      gameDisp.displayAnimation(AnimationType::STARTUP_ANIMATION);
      soundManager.playSound(SoundType::STARTUP_SOUND);
      setTransitionTimer(startupDelay);
      break;
    case AppState::MAIN_NAVIGATION:
      menuManager.resetMenu(AppMenu::MAIN_MENU);
      setInputContext(AppInputContext::UI_INPUT);
      break;

    case AppState::GAME_START:
      game.startGame();
      break;

    case AppState::LEVEL_START:
      setTransitionTimer(GameDisplay::matrixSize * GameDisplay::matrixSize * GameDisplayAnimation::animationInterval + levelStartupDelay);
      break;

    case AppState::GAME_RUNNING:
      setInputContext(AppInputContext::GAME_INPUT);
      statusDisp.setupGameInfo(game.getLevel(), game.getLives(), game.getPoints(), game.getEnemies());
      soundManager.playSound(SoundType::INPUT_SELECTION);
      break;

    case AppState::SCORE_REVIEW:
      if (game.getState() == GameState::LOST) {
        gameDisp.displayImage(ImageType::GAME_LOST);
        statusDisp.printScreen(lostGameScreen);
        soundManager.playSound(SoundType::GAME_LOST);
      } else {
        gameDisp.displayImage(ImageType::GAME_WON);
        statusDisp.printScreen(wonGameScreen);
        statusDisp.updatePoints(game.getPoints());
        soundManager.playSound(SoundType::GAME_WON);
      }
      setTransitionTimer(scoreReviewSkipDelay);
      break;

    case AppState::SCORE_REVIEW_SKIP:
      setInputContext(AppInputContext::SKIP_INPUT);
      break;

    case AppState::HIGHSCORE_REVIEW:
      statusDisp.printHighscoreMessage(leaderboardManager.isHighscore(game.getPoints()));
      setTransitionTimer(highscoreReviewDelay);
      break;

    case AppState::SAVE_HIGHSCORE:
      leaderboardManager.setPoints(game.getPoints());
      inputManager.setupInput(InputActionType::HIGHSCORE_NAME);
      setInputContext(AppInputContext::UI_INPUT);
      break;

    case AppState::ENDED:
      setTransitionTimer(1);
      break;
  }
}

void AppStateManager::stateTransition() {
  AppState newState = AppState::UNCHANGED;

  switch (currentState) {
    case AppState::UNCHANGED:
      newState = AppState::STARTUP;
      break;

    case AppState::STARTUP:
      newState = AppState::MAIN_NAVIGATION;
      break;

    case AppState::MAIN_NAVIGATION:
      menuManager.showMenu();
      break;

    case AppState::GAME_START:
      newState = AppState::GAME_START;
      break;

    case AppState::LEVEL_START:
      newState = AppState::GAME_RUNNING;
      break;

    case AppState::GAME_RUNNING:
      newState = AppState::GAME_RUNNING;
      break;

    case AppState::SCORE_REVIEW:
      newState = AppState::SCORE_REVIEW_SKIP;
      break;

    case AppState::SCORE_REVIEW_SKIP:
      newState = game.getState() == GameState::WON && leaderboardManager.isHighscore(game.getPoints()) != -1 ? AppState::HIGHSCORE_REVIEW : AppState::ENDED;
      break;

    case AppState::HIGHSCORE_REVIEW:
      newState = AppState::SAVE_HIGHSCORE;
      break;

    case AppState::SAVE_HIGHSCORE:
      leaderboardManager.saveHighscore();
      newState = AppState::ENDED;
      break;

    case AppState::ENDED:
      newState = AppState::MAIN_NAVIGATION;
      break;
  }

  changeState(newState);
}

void AppStateManager::tickTimer() {
  if (transitionTimerDuration != 0 && delayedExec(transitionTimer, transitionTimerDuration)) {
    transitionTimerDuration = 0;
    stateTransition();
  }
}

AppInputContext AppStateManager::getInputContext() {
  return inputContext;
}

void AppStateManager::setInputContext(AppInputContext newContext) {
  inputContext = newContext;
}

void AppStateManager::setTransitionTimer(unsigned long timerDuration) {
  setInputContext(AppInputContext::NONE);
  transitionTimer = millis();
  transitionTimerDuration = timerDuration;
}
