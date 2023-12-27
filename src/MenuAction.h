#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include <Arduino.h>
#include "InputAction.h"


enum class AppMenu : byte;


/**
 * @brief Menu action type
 * 
 */
enum class MenuActionType : byte {
  CHANGE_MENU,
  MENU_BACK,
  START_GAME,
  UI_INPUT,
  RESET_LEADERBOARD,
  NO_ACTION
};

/**
 * @brief Menu action handler.
 * Specify menu action handler based on action type and action data.
 */
class MenuAction {
  MenuActionType type;
  byte data;

public:
  /**
   * @brief Construct menu action.
   * 
   * @param type action type
   * @param data generic action data
   */
  constexpr MenuAction(MenuActionType _type, byte _data = 0) : type{_type}, data{_data} {}

  /**
   * @brief Construct change menu action.
   * 
   * @param menu menu type
   */
  constexpr MenuAction(AppMenu menu) : MenuAction(MenuActionType::CHANGE_MENU, (byte) menu) {}

  /**
   * @brief Construct input menu action.
   * 
   * @param input input action handlers type
   */
  constexpr MenuAction(InputActionType input) : MenuAction(MenuActionType::UI_INPUT, (byte) input) {}

  /**
   * @brief Construct menu action with no handler.
   */
  constexpr MenuAction() : MenuAction(MenuActionType::NO_ACTION, 0) {}
 
  /**
   * @brief Execute action handler.
   */
  void handleMenuAction() const;

private:
  // Menu action type handlers
  void changeMenuHandler() const;
  void menuBackHandler() const;
  void startGameHandler() const;
  void uiInputHandler() const;
};

#endif // MENU_ACTION_H
