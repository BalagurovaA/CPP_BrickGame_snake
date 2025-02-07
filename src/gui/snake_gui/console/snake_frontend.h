#ifndef FRONTEND_SNAKE_H
#define FRONTEND_SNAKE_H
#include <ncurses.h>

#include "./../../../brick_game/snake/snake_backend.h"
#include "./../../../brick_game/snake/snake_controller.h"

namespace s21 {
class Snake;
class Controller;

class Frontend {
 private:
  WINDOW *win;
  WINDOW *menu;
  WINDOW *pause;
  WINDOW *game_ov;
  WINDOW *add_win;
  int window_flag;

 public:
  Frontend();
  void settings();
  void initialization_of_colors();
  void print_field(Snake &snake);

  void measure(int i, int j);
  int main_menu();
  int pause_menu();
  void game_over_(Snake &snake);
  void additional_win(Snake &snake);

  void initialization_of_windows();
  void labels();
  void start_menu();
  void exit_menu();
  void labels_pause();
  void pause_continue();
  void pause_exit();
  void game_ov_labels();

  int get_window_flag() { return window_flag; }
  void set_window_flag(int w_f) { window_flag = w_f; }

  friend class Controller;
  friend class Snake;
};

}  // namespace s21

#endif