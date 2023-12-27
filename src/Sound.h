#ifndef SOUND_H
#define SOUND_H


/**
 * @brief A note from a sound, which has its value (frequency) and its duration (in ms)
 */
struct Note {
  int value;
  unsigned long duration;

  constexpr Note (int _value = 0, unsigned long _duration = 0) : value{_value}, duration{_duration} {}
};


/**
 * @brief Collection of notes.
 */
struct Sound {
  const Note* notes;
  int lenNotes;

  constexpr Sound(const Note* _notes = nullptr, int _lenNotes = 0) : notes{_notes}, lenNotes{_lenNotes} {}
};

#endif // SOUND_H
