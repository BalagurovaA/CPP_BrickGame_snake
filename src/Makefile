GCC = gcc
C_FLAGS = -Wall -Werror -Wextra -std=c11
CPP_FLAGS = -Wall -Werror -Wextra -std=c++17
C = -std=c11

# sourses snake
SNAKE_SOURSES_BACK = ./brick_game/snake/*.cc
SNAKE_SOURSES_FRONT = ./gui/snake_gui/console/*.cc
SNAKE_SCORE = ./brick_game/snake/s_score.txt
SNAKE_BACK_H = ./brick_game/snake/*.h
SNAKE_FRONT_CONSOLE_H = ./gui/snake_gui/console/snake_frontend.h

SNAKE_TEST = ./my_test/tests_snake_back.cc
SNAKE_TEST_BACK = ./brick_game/snake/snake_backend.cc \

# sourses tetris
TETRIS_SOURSES_BACK = ./brick_game/tetris/*.c
TETRIS_SOURSES_FRONT = ./gui/tetris_gui/tetris_frontend.c
TETRIS_SCORE = ./brick_game/tetris/t_score.txt
TETRIS_BACK_H = ./brick_game/tetris/*.h
TETRIS_FRONT_H = ./gui/tetris_gui/tetris_frontend.h

TETRIS_TEST = ./my_test/tests_tetris_back.c

TETRIS_TEST_BACK = ./brick_game/tetris/tetris_backend.c \
				./brick_game/tetris/tetris_controller.c \
				./brick_game/tetris/tetris_figures.c \

OS = $(shell uname)

ifeq ($(OS),Linux)
    det_OS = -lcheck -lm -lrt -lpthread -lsubunit
	project = snake_app.pro
	inst_s = cd gui && cd snake_gui && cd desktop && cd snake_app && qmake && make && rm Makefile && mkdir -p ../../../../build && mv $(project) ../../../../build/

else
    det_OS = -lcheck -lm -lpthread
	project = snake_app.app
	my_inst = cd ./gui/snake_gui/desktop/snake_app && qmake snake_app.pro && make && rm Makefile && mkdir -p ../../../../build && mv snake_app.app/$(UI_BIN) ../../../../build/

endif

# ----------------------------------------------------- T E T R I S ----------------------------------------------------- #
tetris_all : clean_tetris dist_tetris gcov_report_tetris fix_clang_tetris check_tetris dvi_tetris run_tetris

install_tetris: clean_tetris uninstall_tetris
	$(GCC) $(C_FLAGS) $(TETRIS_SOURSES_BACK) $(TETRIS_SOURSES_FRONT) -o my_tetris -lncurses $(det_OS)

run_tetris : install_tetris
	./my_tetris

uninstall_tetris: 
	rm -rf my_tetris

dvi_tetris:
	open ./documentation/documentation_tetris.md

dist_tetris: clean_tetris install_tetris
	mkdir dist_tetris
	tar -czvf dist_tetris/tetris_the_archive.tgz $(TETRIS_SOURSES_BACK) $(TETRIS_SOURSES_FRONT) $(TETRIS_TEST) $(TETRIS_SCORE) $(TETRIS_BACK_H) $(TETRIS_FRONT_H) ./documentation/documentation_tetris.md Makefile

test_tetris:
	$(GCC) $(CFLAGS) --coverage $(TETRIS_TEST_BACK) $(TETRIS_SOURSES_FRONT) $(TETRIS_TEST) -lncurses -o test_tetris $(det_OS)
	./test_tetris

gcov_report_tetris: test_tetris
	./test_tetris
	lcov -t "result" -o res.info -c -d .
	genhtml -o report res.info
	open report/index.html

fix_clang_tetris:
	clang-format -style=Google -i $(TETRIS_SOURSES_BACK)
	clang-format -style=Google -i $(TETRIS_SOURSES_FRONT)
	clang-format -style=Google -i $(TETRIS_BACK_H)
	clang-format -style=Google -i $(TETRIS_FRONT_H)
	clang-format -style=Google -i $(TETRIS_TEST)
	

check_tetris: fix_clang_tetris
	clang-format -style=Google -n $(TETRIS_SOURSES_BACK)
	clang-format -style=Google -n $(TETRIS_SOURSES_FRONT)
	clang-format -style=Google -n $(TETRIS_BACK_H)
	clang-format -style=Google -n $(TETRIS_FRONT_H)
	clang-format -style=Google -n $(TETRIS_TEST)


clean_tetris:
	rm -rf dist_tetris
	rm -rf ./test_tetris ./my_tetris
	rm -rf gcov_report report *.gc* *.o *.info *.a test.dSYM test dist compose-dev.yaml 

# ----------------------------------------------------- S N A K E ----------------------------------------------------- #

install_snake:
	$(GCC) $(CPPFLAGS) --coverage $(SNAKE_SOURSES_BACK) $(SNAKE_SOURSES_FRONT) -o my_snake -lncurses -lstdc++ $(det_OS)

install_desktop:
	$(my_inst)

run_snake_console:
	./my_snake

dvi_snake:
	open ./documentation/documentation_snake.md

dist_snake:
	mkdir dist_snake
	tar -czvf dist_snake/snake_the_archive.tgz $(SNAKE_SOURSES_BACK) $(SNAKE_SOURSES_FRONT) $(SNAKE_SCORE) $(SNAKE_BACK_H) $(SNAKE_FRONT_CONSOLE_H) $(SNAKE_TEST) ./documentation/documentation_snake.md Makefile

test_snake:
	$(GCC) $(CPP_FLAGS) --coverage $(SNAKE_TEST_BACK) $(SNAKE_TEST) -lstdc++ -lncurses -o test_snake -lgtest $(det_OS)
	./test_snake

gcov_report_snake: clean_snake test_snake
	lcov -t "result" -o res.info  --ignore-errors inconsistent -c -d .
	lcov --remove res.info /c++/13 /usr/local/include/gtest -o filtered_coverage.info
	genhtml -o report filtered_coverage.info
	open report/index.html

fix_clang_snake:
	clang-format -style=Google -i $(SNAKE_SOURSES_BACK)
	clang-format -style=Google -i $(SNAKE_SOURSES_FRONT)
	clang-format -style=Google -i $(SNAKE_BACK_H)
	clang-format -style=Google -i $(SNAKE_FRONT_CONSOLE_H)
	clang-format -style=Google -i $(SNAKE_TEST)

clang_snake: fix_clang_snake
	clang-format -style=Google -n $(SNAKE_SOURSES_BACK)
	clang-format -style=Google -n $(SNAKE_SOURSES_FRONT)
	clang-format -style=Google -n $(SNAKE_BACK_H)
	clang-format -style=Google -n $(SNAKE_FRONT_CONSOLE_H)
	clang-format -style=Google -n $(SNAKE_TEST)

clean_snake:
	rm -rf ./build ./qt_fr
	rm -rf ./build/snake_app.pro
	rm -rf ./build/snake_app.app
	rm -rf test_snake my_snake 
	rm -rf ./my_snake-snake_backend.gcda
	rm -rf report *.gc* *.o *.info *.a test.dSYM test gch ./snake_app.pro/.qmake.stash compose-dev.yaml 
	rm -rf gcov_report report *.gc* *.o *.info *.a test.dSYM test dist compose-dev.yaml

clean_all: clean_snake clean_tetris
	rm -rf test_snake my_snake 
	rm -rf gcov_report report *.gc* *.o *.info *.a test.dSYM test dist compose-dev.yaml

	rm -rf ./test_tetris ./my_tetris
	rm -rf gcov_report report *.gc* *.o *.info *.a test.dSYM test dist compose-dev.yaml 