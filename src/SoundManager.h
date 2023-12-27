#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H
#include <Arduino.h>

enum class SoundType : byte;

struct Note {
  int value;
  unsigned long duration;

  constexpr Note (int _value = 0, unsigned long _duration = 0) : value{_value}, duration{_duration} {}
};

struct Sound {
  const Note* notes;
  int lenNotes;

  constexpr Sound(const Note* _notes = nullptr, int _lenNotes = 0) : notes{_notes}, lenNotes{_lenNotes} {}
};

class SoundManager {
  Sound activeSound;
  Note currentNote;
  int toneIndex = 0;
  unsigned long lastTone = 0;

public:
  void setEnabled(bool state);

  bool getEnabled() const;

  void playSound(SoundType sound);

  void runtime();

private:
  bool isPlaying() const;

  Note getNote(int index) const;

  void playTone();
};

#endif // SOUND_MANAGER_H
