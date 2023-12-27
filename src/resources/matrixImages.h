#ifndef MATRIX_IMAGES_H
#define MATRIX_IMAGES_H
#include "../GameDisplay.h"

enum class ImageType : byte {
  GAME_LOST,
  GAME_WON,
  START_GAME,
  HELP,
  SETTINGS,
  ABOUT,
  LEADERBOARD,
  LCD_BRIGHTNESS,
  MATRIX_BRIGHTNESS,
  SOUND,
  RESET,
  BACK
};

MatrixImage getImage(ImageType type);

#endif // MATRIX_IMAGES_H
