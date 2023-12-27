#include "SoundManager.h"
#include <EEPROM.h>
#include "config.h"
#include "utils.h"
#include "resources/sounds.h"


void SoundManager::setEnabled(bool state) {
  EEPROM.put(soundSettingStoreIndex, state);
}

bool SoundManager::getEnabled() const {
  bool enabled;
  EEPROM.get(soundSettingStoreIndex, enabled);
  return enabled;
}

void SoundManager::playSound(SoundType sound) {
  if (!getEnabled()) {
    return;
  }

  if (isPlaying()) {
    noTone(buzzerPin);
  }

  activeSound = getSound(sound);
  toneIndex = 0;
  playTone();
}

void SoundManager::runtime() {
  if (!isPlaying()) {
    return;
  }

  if (toneIndex == 0 || delayedExec(lastTone, currentNote.duration)) {
    playTone();
  }
}

bool SoundManager::isPlaying() const {
  return activeSound.lenNotes != 0;
}

Note SoundManager::getNote(int index) const {
  Note note;
  if (isPlaying()) {
    memcpy_P(&note, activeSound.notes + index, sizeof(Note));
  }
  return note;
}

void SoundManager::playTone() {
  if (!isPlaying()) {
    return;
  }

  currentNote = getNote(toneIndex);
  tone(buzzerPin, currentNote.value, currentNote.duration);

  toneIndex++;
  if (toneIndex == activeSound.lenNotes) {
    activeSound.lenNotes = 0;
  }
}
