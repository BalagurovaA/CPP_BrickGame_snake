#include <gtest/gtest.h>

#include "./../brick_game/snake/snake_backend.h"
using namespace s21;

// create field
TEST(EQTest, EqTest_1) {
  Snake tsnake;
  tsnake.create_field();
  int check_matrix[HEIGHT][WIDTH] = {0};
  EXPECT_EQ(tsnake.get_field(4, 8), check_matrix[4][8]);
  EXPECT_EQ(tsnake.get_field(8, 4), check_matrix[4][8]);
  EXPECT_EQ(tsnake.get_field(11, 6), check_matrix[4][8]);
}

// spawn snake field
TEST(EQTest, EqTest_2) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  int check_matrix[HEIGHT][WIDTH] = {0};
  check_matrix[1][7] = 1;
  check_matrix[2][7] = 1;
  check_matrix[3][7] = 1;
  check_matrix[4][7] = 1;

  EXPECT_EQ(tsnake.get_field(1, 7), check_matrix[1][7]);
  EXPECT_EQ(tsnake.get_field(2, 7), check_matrix[2][7]);
  EXPECT_EQ(tsnake.get_field(3, 7), check_matrix[3][7]);
  EXPECT_EQ(tsnake.get_field(4, 7), check_matrix[4][7]);
}

// accel down
TEST(EQTest, EqTest_3) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.accel_down();
  int check_matrix[HEIGHT][WIDTH] = {0};
  check_matrix[2][7] = 1;
  check_matrix[3][7] = 1;
  check_matrix[4][7] = 1;
  check_matrix[5][7] = 1;

  EXPECT_EQ(tsnake.get_field(2, 7), check_matrix[2][7]);
  EXPECT_EQ(tsnake.get_field(3, 7), check_matrix[3][7]);
  EXPECT_EQ(tsnake.get_field(4, 7), check_matrix[4][7]);
  EXPECT_EQ(tsnake.get_field(5, 7), check_matrix[5][7]);

  tsnake.accel_down();
  tsnake.accel_down();
  tsnake.accel_down();

  check_matrix[5][7] = 1;
  check_matrix[6][7] = 1;
  check_matrix[7][7] = 1;
  check_matrix[8][7] = 1;

  EXPECT_EQ(tsnake.get_field(5, 7), check_matrix[5][7]);
  EXPECT_EQ(tsnake.get_field(6, 7), check_matrix[6][7]);
  EXPECT_EQ(tsnake.get_field(7, 7), check_matrix[7][7]);
  EXPECT_EQ(tsnake.get_field(8, 7), check_matrix[8][7]);

  Snake tsnake_b;
  tsnake_b.create_field();
  tsnake_b.spawn_snake_field();
  tsnake_b.accel_down();
  for (int i = 4; i < HEIGHT; i++) {
    tsnake_b.accel_down();
  }
  EXPECT_EQ(tsnake.get_field(20, 7), 1);
}

// accel up
TEST(EQTest, EqTest_4) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.accel_left();
  tsnake.accel_up();

  int check_matrix[HEIGHT][WIDTH] = {0};
  check_matrix[3][6] = 1;
  check_matrix[3][7] = 1;
  check_matrix[4][6] = 1;
  check_matrix[4][7] = 1;

  EXPECT_EQ(tsnake.get_field(3, 6), check_matrix[3][6]);
  EXPECT_EQ(tsnake.get_field(3, 7), check_matrix[3][7]);
  EXPECT_EQ(tsnake.get_field(4, 6), check_matrix[4][6]);
  EXPECT_EQ(tsnake.get_field(4, 7), check_matrix[4][7]);

  tsnake.accel_up();
  tsnake.accel_up();

  check_matrix[1][6] = 1;
  check_matrix[2][6] = 1;
  check_matrix[3][6] = 1;
  check_matrix[4][6] = 1;

  EXPECT_EQ(tsnake.get_field(1, 6), check_matrix[1][6]);
  EXPECT_EQ(tsnake.get_field(2, 6), check_matrix[2][6]);
  EXPECT_EQ(tsnake.get_field(3, 6), check_matrix[3][6]);
  EXPECT_EQ(tsnake.get_field(4, 6), check_matrix[4][6]);
}

// accel left
TEST(EQTest, EqTest_5) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.accel_left();

  int check_matrix[HEIGHT][WIDTH] = {0};
  check_matrix[4][6] = 1;
  check_matrix[4][7] = 1;
  check_matrix[3][7] = 1;
  check_matrix[2][7] = 1;

  EXPECT_EQ(tsnake.get_field(4, 6), check_matrix[4][6]);
  EXPECT_EQ(tsnake.get_field(4, 7), check_matrix[4][7]);
  EXPECT_EQ(tsnake.get_field(3, 7), check_matrix[3][7]);
  EXPECT_EQ(tsnake.get_field(2, 7), check_matrix[2][7]);

  tsnake.accel_left();
  tsnake.accel_left();

  check_matrix[4][4] = 1;
  check_matrix[4][5] = 1;
  check_matrix[4][6] = 1;
  check_matrix[4][7] = 1;

  EXPECT_EQ(tsnake.get_field(4, 4), check_matrix[4][6]);
  EXPECT_EQ(tsnake.get_field(4, 5), check_matrix[4][5]);
  EXPECT_EQ(tsnake.get_field(4, 6), check_matrix[4][6]);
  EXPECT_EQ(tsnake.get_field(4, 7), check_matrix[4][7]);
}

