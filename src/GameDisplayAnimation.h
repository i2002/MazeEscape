#ifndef GAME_DISPLAY_ANIMATION_H
#define GAME_DISPLAY_ANIMATION_H
#include <Arduino.h>
#include <LedControl.h>

enum class AnimationType {
  NO_ANIMATION,
  STARTUP_ANIMATION,
  // BOMB_EXPLODE_ANIMATION
  START_LEVEL_ANIMATION
};

class GameDisplay;

class GameDisplayAnimation {
  byte type;
  int currentFrame = 0;
  unsigned long lastRender = 0;

public:
  GameDisplayAnimation(AnimationType type);

  void render(GameDisplay &disp);

  bool inProgress();

private:
  int getLength();
  bool renderFrame(byte frame, byte row, byte col);
  bool renderStartupAnimation(byte frame, byte row, byte col);
  // bool renderBombExplodeAnimation(byte frame, byte row, byte col);
  bool renderLevelStartAnimation(byte frame, byte row, byte col);
};

#endif // GAME_DISPLAY_ANIMATION_H
