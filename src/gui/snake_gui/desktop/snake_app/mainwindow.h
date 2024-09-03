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
#include <QDir>
#include <QMessageBox>
#include <QLabel>
#include <filesystem>


#include "../../../../brick_game/snake/snake_backend.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
QWidget *end_w;
QWidget *menu_w;

QPushButton *start_butt;

QVBoxLayout *start_layout;


QTimer *timer_spawn_apple;
QTimer *timer_move;
QTimer *timer_pause;


QPainter painter;
int old_record;
int state;

private slots:
    void ClickedSlot_Start();
    void onSpawnTimerTimeout();
    void onMoveTimerTimeout();
//    void onPauseTimerTimeout();
    void updateMoveTimer();

protected:
    void closeEvent(QCloseEvent *event) override {
            if (QMessageBox::question(this, "Уходишь?", "Уходишь?") == QMessageBox::Yes) {
                writeFile();
                event->accept();
            } else {
                event->ignore();
            }
    }

public:
//    std::filesystem::path absolutePath = std::filesystem::absolute("s_score.txt");

    const QString fileName ="./../../../../../brick_game/snake/s_score.txt";
//    const QString fileName ="./../../../../../../../s_score.txt";
    void writeFile();
    int readFile();

    void q_level_update(int *state);

    MainWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void snake_the_game_q();


    s21::Snake q_snake;
    void q_print_field(QPainter *painter);
    void q_add_win(QPainter *painter);
    void gameov_Widget();
    void menu_widget();
    ~MainWindow();
};







#endif // MAINWINDOW_H


