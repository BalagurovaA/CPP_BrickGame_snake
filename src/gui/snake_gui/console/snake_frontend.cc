#include "snake_frontend.h"
namespace s21 {
///////////-----------FRONTEND CLASS------------///////////
Frontend::Frontend() {
  settings();
  initialization_of_colors();
  initialization_of_windows();
  window_flag = 0;
  set_window_flag(main_menu());
}

void Frontend::settings() {
  initscr();
  curs_set(0);
  keypad(stdscr, 1);
  noecho();
  initialization_of_colors();
  srand(time(NULL));
}

//масштаб
void Frontend::measure(int i, int j) {
  for (int a = 1; a <= 2; a++) {
    for (int b = 1; b <= 4; b++) {
      mvwaddch(win, i + a, j + b, ' ');
    }
  }
}

//поле
void Frontend::print_field(Snake &snake) {
  wbkgd(win, COLOR_PAIR(7));
  wattron(win, COLOR_PAIR(4));
  box(win, '!', '-');
  wattroff(win, COLOR_PAIR(4));

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (snake.field_[i][j] == 0) {
        wattron(win, COLOR_PAIR(1));
        // mvwaddch(win, i + 1, j + 1, ' ');
        measure(i * 2, j * 4);

      } else if (snake.field_[i][j] == 1) {
        wattron(win, COLOR_PAIR(2));
        // mvwaddch(win, i + 1, j + 1, ' ');
        measure(i * 2, j * 4);

      } else if (snake.field_[i][j] == 3) {
        wattron(win, COLOR_PAIR(3));
        // mvwaddch(win, i + 1, j + 1, ' ');
        measure(i * 2, j * 4);
      }
    }
  }
  wrefresh(win);
}

//главное меню
int Frontend::main_menu() {
  int main_flag = 0;
  timeout(-1);
  int old_key = 0;
  int key = 0;
  while (main_flag == 0) {
    box(menu, '!', '-' | COLOR_PAIR(4));
    labels();
    key = getch();
    if (key == 'w' || key == KEY_UP) {
      wattron(menu, COLOR_PAIR(5));
      start_menu();
      wattroff(menu, COLOR_PAIR(5));
      exit_menu();
    } else if (key == 's' || key == KEY_DOWN) {
      wattron(menu, COLOR_PAIR(5));
      exit_menu();
      wattroff(menu, COLOR_PAIR(5));
      start_menu();

    } else if (key == 10 && (old_key == 's' || old_key == KEY_DOWN)) {
      main_flag = 3;
    }
    wrefresh(menu);

    if (key == 10 && (old_key == 'w' || old_key == KEY_UP)) {
      main_flag = 1;
    }
    old_key = key;
  }
  return main_flag;
}

//меню паузы
int Frontend::pause_menu() {
  int pause_flag = 0;
  timeout(-1);
  int old_key = 0;
  int key = 0;
  while (pause_flag == 0) {
    box(pause, '!', '-' | COLOR_PAIR(4));
    labels_pause();
    key = getch();
    if (key == 'w' || key == KEY_UP) {
      wattron(pause, COLOR_PAIR(5));
      pause_continue();
      wattroff(pause, COLOR_PAIR(5));
      pause_exit();
    } else if (key == 's' || key == KEY_DOWN) {
      wattron(pause, COLOR_PAIR(5));
      pause_exit();
      wattroff(pause, COLOR_PAIR(5));
      pause_continue();

    } else if (key == 10 && (old_key == 's' || old_key == KEY_DOWN)) {
      pause_flag = 3;
    }
    wrefresh(pause);

    if (key == 10 && (old_key == 'w' || old_key == KEY_UP)) {
      pause_flag = 1;
    }
    old_key = key;
  }
  return pause_flag;
}

//меню окончания игры
void Frontend::game_over_(Snake &snake) {
  int score = snake.get_score();
  wbkgd(game_ov, COLOR_PAIR(4));
  box(game_ov, '!', '-');
  int key = 0;
  while ((key = getch()) != 'q') {
    game_ov_labels();
    mvwprintw(game_ov, 28, 20, "%d", score);
    wrefresh(game_ov);
  }
  werase(game_ov);
  wrefresh(game_ov);
  delwin(game_ov);
  window_flag = 3;
}

//дополниетельное меню
void Frontend::additional_win(Snake &snake) {
  box(add_win, '!', '-');
  wbkgd(add_win, COLOR_PAIR(4));

  mvwprintw(add_win, 4, 6, "L E V E L");
  mvwprintw(add_win, 5, 5, "-----------");
  mvwprintw(add_win, 6, 10, "%d", snake.get_level());

  mvwprintw(add_win, 9, 6, "S P E E D");
  mvwprintw(add_win, 10, 5, "-----------");
  mvwprintw(add_win, 11, 9, "%d", snake.getter_speed());

  mvwprintw(add_win, 15, 6, "S C O R E");
  mvwprintw(add_win, 16, 5, "-----------");
  mvwprintw(add_win, 17, 10, "%d", snake.get_score());

  mvwprintw(add_win, 20, 5, "R E C O R D");
  mvwprintw(add_win, 21, 5, "-----------");
  mvwprintw(add_win, 22, 10, "%d", snake.get_record());

  mvwprintw(add_win, 25, 4, "M A X I M U M");
  mvwprintw(add_win, 26, 5, "-----------");
  mvwprintw(add_win, 27, 10, "200");

  wrefresh(add_win);
}

