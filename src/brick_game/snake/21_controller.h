#ifndef _CONTROLLER_H
#define _CONTROLLER_H
#include "backend.h"
#include "frontend.h"

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
}
#endif
