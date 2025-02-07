#ifndef FIG_H
#define FIG_H

#include "tetris_backend.h"
///////////------------NEXT FIGURES------------///////////
void next_fig_null(int next_fig[4][4]);
void next_stick(int next_fig[4][4]);
void next_cube(int next_fig[4][4]);
void next_left_wing(int next_fig[4][4]);
void next_right_wing(int next_fig[4][4]);
void next_left_snake(int next_fig[4][4]);
void next_right_snake(int next_fig[4][4]);
void next_pyramide(int next_fig[4][4]);
void next_measure(WINDOW *add_win, int i, int j);
#endif