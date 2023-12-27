#ifndef MENU_H
#define MENU_H
#include <Arduino.h>
#include "resources/matrixImages.h"
#include "MenuAction.h"

struct MenuOption;

/**
 * @struct Menu
 * This struct defines the information about a menu (its name and the options of that menu).
 */
struct Menu {
  const char *name;
  const MenuOption *options;
  byte lenOptions;

  constexpr Menu(const char* name = nullptr, const MenuOption *options = nullptr, byte lenOptions = 0): name{name}, options{options}, lenOptions{lenOptions} {}

  Menu(AppMenu menuType);

};

/**
 * @struct MenuOption
 * This struct defines the information about a menu option (its name, the action triggered by the menu and the data associated with the action).
 * It is used to configure the options displayed when a menu is active.
 */
struct MenuOption {
  const char *name;
  const byte image;
  MenuAction action;

  constexpr MenuOption(const char *_name, ImageType _image, MenuAction _action) : name{_name}, image{(byte)_image}, action{_action} {}
  MenuOption(): name{nullptr}, image{0} {}
};

#endif // MENU_H
