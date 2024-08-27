#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include "../../brick_game/snake/backend.h"


struct Snake_data {
    int state;
    int code;
    int prev_code;
    int border_flag;

};

class Control;

class Control: public QWidget {

public:

    Control();
    void begin();
    void q_moving(int *border_flag, int *prev_code, int *code, int *state, s21::Snake &snake);

     void initialization_of_data(Snake_data newData);

    QTimer * timer = new QTimer;

    friend class s21::Snake;


protected:

    void keyPressEvent(QKeyEvent *e) override;

};

#endif // CONTROLLER_H
