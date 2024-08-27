#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QFile>

#include "../../brick_game/snake/backend.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
QWidget *start_w;
QTimer *timer_spawn_apple;
QTimer *timer_move;


QPainter painter;
int state;

private slots:
    void onSpawnTimerTimeout();
    void onMoveTimerTimeout();


public:
    const QString fileName ="./../../../../../brick_game/snake/s_score.txt";
    void writeFile(QFile &fileName);
    int readFile(QFile &fileName);

    void q_level_update(int *state);

    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void snake_the_game_q();


    s21::Snake q_snake;


    void q_print_field(QPainter *painter);
    void q_add_win(QPainter *painter);
    void start_Widget();


    ~MainWindow();
};

class q_Frontend : public QWidget {
private:

 public:
        void paintEvent(QPaintEvent *e) override;
        void q_print_field(QPainter *painter);
};





#endif // MAINWINDOW_H


