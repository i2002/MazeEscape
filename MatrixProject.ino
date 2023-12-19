
#include "src/config.h"
#include "src/context.h"
#include "src/utils.h"
#include "src/resources/matrixImages.h"
#include "src/resources/displayScreens.h"
#include "src/resources/menuDefinitions.h"


// - Input components
Joystick joystick(joystickPinX, joystickPinY, joystickInvertX, joystickInvertY);
Button triggerBtn(triggerPin);

// - Output components
StatusDisplay statusDisp;
GameDisplay gameDisp;

// - App state components
AppStateManager appStateManager;
MenuManager menuManager;
InputManager inputManager;
LeaderboardManager leaderboardManager;
SoundManager soundManager;
Game game;


void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A2));

  joystick.setup();
  triggerBtn.setup();

  gameDisp.setup();
  statusDisp.setup();

  appStateManager.changeState(AppState::STARTUP);
}

void loop() {
  switch(appStateManager.getInputContext()) {
    case AppInputContext::NONE:
      break;

    case AppInputContext::UI_INPUT:
      uiNavigationRuntime();
      break;

    case AppInputContext::GAME_INPUT:
      gameRuntime();
      break;

    case AppInputContext::SKIP_INPUT:
      if (triggerBtn.buttonPressed()) {
        appStateManager.stateTransition();
      }
  }

  appStateManager.tickTimer();
  gameDisp.renderAnimation();
  soundManager.runtime();
}

inline void uiNavigationRuntime() {
  if (joystick.processMovement()) {
    inputManager.processMovement(joystick.getState());
  }

  if (triggerBtn.buttonPressed()) {
    inputManager.processActionBtn();
  }
}

unsigned long lastBulletUpdate = 0;
unsigned long lastEnemyAction = 0;
const int bulletUpdateInterval = 50;
const int enemyActionInterval = 1000;

inline void gameRuntime() {
  if (joystick.processMovement()) {
    if (game.playerMove(joystick.getState())) {
      gameDisp.resetPlayerBlink();
    }
  }

  if (triggerBtn.buttonPressed()) {
    game.fireBullet();
    gameDisp.resetPlayerBlink();
    lastBulletUpdate = millis();
  }

  if (delayedExec(lastBulletUpdate, bulletUpdateInterval)) {
    game.updateBullets();
  }

  if (delayedExec(lastEnemyAction, enemyActionInterval)) {
    game.processEnemyActions();
    // gameDisp.resetEnemyBlink();
  }

  gameDisp.renderGame();

  if (game.getState() != GameState::RUNNING) {
    appStateManager.changeState(AppState::SCORE_REVIEW);
  }
}
