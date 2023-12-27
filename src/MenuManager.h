#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Menu.h"

struct MenuStackItem {
  AppMenu menuType;
  int savedPos;
};

class MenuManager {
  static const int maxMenuStack = 3;

  byte stackSize = 0;
  MenuStackItem menuStack[maxMenuStack];
  Menu currentMenu;

public:
  void resetMenu(AppMenu menu);
  void pushMenu(AppMenu menu);
  void popMenu();
  void showMenu();
  void menuInputSetup();
  void menuInputPreview(byte option);
  void menuInputAction(byte option);

private:
  bool empty();
  MenuStackItem& getActiveMenu();
  MenuOption getOption(byte index);
};

#endif // MENU_MANAGER_H
