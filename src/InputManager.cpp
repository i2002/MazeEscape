#include "InputManager.h"
#include <new>
#include "context.h"
#include "resources/sounds.h"


void InputManager::setupInput(InputActionType type) {
  actions = InputAction(type);
  actions.setupInput();
  actions.preview(state);
  previewInputState();
}

void InputManager::processMovement(Direction dir) {
  bool stateChanged = false;
  switch ((InputType) inputType) {
    case InputType::SELECT_INPUT:
      stateChanged = processSelectInputMovement(dir);
      break;

    case InputType::RANGE_INPUT:
      stateChanged = processRangeInputMovement(dir);
      break;

    case InputType::TEXT_INPUT:
      stateChanged = processTextInputMovement(dir);
      break;
  }

  if (stateChanged) {
    actions.preview(state);
    previewInputState();
  }
}

void InputManager::processActionBtn() {
  bool inputReturn = actions.inputReturn(state);
  actions.action(state);
  soundManager.playSound(SoundType::INPUT_SELECTION);

  if (inputReturn) {
    appStateManager.stateTransition();
  }
}

void InputManager::setupSelectInput(const char* title, byte optionsSize, byte initialSelection) {
  new (&state.selectInput) SelectInput{title, optionsSize, initialSelection};
  inputType = (byte) InputType::SELECT_INPUT;
}

void InputManager::setupRangeInput(const char* title, byte initialValue) {
  new (&state.rangeInput) RangeInput{title, initialValue};
  inputType = (byte) InputType::RANGE_INPUT;
}

void InputManager::setupTextInput(const char* title, byte maxLen, const char* initialValue) {
  new (&state.textInput) TextInput{title, maxLen, initialValue};
  inputType = (byte) InputType::TEXT_INPUT;
}

void InputManager::previewInputState() {
  switch((InputType) inputType) {
    case InputType::RANGE_INPUT:
      return state.rangeInput.preview();

    case InputType::SELECT_INPUT:
      return state.selectInput.preview();

    case InputType::TEXT_INPUT:
      return state.textInput.preview();
  }
}

bool InputManager::processSelectInputMovement(Direction dir) {
  if (dir == Direction::DOWN) {
    return state.selectInput.nextOption();
  } else if (dir == Direction::UP) {
    return state.selectInput.prevOption();
  }

  return false;
}

bool InputManager::processRangeInputMovement(Direction dir) {
  if (dir == Direction::LEFT) {
    return state.rangeInput.stepsDecrement();
  } else if (dir == Direction::RIGHT) {
    return state.rangeInput.stepsIncrement();
  }

  return false;
}

bool InputManager::processTextInputMovement(Direction dir) {
  if (dir == Direction::LEFT) {
    state.textInput.moveCursorLeft();
  } else if (dir == Direction::RIGHT) {
    state.textInput.moveCursorRight();
  } else if (dir == Direction::UP) {
    state.textInput.nextChar();
  } else if (dir == Direction::DOWN) {
    state.textInput.prevChar();
  }

  return true;
}
