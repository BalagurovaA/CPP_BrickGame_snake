GCC = gcc
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

# ----------------------------------------------------- S N A K E ----------------------------------------------------- #

install_snake:
	$(GCC) $(CPPFLAGS) --coverage $(SNAKE_SOURSES_BACK) $(SNAKE_SOURSES_FRONT) -o my_snake -lncurses -lstdc++ $(det_OS)
	./my_snake

install_desktop:
	$(my_inst)

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