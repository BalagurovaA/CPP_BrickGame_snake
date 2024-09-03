#ifndef BACKEND_SNAKE_CC
#define BACKEND_SNAKE_CC
#include "snake_backend.h"

using namespace s21;
namespace s21 {
///////////-----------SNAKE CLASS------------///////////
Snake::Snake() {
  create_field();
  speed = 1000;
  level = 0;
  border_flag = 0;
  code = 0;
  score = 0;
  record = 0;
  old_record = 0;

  prev_code = MOVE_DOWN;
}

void Snake::create_field() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      field_[i][j] = 0;
    }
  }
}

//спавн змейки в поле
void Snake::spawn_snake_field() {
  for (int i = 4; i >= 1; i--) {
    for (int j = 7; j < 8; j++) {
      field_[i][j] = 1;
      body_snake.push_back({i, j});
    }
  }
}

//движение вниз
void Snake::accel_down() {
  Coordinate head = body_snake.front();
  Coordinate tail = body_snake.back();
  if (field_[head.i][head.j] == 1 && head.i <= 19) {
    if (field_[head.i + 1][head.j] == 1 || head.i == 19) {
      border_flag = 1;
    } else {
      field_[head.i + 1][head.j] = 1;
      body_snake.push_front({head.i + 1, head.j});
      field_[tail.i][tail.j] = 0;
      body_snake.pop_back();
    }
  }
  code = MOVE_DOWN;
}

//движение вверх
void Snake::accel_up() {
  Coordinate head = body_snake.front();
  Coordinate tail = body_snake.back();

  if (field_[head.i][head.j] == 1 && head.i >= 0) {
    if (field_[head.i - 1][head.j] == 1 || head.i == 0) {
      border_flag = 1;
    } else {
      field_[head.i - 1][head.j] = 1;
      body_snake.push_front({head.i - 1, head.j});
      field_[tail.i][tail.j] = 0;
      body_snake.pop_back();
    }
  }
  code = MOVE_UP;
}

//движение влево
void Snake::accel_right() {
  Coordinate head = body_snake.front();
  Coordinate tail = body_snake.back();

  if (field_[head.i][head.j] == 1 && head.j <= 9) {
    if (field_[head.i][head.j + 1] == 1 || head.j == 9) {
      border_flag = 1;
    } else {
      field_[head.i][head.j + 1] = 1;
      body_snake.push_front({head.i, head.j + 1});
      field_[tail.i][tail.j] = 0;
      body_snake.pop_back();
    }
  }
  code = MOVE_R;
}

//движение вправо
void Snake::accel_left() {
  Coordinate head = body_snake.front();
  Coordinate tail = body_snake.back();

  if (field_[head.i][head.j] == 1 && head.j >= 0) {
    if (field_[head.i][head.j - 1] == 1 || head.j == 0) {
      border_flag = 1;
    } else {
      field_[head.i][head.j - 1] = 1;
      body_snake.push_front({head.i, head.j - 1});
      field_[tail.i][tail.j] = 0;
      body_snake.pop_back();
    }
  }
  code = MOVE_L;
}

//дефолтное движение проверка предыдущего движения
void Snake::control_moving() {
  if (prev_code == MOVE_DOWN) {
    accel_down();
  } else if (prev_code == MOVE_UP) {
    accel_up();
  } else if (prev_code == MOVE_L) {
    accel_left();
  } else if (prev_code == MOVE_R) {
    accel_right();
  }
}

//---------------APPLE---------------//
//спавн яблока
void Snake::spawn_apple() {
  bool pos_apple = false;
  Coordinate apple;
  while (!pos_apple) {
    apple = random_apple();
    if (field_[apple.i][apple.j] == 0) {
      field_[apple.i][apple.j] = 3;
      pos_apple = true;
    }
    apple = random_apple();
  }
}

//рандомные координаты для яблока
Coordinate Snake::random_apple() {
  Coordinate apple;
  apple.i = RAND_APPLE_I;
  apple.j = RAND_APPLE_J;
  return apple;
}

//поиск яблока во всем поле
Coordinate Snake::finding_apple() {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (field_[i][j] == 3) {
        apple.i = i;
        apple.j = j;
        break;
      }
    }
  }
  return apple;
}

//увеличение длины змейки
void Snake::rising_snake() {
  Coordinate head = body_snake.front();
  Coordinate apple = finding_apple();  //запоминаю координату яблок
  if (head.i == apple.i && head.j == apple.j) {
    body_snake.push_front(apple);
    field_[apple.i][apple.j] = 1;
    score++;
  }
  if (score > old_record) {
    record = score;
  }
}

//проверка что голова коснулась яблока
int Snake::check_the_head() {
  int i = body_snake.front().i;
  int j = body_snake.front().j;
  int flag = 0;
  if (i == finding_apple().i && j == finding_apple().j) {
    flag = 1;
  }
  return flag;
}

//---------------SCORE-RECORD---------------//
//выгрузка рекорда из файла
int Snake::reading_from_file() {
  FILE *file;
  int old_record = 0;
  file = fopen("s_score.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &old_record);
  }
  // record = old_record;
  return old_record;
}

//запись рекорда в файл
void Snake::writing_in_file() {
  FILE *file;
  if (score > record) {
    record = score;
  }
  file = fopen("s_score.txt", "w");
  if (file != NULL) fprintf(file, "%d", record);
}

//---------------LEVELS---------------//
//обновление уровня и скорости
void Snake::level_speed_update(int *state) {
  record = reading_from_file();
  if (level < 10 && level >= 0) {
    level = score / 5;
    speed = 1000 - (level * 100);
  }
  if (level >= 10 && score >= 50) {
    speed = 100;
  }
  if (score == 200) {
    *state = GAMEOVER;
  }
}

void Snake::fsm_up() {
  if (get_prev_code() != MOVE_DOWN) {
    accel_up();
    set_prev_code(get_code());
  }
}
void Snake::fsm_down() {
  if (get_prev_code() != MOVE_UP) {
    accel_down();
    set_prev_code(get_code());
  }
}

void Snake::fsm_left() {
  if (get_prev_code() != MOVE_R) {
    accel_left();
    set_prev_code(get_code());
  }
}
void Snake::fsm_right() {
  if (get_prev_code() != MOVE_L) {
    accel_right();
    set_prev_code(get_code());
  }
}

}  // namespace s21

#endif

// gcc -Wall -Werror -Wextra -std=c++17 -lncurses -lstdc++