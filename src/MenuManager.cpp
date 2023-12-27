#include "MenuManager.h"
#include <Arduino.h>
#include "context.h"


void MenuManager::resetMenu(AppMenu menu) {
  stackSize = 0;
  pushMenu(menu);
}

void MenuManager::pushMenu(AppMenu menu) {
  menuStack[stackSize].menuType = menu;
  menuStack[stackSize].savedPos = 0;
  stackSize++;
  currentMenu = Menu(getActiveMenu().menuType);
  showMenu();
}

void MenuManager::popMenu() {
  if (empty()) {
    return;
  }

  menuStack[stackSize - 1].savedPos = 0;
  stackSize--;
  currentMenu = Menu(getActiveMenu().menuType);
  showMenu();
}

void MenuManager::showMenu() {
  if (!empty()) {
    inputManager.setupInput(InputActionType::MENU_INPUT);
  }
}

void MenuManager::menuInputSetup() {
  if (!empty()) {
    inputManager.setupSelectInput(currentMenu.name, currentMenu.lenOptions, getActiveMenu().savedPos);
  }
}

void MenuManager::menuInputAction(byte option) {
  if (!empty()) {
    getActiveMenu().savedPos = option;
    getOption(option).action.handleMenuAction();
  }
}

void MenuManager::menuInputPreview(byte option) {
  if (!empty()) {
    gameDisp.displayImage((ImageType)getOption(option).image);
    statusDisp.printMenuOption(getOption(option).name);
  }
}

bool MenuManager::empty() {
  return stackSize == 0;
}

MenuStackItem& MenuManager::getActiveMenu() {
  return menuStack[stackSize - 1];
}

MenuOption MenuManager::getOption(byte index) {
  MenuOption option;
  memcpy_P(&option, currentMenu.options + index, sizeof(MenuOption));
  return option;
}
