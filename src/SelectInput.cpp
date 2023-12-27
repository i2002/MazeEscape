#include "SelectInput.h"
#include "context.h"
#include "resources/sounds.h"


SelectInput::SelectInput(const char *title, byte _optionsSize, byte initialSelection) : optionsSize{_optionsSize} {
  currentOption = initialSelection < optionsSize ? initialSelection : 0;
  statusDisp.printTitle(title);
}

bool SelectInput::nextOption() {
  if (!canNext()) {
    return false;
  }

  currentOption++;
  soundManager.playSound(SoundType::MENU_NAVIGATION_NEXT);
  return true;
}

bool SelectInput::prevOption() {
  if (!canPrev()) {
    return false;
  }

  currentOption--;
  soundManager.playSound(SoundType::MENU_NAVIGATION_PREV);
  return true;
}

void SelectInput::preview() {
  statusDisp.printMenuArrow(canPrev(), canNext());
}

byte SelectInput::getCurrentOption() const {
  return currentOption;
}

bool SelectInput::canNext() {
  return currentOption < optionsSize - 1;
}

bool SelectInput::canPrev() {
  return currentOption > 0;
}
