#ifndef SOUNDS_H
#define SOUNDS_H
#include "../SoundManager.h"
#include "pitches.h"

enum class SoundType : byte {
  STARTUP_SOUND,
  MENU_NAVIGATION_NEXT,
  MENU_NAVIGATION_PREV,
  INPUT_SELECTION,
  LEVEL_START,
  PLAYER_HIT,
  ENEMY_HIT,
  BULLET_FIRE,
  GAME_WON,
  GAME_LOST
};

#define SOUND_NOTES_SIZE(options) sizeof(options) / sizeof(Note)

const Note startupSoundNotes[] PROGMEM = {
  { NOTE_C4, 400 }, { NOTE_F4, 400 }, { NOTE_E4, 400 }, { NOTE_G4, 400 }
};

const Note menuNavigationPrev[] PROGMEM = {
  { NOTE_G4, 200 }
};

const Note menuNavigationNext[] PROGMEM = {
  { NOTE_A4, 200 }
};

const Note inputSelection[] PROGMEM = {
  { NOTE_E6, 250 }
};

const Note levelStart[] PROGMEM = {
  { NOTE_C5, 400 }, { NOTE_E5, 400 }, { NOTE_D5, 400 }, { NOTE_E5, 400 }, { NOTE_F5, 600 }
};

const Note playerHit[] PROGMEM = {
  { NOTE_C5, 200 }
};

const Note enemyHit[] PROGMEM = {
  { NOTE_F6, 200 }
};

const Note bulletFire[] PROGMEM = {
  { NOTE_A5, 100 }, { NOTE_G5, 150 }
};

const Note gameWin[] PROGMEM = {
  { NOTE_C5, 600 }, { NOTE_F5, 400 }, { NOTE_A5, 400 }, { NOTE_G5, 400 }, { NOTE_A5, 600 }
};

const Note gameLost[] PROGMEM = {
  { NOTE_G4, 500 }, { NOTE_E4, 400 }, { NOTE_D4, 400 }, { NOTE_C4, 500 }
};

const Sound sounds[] PROGMEM = {
  { startupSoundNotes, SOUND_NOTES_SIZE(startupSoundNotes) },
  { menuNavigationNext, SOUND_NOTES_SIZE(menuNavigationNext) },
  { menuNavigationPrev, SOUND_NOTES_SIZE(menuNavigationPrev) },
  { inputSelection, SOUND_NOTES_SIZE(inputSelection) },
  { levelStart, SOUND_NOTES_SIZE(levelStart) },
  { playerHit, SOUND_NOTES_SIZE(playerHit) },
  { enemyHit, SOUND_NOTES_SIZE(enemyHit) },
  { bulletFire, SOUND_NOTES_SIZE(bulletFire) },
  { gameWin, SOUND_NOTES_SIZE(gameWin) },
  { gameLost, SOUND_NOTES_SIZE(gameLost) }
};

inline Sound getSound(SoundType type) {
  Sound sound;
  memcpy_P(&sound, sounds + (int) type, sizeof(Sound));
  return sound;
}

#endif // SOUNDS_H
