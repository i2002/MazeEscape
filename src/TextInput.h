#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <Arduino.h>
#include "StatusDisplay.h"


/**
 * @brief Text UI input state.
 */
class TextInput {
  char inputBuf[StatusDisplay::dispCols];
  byte maxLen = 0;
  byte cursor = 0;

public:
  /**
   * @brief Construct a new Text UI input state.
   * 
   * @param title input title
   * @param maxLen maximum number of input characters
   * @param initialValue pointer to initial text (can be nullptr for empty initial text)
   */
  TextInput(const char *title = nullptr, byte maxLen = 0, const char* initialValue = nullptr);

  /**
   * @brief Move cursor to the left.
   */
  void moveCursorLeft();

  /**
   * @brief Move cursor to the right.
   */
  void moveCursorRight();

  /**
   * @brief Change current position to the next character.
   * The characters cycle through a-z, A-Z, 0-9 and space
   */
  void nextChar();
  
  /**
   * @brief Change current position to the previous character.
   * The characters cycle through a-z, A-Z, 0-9 and space
   */
  void prevChar();

  /**
   * @brief Input preview handler.
   * Display character to the current position.
   */
  void preview();

  /**
   * @brief Get the pointer to input state.
   * The pointer is to an internal buffer and should be copyied if data is needed afterwards.
   * 
   * @return const char*
   */
  const char* getInput() const;

private:
  /**
   * @brief Set cursor position.
   * 
   * @param cursor new cursor position index
   */
  void setCursor(byte cursor);

  /**
   * @brief Write character to cursor position.
   * 
   * @param newChar new character
   */
  void writeChar(char newChar);

  /**
   * @brief Get the next character for current position.
   * The characters cycle through a-z, A-Z, 0-9 and space
   *
   * @return char
   */
  char getNextChar();

  /**
   * @brief Get the previous character for current position.
   * The characters cycle through a-z, A-Z, 0-9 and space
   *
   * @return char 
   */
  char getPrevChar();

  /**
   * @brief Checks whether the given character is valid.
   * 
   * @param c character to be checked
   * @return true if character valid for input, false otherwise
   */
  bool isValidChar(char c);
};

#endif // TEXT_INPUT_H