// accel_right
TEST(EQTest, EqTest_6) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.accel_left();
  tsnake.accel_left();
  tsnake.accel_left();
  tsnake.accel_left();
  tsnake.accel_left();
  tsnake.accel_left();
  tsnake.accel_down();
  tsnake.accel_right();

  int check_matrix[HEIGHT][WIDTH] = {0};
  check_matrix[4][1] = 1;
  check_matrix[4][2] = 1;
  check_matrix[5][1] = 1;
  check_matrix[5][2] = 1;

  EXPECT_EQ(tsnake.get_field(4, 1), check_matrix[4][1]);
  EXPECT_EQ(tsnake.get_field(4, 2), check_matrix[4][2]);
  EXPECT_EQ(tsnake.get_field(5, 1), check_matrix[5][1]);
  EXPECT_EQ(tsnake.get_field(5, 2), check_matrix[5][2]);

  tsnake.accel_right();
  tsnake.accel_right();

  check_matrix[5][1] = 1;
  check_matrix[5][2] = 1;
  check_matrix[5][3] = 1;
  check_matrix[5][4] = 1;

  EXPECT_EQ(tsnake.get_field(5, 1), check_matrix[5][1]);
  EXPECT_EQ(tsnake.get_field(5, 2), check_matrix[5][2]);
  EXPECT_EQ(tsnake.get_field(5, 3), check_matrix[5][3]);
  EXPECT_EQ(tsnake.get_field(5, 4), check_matrix[5][4]);
}

// FSM MOVING
TEST(EQTest, EqTest_7) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  int prev_code_tt = MOVE_DOWN;
  EXPECT_EQ(tsnake.get_prev_code(), prev_code_tt);

  Snake tsnake_1;
  tsnake_1.create_field();
  tsnake_1.spawn_snake_field();
  tsnake_1.fsm_left();
  int prev_code_tt_1 = MOVE_L;
  EXPECT_EQ(tsnake_1.get_prev_code(), prev_code_tt_1);

  Snake tsnake_2;
  tsnake_2.create_field();
  tsnake_2.spawn_snake_field();
  tsnake_2.fsm_right();
  int prev_code_tt_2 = MOVE_R;
  EXPECT_EQ(tsnake_2.get_prev_code(), prev_code_tt_2);

  Snake tsnake_3;
  tsnake_3.create_field();
  tsnake_3.spawn_snake_field();
  tsnake_3.fsm_right();
  int prev_code_tt_3 = MOVE_R;
  EXPECT_EQ(tsnake_3.get_prev_code(), prev_code_tt_3);

  Snake tsnake_4;
  tsnake_4.create_field();
  tsnake_4.spawn_snake_field();
  tsnake_4.fsm_down();
  tsnake_4.fsm_left();
  tsnake_4.fsm_up();
  int prev_code_tt_4 = MOVE_UP;
  EXPECT_EQ(tsnake_4.get_prev_code(), prev_code_tt_4);
}

// control_moving
TEST(EQTest, EqTest_8_1) {  /////////////////
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.set_prev_code(MOVE_DOWN);
  tsnake.control_moving();
  EXPECT_EQ(tsnake.get_field(5, 7), 1);

  Snake tsnakeL;
  tsnakeL.create_field();
  tsnakeL.spawn_snake_field();
  tsnakeL.set_prev_code(MOVE_L);
  tsnakeL.control_moving();
  EXPECT_EQ(tsnakeL.get_field(4, 6), 1);

  Snake tsnakeR;
  tsnakeR.create_field();
  tsnakeR.spawn_snake_field();
  tsnakeR.set_prev_code(MOVE_R);
  tsnakeR.control_moving();
  EXPECT_EQ(tsnakeR.get_field(4, 8), 1);
}

/////

// spawn apple
TEST(EQTest, EqTest_8) {
  Snake tsnake;
  int flag = 0;
  tsnake.create_field();
  tsnake.spawn_apple();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (tsnake.get_field(i, j) == 3) {
        flag = 3;
      }
    }
  }
  EXPECT_EQ(flag, 3);
}

// rising snake
TEST(EQTest, EqTest_9) {
  Snake tsnake;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.spawn_apple();
  tsnake.rising_snake();

  EXPECT_EQ(tsnake.get_score(), 0);
}

// check the head
TEST(EQTest, EqTest_10) {
  Snake tsnake;
  int flag = 0;
  tsnake.create_field();
  tsnake.spawn_snake_field();
  tsnake.spawn_apple();
  flag = tsnake.check_the_head();

  EXPECT_EQ(flag, 0);
}

// level_speed_update
TEST(EQTest, EqTest_11) {
  Snake tsnake;
  tsnake.set_score(200);

  int state = BEGIN;
  tsnake.level_speed_update(&state);
  EXPECT_EQ(state, GAMEOVER);

  Snake tsnake_1;
  tsnake_1.set_score(36);
  int state_1 = BEGIN;
  tsnake_1.level_speed_update(&state_1);
  EXPECT_EQ(tsnake_1.getter_speed(), 300);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

// gcc -Wall -Werror -Wextra -std=c++17 --coverage  -lstdc++ -lgtest_main
// -lgtest -lm  tests_back.cc ../brick_game/snake/backend.cc