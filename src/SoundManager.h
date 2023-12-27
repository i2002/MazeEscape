#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <Arduino.h>
#include "Sound.h"

enum class SoundType : byte;


/**
 * @brief Sound Manager.
 * Handles playing sounds to the buzzer. 
 */
class SoundManager {
  Sound activeSound;
  Note currentNote;
  int toneIndex = 0;
  unsigned long lastTone = 0;

public:
  /**
   * @brief Enable / disable sounds.
   * 
   * @param state whether the sounds should be enabled or disabled
   */
  void setEnabled(bool state);

  /**
   * @brief Check if sounds are enabled or disabled.
   * 
   * @return true if sounds are enabled, false if disabled
   */
  bool getEnabled() const;

  /**
   * @brief Start playing a sound
   * 
   * @param sound sound identifier
   */
  void playSound(SoundType sound);

  /**
   * @brief Asynchronous sound playing runtime.
   * Waits asynchronously for the next note to be played until the sound finishes playing.
   */
  void runtime();

private:
  /**
   * @brief If a sound is being currently played.
   * 
   * @return true if there is a sound currently playing, false otherwise
   */
  bool isPlaying() const;

  /**
   * @brief Get a note from current sound.
   * 
   * @param index note index
   * @return Note 
   */
  Note getNote(int index) const;

  /**
   * @brief Play the next note from current sound.
   */
  void playTone();
};

#endif // SOUND_MANAGER_H
