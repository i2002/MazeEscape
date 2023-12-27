#include "matrixImages.h"

static const MatrixImage images[] PROGMEM = {
  0x00423c0000240000, // GAME_LOST
  0x003c420000240000, // GAME_WON
  0x00040c1c3c1c0c04, // START_GAME
  0x0010001010202418, // HELP
  0x185a24c3c3245a18, // SETTINGS
  0x0018181818001818, // ABOUT
  0x007e7e1e18180000, // LEADERBOARD
  0x0000ffffffff0000, // LCD_BRIGHTNESS
  0x007e7e7e7e7e7e00, // MATRIX_BRIGHTNESS
  0x0024465757462400, // SOUND
  0x0042241818244200, // RESET
  0x0020100804081020  // BACK
};

MatrixImage getImage(ImageType type) {
  MatrixImage image;
  memcpy_P(&image, images + (int) type, sizeof(MatrixImage));
  return image;
}
