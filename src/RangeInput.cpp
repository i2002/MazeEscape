#include "RangeInput.h"
#include "context.h"

RangeInput::RangeInput(const char *title, byte initialValue) {
  statusDisp.printTitle(title);

  value = initialValue <= maxSteps ? initialValue : 0;
}

bool RangeInput::stepsIncrement() {
  if (value >= maxSteps) {
    return false;
  }

  value++;
  return true;
}

bool RangeInput::stepsDecrement() {
  if (value <= 0) {
    return false;
  }

  value--;
  return true;
}

void RangeInput::preview() {
  statusDisp.printRange(value);
}

byte RangeInput::getValue() const {
  return value;
}
