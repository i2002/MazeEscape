#include "../Menu.h"
#include "matrixImages.h"

enum class AppMenu : byte {
  MAIN_MENU,
  SETTINGS_SUBMENU,
  APP_MENU_SIZE
};

extern const Menu menus[(int) AppMenu::APP_MENU_SIZE];
