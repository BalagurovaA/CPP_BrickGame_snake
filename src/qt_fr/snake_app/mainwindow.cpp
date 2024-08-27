#include "mainwindow.h"
using namespace s21;

//конструктор
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
 setFixedSize(610, 601);
 state = BEGIN;
 timer_spawn_apple = new QTimer(this);
 timer_spawn_apple->start(10);
 connect(timer_spawn_apple, &QTimer::timeout, this, &MainWindow::onSpawnTimerTimeout);

 timer_move = new QTimer(this);
 timer_move->start(1000);

 connect(timer_move, &QTimer::timeout, this, &MainWindow::onMoveTimerTimeout);


 snake_the_game_q();
 update();
};

///////////-----------CONTROLLER------------///////////

void MainWindow::onSpawnTimerTimeout() {
    snake_the_game_q();
    update();
}

void MainWindow::onMoveTimerTimeout() {
    q_snake.control_moving();
}

void MainWindow::snake_the_game_q()
{

    QFile score_file(fileName);
    q_snake.set_record(readFile(score_file));
    q_level_update(&state);
    if(state == BEGIN) {
        q_snake.set_prev_code(q_snake.get_code());
        q_snake.spawn_snake_field();
        state = SPAWN;
    }
    else if(state == SPAWN) {
         qDebug() << "ЗАСПАВНИЛ ЯБЛОКО";
        q_snake.spawn_apple();
        state = MOVING;
    } else if(state == MOVING) {
        if( q_snake.get_border_flag() != 1 && q_snake.check_the_head() == 1) {
            state = ATTACHING;
        }

} else if(state == ATTACHING) {
        qDebug() << "СЪЕЛ ЯБЛОКО";
        q_snake.rising_snake();
        state = SPAWN;

    } else  {
        state = GAMEOVER;
        writeFile(score_file);
        exit(1);
    }

update();
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(q_snake.get_border_flag() != 1) {

    if(e->key() == Qt::Key_Up) {
    q_snake.fsm_up();
    }
    else if(e->key() == Qt::Key_Down) {
    q_snake.fsm_down();
    }
    else if(e->key() == Qt::Key_Left) {
     q_snake.fsm_left();
    }
    else if(e->key() == Qt::Key_Right) {
     q_snake.fsm_right();
    }
} else {
        state = GAMEOVER;
    }

}


///////////-----------FRONTEND------------///////////

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    painter.begin(this);
    QColor lightBlue(203, 206, 214);
    painter.fillRect(rect(), lightBlue);
    painter.drawRect(300,0, 300, 600);
    q_print_field(&painter);
    q_add_win(&painter);
    painter.end();
}

void MainWindow::q_print_field(QPainter *painter) {
        QBrush brush(Qt::white);
    for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 10; j++) {
              if(q_snake.get_field(i, j) == 0) {
                  QColor my_grey(215, 231, 247);
                  QBrush brush(my_grey);
                  painter->setBrush(brush);
                  painter->drawRect(j * 30, i * 30, 30, 60);

              }
              else if(q_snake.get_field(i, j) == 1) {
                  QColor my_blue(6, 105, 150);
                  painter->setBrush(my_blue);
                  painter->drawRect(j * 30, i * 30, 30, 60);
              }
              else if(q_snake.get_field(i, j) == 3) {
                  QColor my_red(156, 13, 3);
                  brush.setColor(my_red);
                  painter->setBrush(brush);
                  painter->drawRect(j * 30, i * 30, 30, 60);
              }
          }

    }
    update();
}

void MainWindow::q_add_win(QPainter *painter)
{
  painter ->setPen(Qt::black);
  painter->setFont(QFont("Times New Roman", 18));

 int score = q_snake.get_score();
 int level = q_snake.get_level();
 int speed = q_snake.getter_speed();
 int record = q_snake.get_record();
 QString beauty = "---------------";
 QString score_text = "S C O R E";
 QString level_text = "L E V E L";
 QString speed_text = "S P E E D";
 QString record_text = "R E C O R D";


 painter->drawText(QPoint(420, 100), level_text);
 painter->drawText(QPoint(410, 110), beauty);
 painter->drawText(QPoint(455, 125), QString::number(level));

 painter->drawText(QPoint(420, 160), speed_text);
 painter->drawText(QPoint(410, 170), beauty);
 painter->drawText(QPoint(440, 185), QString::number(speed));

 painter->drawText(QPoint(410, 220), record_text);
 painter->drawText(QPoint(410, 230), beauty);
 painter->drawText(QPoint(455, 245), QString::number(record));

 painter->drawText(QPoint(420, 280), score_text);
 painter->drawText(QPoint(410, 290), beauty);
 painter->drawText(QPoint(455, 305), QString::number(score));


 update();
}
///////////-----------FILES------------///////////
int MainWindow::readFile(QFile &file) {
    bool ok;

    int old_record = 0;

     file.open(QIODevice::ReadOnly);
    if(file.isOpen() && file.exists()) {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            old_record = line.toInt(&ok);
        }
        q_snake.set_record(old_record);
    }
    else {
        qDebug() << "не открыл";
    }
    file.close();
    return old_record;
}

void MainWindow::writeFile(QFile &file) {
    QTextStream out(&file);

    if(q_snake.get_score() > q_snake.get_record()) {
        q_snake.set_record(q_snake.get_score());
    }

    file.open(QIODevice::Text);
    if(file.exists(fileName)) {
    out << q_snake.get_record();
    } else {
        qDebug() << "НЕ СУЩЕСТВУЕТ";
    }
    file.close();
}




void MainWindow::q_level_update(int *state) {
if(q_snake.get_level() < 10 && q_snake.get_level() >= 0) {
    int lvl = q_snake.get_score() / 5;
    q_snake.set_level(lvl);
}

else {
    qDebug() << "закончил";
    *state = GAMEOVER;
}
}


MainWindow::~MainWindow()
{

}


