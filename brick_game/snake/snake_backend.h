#ifndef BACKEND_SNAKE_H
#define BACKEND_SNAKE_H

#include <time.h>

#include <iostream>
#include <list>

#define HEIGHT 20
#define WIDTH 10

#define BIG_HEIGHT 42
#define BIG_WIDTH 42

#define RAND_APPLE_I 1 + rand() % (18)
#define RAND_APPLE_J 1 + rand() % (8)
#define BEGIN_TIMEOUT 1000

#define MOVE_DOWN 1
#define MOVE_UP 2
#define MOVE_R 3
#define MOVE_L 4

namespace s21 {

class Snake;
class Windows;
class Frontend;

struct Coordinate {
  int i;
  int j;
};

class Snake {
 private:
  int speed;
  int level;
  int score;
  int record;
  int old_record;
  int border_flag;
  int code;
  int prev_code;

  Coordinate apple;
  std::list<Coordinate> body_snake;

 protected:
  int field_[HEIGHT][WIDTH];

 public:
  Snake();
  int get_level() { return level; }
  void set_level(int new_l) { level = new_l; }
  int get_record() { return record; }
  void set_record(int rec) { record = rec; }
  int get_score() { return score; }
  void set_score(int new_score) { score = new_score; }
  void create_field();
  void spawn_snake_field();
  void accel_up();
  void accel_down();
  void accel_right();
  void accel_left();
  void control_moving();

  int get_border_flag() { return border_flag; }
  void set_border_flag(int flag) { border_flag = flag; }

  int get_code() { return code; }
  void set_code(int out_code) { code = out_code; }
  int get_prev_code() { return prev_code; }
  void set_prev_code(int code) { prev_code = code; }

  int get_field(int i, int j) { return field_[i][j]; }

  //---------------APPLE---------------//
  void spawn_apple();
  Coordinate finding_apple();
  void rising_snake();
  Coordinate random_apple();
  int check_the_head();

  //---------------WORK WITH FILES---------------//
  int reading_from_file();
  void writing_in_file();

  //---------------SCORE-RECORD---------------//
  void level_speed_update(int *state);
  int getter_speed() { return speed; }
  void set_speed(int n_speed) { speed = n_speed; }

  friend class Frontend;

  void fsm_up();
  void fsm_down();
  void fsm_left();
  void fsm_right();
};

enum state { BEGIN, SPAWN, MOVING, SHIFTING, ATTACHING, GAMEOVER };

void snake_the_game();

}  // namespace s21

#endif
