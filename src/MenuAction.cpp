#include "MenuAction.h"
#include "context.h"
#include "resources/menuDefinitions.h"


void MenuAction::handleMenuAction() const {
  switch((MenuActionType)type) {
    case MenuActionType::CHANGE_MENU:
      return changeMenuHandler();
    case MenuActionType::MENU_BACK:
      return menuBackHandler();
    case MenuActionType::START_GAME:
      return startGameHandler();
    case MenuActionType::UI_INPUT:
      return uiInputHandler();
    case MenuActionType::RESET_LEADERBOARD:
      return leaderboardManager.resetLeaderboard();
    case MenuActionType::NO_ACTION:
      return;
  }
}


void MenuAction::changeMenuHandler() const {
  menuManager.pushMenu((AppMenu) data);
}

void MenuAction::menuBackHandler() const {
  menuManager.popMenu();
}

void MenuAction::startGameHandler() const {
  appStateManager.changeState(AppState::GAME_START);
}

void MenuAction::uiInputHandler() const {
  inputManager.setupInput((InputActionType) data);
}
