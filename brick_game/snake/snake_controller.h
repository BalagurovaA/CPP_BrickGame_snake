#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "./../../gui/snake_gui/console/snake_frontend.h"
#include "snake_backend.h"

namespace s21 {
class Controller;
class Frontend;

//---------------FSM---------------//
class Controller {
 private:
  int state;

 public:
  Controller();

  void FSM_begin(Snake &snake);
  void FSM_spawn(Snake &snake, int *state);
  void FSM_moving(Snake &snake, Frontend &front);
  void controller(Snake &snake, Frontend &front);
};
}  // namespace s21
#endif
