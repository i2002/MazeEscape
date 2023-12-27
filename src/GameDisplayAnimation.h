#ifndef GAME_DISPLAY_ANIMATION_H
#define GAME_DISPLAY_ANIMATION_H

#include <Arduino.h>
#include <LedControl.h>


/**
 * @brief Available animation types
 */
enum class AnimationType : byte {
  NO_ANIMATION,
  STARTUP_ANIMATION,
  START_LEVEL_ANIMATION
};


class GameDisplay;


/**
 * @brief Game display animation handlers.
 */
class GameDisplayAnimation {
public:
  // Animation configs
  static const unsigned int animationInterval = 50;

private:
  // Animation state
  AnimationType type;
  int currentFrame = 0;
  unsigned long lastRender = 0;

public:
  /**
   * @brief Construct a new Game Display Animation object.
   * 
   * @param type the animation type
   */
  GameDisplayAnimation(AnimationType type);

  /**
   * @brief Animation render routine.
   * 
   * @param disp reference to game display
   */
  void render(GameDisplay &disp);

  /**
   * @brief Checks whether the animation is in progress or had ended.
   * 
   * @return true if animation in progress, false if animation ended
   */
  bool inProgress();

private:
  /**
   * @brief Get the number of frames of the animation.
   * 
   * @return int 
   */
  int getLength();

  /**
   * @brief Get state of a display pixel at given frame.
   * 
   * @param frame animation frame index
   * @param row the row of the frame pixel
   * @param col the col of the frame pixel
   * @return pixel state
   */
  bool renderFrame(byte frame, byte row, byte col);

  /**
   * @brief Render startup animation frame.
   * 
   * @param frame animation frame index
   * @param row the row of the frame pixel
   * @param col the col of the frame pixel
   * @return pixel state
   */
  bool renderStartupAnimation(byte frame, byte row, byte col);

  /**
   * @brief Render level start animation frame.
   * 
   * @param frame animation frame index
   * @param row the row of the frame pixel
   * @param col the col of the frame pixel
   * @return pixel state
   */
  bool renderLevelStartAnimation(byte frame, byte row, byte col);
};

#endif // GAME_DISPLAY_ANIMATION_H
