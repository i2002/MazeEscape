#ifndef UTILS_H
#define UTILS_H

/**
 * @brief Helper function to execute a code delay without blocking the main loop.
 * Update the lastExec argument and retrun true if the ammount specified has
 * passed since the last run.
 *
 * @param lastExec the last millis() time when the action has been executed
 * @param delay the ammount in milliseconds between two executions
 * @returns true if the ammount has passed and the lastExec argument has been
 *  updated, false otherwise
 */
inline bool delayedExec(unsigned long &lastExec, unsigned long delay) {
  unsigned long currentMillis = millis();
  if (currentMillis - lastExec >= delay) {
    lastExec = currentMillis;
    return true;
  }

  return false;
}

/**
 * @brief Return true with a percentage chance.
 * Assuming random() returns a linear distribution, this function returns true with the specified chance.
 * 
 * @param percent the chance of returning true
 * @return true if random chance, false otherwise
 */
inline bool randomChance(int percent) {
  int rand = random(0, 100);
  return rand >= (100 - percent);
}

#endif // UTILS_H
