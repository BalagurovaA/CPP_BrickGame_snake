#ifndef CONTROLLER_CC
#define CONTROLLER_CC
#include "snake_controller.h"
namespace s21 {
Controller::Controller() { state = BEGIN; }

void snake_the_game() {
  Frontend front;
  Snake snake;
  Controller contr;
  while (front.get_window_flag() != 3) {
    contr.controller(snake, front);
  }
}

void Controller::controller(Snake &snake, Frontend &front) {
  timeout(snake.getter_speed());
  front.additional_win(snake);
  front.print_field(snake);

  // snake.level_speed_update();

  if (state == BEGIN) {
    FSM_begin(snake);
  } else if (state == SPAWN) {
    snake.spawn_apple();
    state = MOVING;
  } else if (state == MOVING) {
    snake.level_speed_update(&state);
    FSM_moving(snake, front);
  } else if (state == ATTACHING) {
    snake.rising_snake();
    state = SPAWN;
  } else if (state == GAMEOVER || front.get_window_flag() == 3) {
    front.game_over_(snake);
    snake.writing_in_file();
  }
}

///////////-----------CONTROLLER------------///////////
void Controller::FSM_begin(Snake &snake) {
  snake.set_prev_code(snake.get_code());
  snake.spawn_snake_field();
  state = SPAWN;
}

void Controller::FSM_spawn(Snake &snake, int *state) {
  snake.spawn_apple();
  *state = MOVING;
}

void Controller::FSM_moving(Snake &snake, Frontend &front) {
  int key = getch();
  if (snake.get_border_flag() != 1) {
    if ((key == 'w' || key == KEY_UP)) {
      snake.fsm_up();
    } else if (key == 's' || key == KEY_DOWN) {
      snake.fsm_down();
    } else if (key == 'a' || key == KEY_LEFT) {
      snake.fsm_left();
    } else if (key == 'd' || key == KEY_RIGHT) {
      snake.fsm_right();
    } else if (key == 'p') {
      if (front.pause_menu() == 3) {
        state = GAMEOVER;
      }
    } else {
      snake.control_moving();
    }
    if (snake.check_the_head() == 1) {
      state = ATTACHING;
    }
  } else
    state = GAMEOVER;
}

};  // namespace s21
#endif