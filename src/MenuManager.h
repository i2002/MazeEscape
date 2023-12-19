#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "Menu.h"

struct MenuStackItem {
  Menu const* menu;
  int savedPos;
};

class MenuManager {
  static const int maxMenuStack = 3;

  byte stackSize = 0;
  MenuStackItem menuStack[maxMenuStack];

public:
  void resetMenu(const Menu &menu);
  void pushMenu(const Menu &menu);
  void popMenu();
  void showMenu();
  void menuInputSetup();
  void menuInputPreview(byte option);
  void menuInputAction(byte option);

private:
  bool empty();
  MenuStackItem& currentMenu();
  const MenuOption& getOption(byte index);
};

#endif // MENU_MANAGER_H
