#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Menu.h"


/**
 * @brief Menu stack information
 */
struct MenuStackItem {
  AppMenu menuType;
  int savedPos;
};


/**
 * @brief Manage menu state.
 */
class MenuManager {
  static const int maxMenuStack = 3;

  byte stackSize = 0;
  MenuStackItem menuStack[maxMenuStack];
  Menu currentMenu;

public:
  /**
   * @brief Empty menu stack and push new root menu.
   * 
   * @param menu root menu
   */
  void resetMenu(AppMenu menu);

  /**
   * @brief Push menu to menu stack.
   * 
   * @param menu new menu
   */
  void pushMenu(AppMenu menu);

  /**
   * @brief Pop menu from menu stack and restore previous menu position.
   */
  void popMenu();

  /**
   * @brief Show menu input.
   */
  void showMenu();

  /**
   * @brief Menu select input setup handler.
   */
  void menuInputSetup();

  /**
   * @brief Menu select input preview handler.
   * 
   * @param option current option
   */
  void menuInputPreview(byte option);

  /**
   * @brief Menu select input action handler.
   * 
   * @param option selected option
   */
  void menuInputAction(byte option);

private:
  /**
   * @brief Checks whether the menu stack is empty.
   * 
   * @return true if the menu stack is empty, false otherwise
   */
  bool empty();

  /**
   * @brief Get the active menu stack item.
   * 
   * @return MenuStackItem& 
   */
  MenuStackItem& getActiveMenu();

  /**
   * @brief Get the option at index for current menu.
   * 
   * @param index option index
   * @return MenuOption 
   */
  MenuOption getOption(byte index);
};

#endif // MENU_MANAGER_H
