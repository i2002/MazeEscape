#include "../Menu.h"
#include "matrixImages.h"

// - Macro for getting the size of a statically allocated vector of MenuOptions
#define MENU_OPTIONS_SIZE(options) sizeof(options) / sizeof(MenuOption)

enum class AppMenu {
  MAIN_MENU,
  SETTINGS_SUBMENU
};

const MenuOption mainMenuOptions[] = {
  { "Start game", startGameImage, MenuActionType::START_GAME },
  { "Help", tutorialImage, InputActionType::HELP_SCREENS },
  { "Settings", settingsImage, AppMenu::SETTINGS_SUBMENU },
  { "Leaderboard", leaderboardImage, InputActionType::LEADERBOARD_VIEW },
  { "About", aboutImage, InputActionType::ABOUT_SCREENS }
};

const MenuOption settingsSubmenuOptions[] = {
  { "LCD Light", lcdBrightnessImage, InputActionType::LCD_BRIGHTNESS_SETTING },
  { "Matrix Light", matrixBrightnessImage, InputActionType::MATRIX_BRIGHTNESS_SETTING },
  { "Sounds", soundImage, InputActionType::SOUND_SETTING },
  { "Reset scores", resetImage, MenuActionType::RESET_LEADERBOARD },
  { "Back", backImage, MenuActionType::MENU_BACK }
};

const Menu menus[] = {
  { "Main menu", mainMenuOptions, MENU_OPTIONS_SIZE(mainMenuOptions) },
  { "Settings", settingsSubmenuOptions, MENU_OPTIONS_SIZE(settingsSubmenuOptions) }
};

inline const Menu& getMenu(AppMenu menu) {
  return menus[(int) menu];
}
