#include "Menu.h"
#include "resources/menuDefinitions.h"


Menu::Menu(AppMenu menuType) {
  memcpy_P(this, menus + (int)menuType, sizeof(Menu));
}

MenuOption::MenuOption() : name{nullptr}, image{0} {}
