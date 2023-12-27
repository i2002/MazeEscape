#ifndef MENU_ACTION_H
#define MENU_ACTION_H
#include <Arduino.h>
#include "InputAction.h"

enum class AppMenu : byte;

enum class MenuActionType : byte {
  CHANGE_MENU,
  MENU_BACK,
  START_GAME,
  UI_INPUT,
  RESET_LEADERBOARD,
  NO_ACTION
};

class MenuAction {
  MenuActionType type;
  byte data;

public:
  constexpr MenuAction(MenuActionType _type, byte _data = 0) : type{_type}, data{_data} {}
  constexpr MenuAction(AppMenu menu) : MenuAction(MenuActionType::CHANGE_MENU, (byte) menu) {}
  constexpr MenuAction(InputActionType input) : MenuAction(MenuActionType::UI_INPUT, (byte) input) {}
  constexpr MenuAction() : MenuAction(MenuActionType::NO_ACTION, 0) {}
 
  void handleMenuAction() const;

private:
  void changeMenuHandler() const;
  void menuBackHandler() const;
  void startGameHandler() const;
  void uiInputHandler() const;
};

#endif // MENU_ACTION_H
