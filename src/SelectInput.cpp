#include "SelectInput.h"
#include "context.h"
#include "resources/sounds.h"

SelectInput::SelectInput(const char *title, byte _optionsSize, byte initialSelection) {
  optionsSize = _optionsSize;
  currentOption = initialSelection < optionsSize ? initialSelection : 0;

  statusDisp.printTitle(title);
  printCurrentOption();
}

bool SelectInput::nextOption() {
  if (!canNext()) {
    return false;
  }

  currentOption++;
  soundManager.playSound(SoundType::MENU_NAVIGATION_NEXT);
  printCurrentOption();
  return true;
}

bool SelectInput::prevOption() {
  if (!canPrev()) {
    return false;
  }

  currentOption--;
  soundManager.playSound(SoundType::MENU_NAVIGATION_PREV);
  printCurrentOption();
  return true;
}

byte SelectInput::getCurrentOption() const {
  return currentOption;
}

void SelectInput::printCurrentOption() {
  statusDisp.printMenuArrow(canPrev(), canNext());
}

bool SelectInput::canNext() {
  return currentOption < optionsSize - 1;
}

bool SelectInput::canPrev() {
  return currentOption > 0;
}
