#include "menuDefinitions.h"

// - Macro for getting the size of a statically allocated vector of MenuOptions
#define MENU_OPTIONS_SIZE(options) sizeof(options) / sizeof(MenuOption)

static const char startGameOptionName[] PROGMEM = "Start game";
static const char helpOptionName[] PROGMEM = "Help";
static const char settingsOptionName[] PROGMEM = "Settings";
static const char leaderboardOptionName[] PROGMEM = "Leaderboard";
static const char aboutOptionName[] PROGMEM = "About";

static const MenuOption mainMenuOptions[] PROGMEM = {
  { startGameOptionName, ImageType::START_GAME, MenuActionType::START_GAME },
  { helpOptionName, ImageType::HELP, InputActionType::HELP_SCREENS },
  { settingsOptionName, ImageType::SETTINGS, AppMenu::SETTINGS_SUBMENU },
  { leaderboardOptionName, ImageType::LEADERBOARD, InputActionType::LEADERBOARD_VIEW },
  { aboutOptionName, ImageType::ABOUT, InputActionType::ABOUT_SCREENS }
};

static const char lcdLightOptionName[] PROGMEM = "LCD Light";
static const char matrixLightOptionName[] PROGMEM = "Matrix Light";
static const char soundOptionName[] PROGMEM = "Sounds";
static const char resetScoresOptionName[] PROGMEM = "Reset scores";
static const char backOptionName[] PROGMEM = "Back";

static const MenuOption settingsSubmenuOptions[] PROGMEM = {
  { lcdLightOptionName, ImageType::LCD_BRIGHTNESS, InputActionType::LCD_BRIGHTNESS_SETTING },
  { matrixLightOptionName, ImageType::MATRIX_BRIGHTNESS, InputActionType::MATRIX_BRIGHTNESS_SETTING },
  { soundOptionName, ImageType::SOUND, InputActionType::SOUND_SETTING },
  { resetScoresOptionName, ImageType::RESET, MenuActionType::RESET_LEADERBOARD },
  { backOptionName, ImageType::BACK, MenuActionType::MENU_BACK }
};

static const char mainMenuName[] PROGMEM = "Main menu";
static const char settingsMenuName[] PROGMEM = "Settings";

const Menu menus[] PROGMEM = {
  { mainMenuName, mainMenuOptions, MENU_OPTIONS_SIZE(mainMenuOptions) },
  { settingsMenuName, settingsSubmenuOptions, MENU_OPTIONS_SIZE(settingsSubmenuOptions) }
};
