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

  /**
   * @brief Construct a new Menu object.
   * 
   * @param name menu name
   * @param options pointer to menu options array
   * @param lenOptions the number of menu options
   */
  constexpr Menu(const char* _name = nullptr, const MenuOption *_options = nullptr, byte _lenOptions = 0): name{_name}, options{_options}, lenOptions{_lenOptions} {}

  /**
   * @brief Load menu information from program memory given menu id.
   * 
   * @param menuType
   */
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

  /**
   * @brief Construct a new MenuOption object.
   * 
   * @param name menu option name
   * @param image menu option image to be shown on matrix display
   * @param action action to be executed on menu option select
   */
  constexpr MenuOption(const char *_name, ImageType _image, MenuAction _action) : name{_name}, image{(byte)_image}, action{_action} {}

  /**
   * @brief Construct a new Menu Option object with default options.
   */
  MenuOption();
};

#endif // MENU_H
