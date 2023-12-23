#include "SoundManager.h"
#include <EEPROM.h>
#include "config.h"
#include "utils.h"
#include "resources/sounds.h"

SoundManager::SoundManager() : activeSound{(byte) SoundType::NONE} {}

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

  activeSound = (byte) sound;
  currentTone = 0;

  playTone();
}

void SoundManager::runtime() {
  if (!isPlaying()) {
    return;
  }

  if (currentTone == 0 || delayedExec(lastTone, getActiveSound()->notes[currentTone - 1].duration)) {
    playTone();
  }
}

bool SoundManager::isPlaying() const {
  return getActiveSound() != nullptr;
}

const Sound* SoundManager::getActiveSound() const {
  return getSound((SoundType) activeSound);
}

void SoundManager::playTone() {
  if (!isPlaying()) {
    return;
  }

  const Note& note = getActiveSound()->notes[currentTone];
  tone(buzzerPin, note.value, note.duration);

  currentTone++;
  if (currentTone == getActiveSound()->lenNotes) {
    activeSound = (byte) SoundType::NONE;
  }
}
