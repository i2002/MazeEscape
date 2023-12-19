#ifndef INPUT_H
#define INPUT_H
#include "Direction.h"

typedef void (*InputCallback)(byte);

class Input {
public:
  virtual void processMovement(Direction pos) = 0;
  virtual bool processActionBtn() = 0;
  virtual ~Input() {}
};

#endif // INPUT_H