void Frontend::initialization_of_windows() {
  win = newwin(BIG_HEIGHT, BIG_WIDTH, 0, 0);
  menu = newwin(BIG_HEIGHT, BIG_WIDTH, 0, 0);
  pause = newwin(BIG_HEIGHT, BIG_WIDTH, 0, 0);
  game_ov = newwin(BIG_HEIGHT, BIG_WIDTH, 0, 0);
  add_win = newwin(BIG_HEIGHT, 20, 0, 43);
}
//-----------WINDOWS LABELS------------//

void Frontend::labels() {
  mvwprintw(menu, 4, 13, "+");
  mvwprintw(menu, 4, 29, "+");

  mvwprintw(menu, 5, 14, "+");
  mvwprintw(menu, 5, 28, "+");

  mvwprintw(menu, 6, 15, ".");
  mvwprintw(menu, 6, 27, ".");

  mvwprintw(menu, 7, 15, " \\ (^ v ^) /");

  mvwprintw(menu, 10, 16, " S N A K E ");
  mvwprintw(menu, 11, 16, "-----------");

  mvwprintw(menu, 15, 18, "M E N U");
  mvwprintw(menu, 16, 17, "---------");

  mvwprintw(menu, 20, 16, "- - - - - -");
  mvwprintw(menu, 21, 16, " S T A R T ");
  mvwprintw(menu, 22, 16, "- - - - - -");

  mvwprintw(menu, 24, 16, "- - - - - -");
  mvwprintw(menu, 25, 16, "  E X I T  ");
  mvwprintw(menu, 26, 16, "- - - - - -");
}

void Frontend::start_menu() {
  mvwprintw(menu, 20, 16, "- - - - - -");
  mvwprintw(menu, 21, 16, " S T A R T ");
  mvwprintw(menu, 22, 16, "- - - - - -");
}

void Frontend::exit_menu() {
  mvwprintw(menu, 24, 16, "- - - - - -");
  mvwprintw(menu, 25, 16, "  E X I T  ");
  mvwprintw(menu, 26, 16, "- - - - - -");
}

void Frontend::labels_pause() {
  mvwprintw(pause, 7, 15, " \\ (~ _ ~) /");

  mvwprintw(pause, 10, 16, "- - - - - -");
  mvwprintw(pause, 11, 16, " P A U S E ");
  mvwprintw(pause, 12, 16, "- - - - - -");
  pause_continue();
  pause_exit();
}

void Frontend::pause_continue() {
  mvwprintw(pause, 20, 13, "- - - - - - - - -");
  mvwprintw(pause, 21, 13, "C O N T I N U E ?");
  mvwprintw(pause, 22, 13, "- - - - - - - - -");
}

void Frontend::pause_exit() {
  mvwprintw(pause, 24, 13, "- - - - - - - - -");
  mvwprintw(pause, 25, 13, "     E X I T     ");
  mvwprintw(pause, 26, 13, "- - - - - - - - -");
}

void Frontend::game_ov_labels() {
  mvwprintw(game_ov, 10, 14, " F O R  Y O U ");
  mvwprintw(game_ov, 12, 13, " T H E  G A M E ");
  wattron(game_ov, COLOR_PAIR(7));
  mvwprintw(game_ov, 14, 14, " I S  O V E R ");
  wattroff(game_ov, COLOR_PAIR(7));
  mvwprintw(game_ov, 26, 15, " S C O R E ");
  mvwprintw(game_ov, 39, 12, "press 'q' to exit");
}

///////////-----------COLORS------------///////////
void Frontend::initialization_of_colors() {
  start_color();
  // 1 - номер пары  2 - символов 3 -фон
  init_color(COLOR_BLACK, 0, 100, 300);  //темно синий
  init_color(COLOR_RED, 500, 0, 0);      //темно красный

  init_pair(1, COLOR_BLACK, COLOR_BLACK);  //фон
  init_pair(2, COLOR_BLUE, COLOR_BLUE);    //змейка

  init_pair(3, COLOR_WHITE, COLOR_WHITE);  // яблоко  + кнопки + рамки

  //     пары для меню
  init_pair(4, COLOR_WHITE, COLOR_BLACK);  //фон + рамка
  init_pair(5, COLOR_BLACK, COLOR_WHITE);  //горящая кнопка
  init_pair(7, COLOR_RED, COLOR_RED);
}

}  // namespace s21
