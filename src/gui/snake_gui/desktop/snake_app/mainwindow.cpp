#include "mainwindow.h"
using namespace s21;

//конструктор
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
 setFixedSize(610, 601);
 state = BEGIN;
 menu_widget();
 timer_spawn_apple = new QTimer(this);
 timer_spawn_apple->start(10);
 connect(timer_spawn_apple, &QTimer::timeout, this, &MainWindow::onSpawnTimerTimeout);
// old_record = 0;
 timer_move = new QTimer(this);
 q_level_update(&state);
 updateMoveTimer();
 connect(timer_move, &QTimer::timeout, this, &MainWindow::onMoveTimerTimeout);

 update();
};

///////////-----------CONTROLLER------------///////////

void MainWindow::onSpawnTimerTimeout() {
    snake_the_game_q();
    update();
}

void MainWindow::onMoveTimerTimeout() {
    q_snake.control_moving();
    update();
}
void MainWindow::updateMoveTimer() {
     timer_move->start(q_snake.getter_speed());
     update();
}



void MainWindow::snake_the_game_q() {
    q_snake.set_record(readFile());
    q_level_update(&state);

    if(state == BEGIN) {
        q_snake.set_prev_code(q_snake.get_code());
        q_snake.spawn_snake_field();
        state = SPAWN;
    }
    else if(state == SPAWN) {
        q_snake.spawn_apple();
        state = MOVING;
    } else if(state == MOVING) {
        if( q_snake.get_border_flag() != 1 && q_snake.check_the_head() == 1) {
            state = ATTACHING;
        }

} else if(state == ATTACHING) {
        updateMoveTimer();
        q_snake.rising_snake();
        state = SPAWN;


    } else  {
        state = GAMEOVER;
        writeFile();
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
    else if(e->key() == Qt::Key_P) {
     timer_move->stop();
    } else if(e->key() == Qt::Key_S) {
         updateMoveTimer();
    }

    } else {
        state = GAMEOVER;
        gameov_Widget();
    }

}


///////////-----------FRONTEND------------///////////

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    painter.begin(this);
    QColor my_grey(215, 231, 247);
    painter.fillRect(rect(), my_grey);
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
 int maxx = 200;
 QString beauty = "---------------";
 QString score_text = "S C O R E";
 QString level_text = "L E V E L";
 QString speed_text = "S P E E D";
 QString record_text = "R E C O R D";
 QString max_text = "M A X I M U M";


 painter->drawText(QPoint(420, 100), level_text);
 painter->drawText(QPoint(410, 110), beauty);
 painter->drawText(QPoint(455, 125), QString::number(level));

 painter->drawText(QPoint(420, 160), speed_text);
 painter->drawText(QPoint(410, 170), beauty);
 painter->drawText(QPoint(440, 185), QString::number(speed));

 painter->drawText(QPoint(410, 220), record_text);
 painter->drawText(QPoint(410, 230), beauty);
 painter->drawText(QPoint(445, 245), QString::number(record));

 painter->drawText(QPoint(420, 280), score_text);
 painter->drawText(QPoint(410, 290), beauty);
 painter->drawText(QPoint(455, 305), QString::number(score));

 painter->drawText(QPoint(400, 340), max_text);
 painter->drawText(QPoint(410, 350), beauty);
 painter->drawText(QPoint(445, 365), QString::number(maxx));

 update();
}


//-----------------------ENDWIN WIDGET-----------------------//
void:: MainWindow::gameov_Widget() {
    end_w  = new QWidget(this);
    end_w->setStyleSheet("background-color: rgb(215, 231, 247);");
    setFixedSize(610, 601);
    setCentralWidget(end_w);

    QLabel *label = new QLabel(end_w);
    QLabel *label_G = new QLabel(end_w);
    QLabel *label_IO = new QLabel(end_w);
    QLabel *label_score = new QLabel(end_w);
    QLabel *s = new QLabel(end_w);
    int score = q_snake.get_score();

    QFont font = label->font();
    font.setPointSize(30);

    label->setFont(font);
    label->setText("F O R  Y O U");
    label->setGeometry(215, 100, 200, 30);

    label_G->setText("T H E  G A M E");
    label_G->setGeometry(200, 145, 200, 30);
    label_G->setFont(font);

    label_IO->setText("I S  O V E R");
    label_IO->setStyleSheet("background-color:rgb(156, 13, 3); color: white;");
    label_IO->setGeometry(220, 200, 150, 30);
    label_IO->setFont(font);

    label_score->setText("S C O R E");
    label_score->setGeometry(235, 400, 150, 30);
    label_score->setFont(font);

    s->setText(QString::number(score));
    s->setGeometry(290, 445, 150, 30);
    s->setFont(font);
    update();
}

//-----------------------MENU WIDGETS-----------------------//

void MainWindow::menu_widget()
{
   menu_w = new QWidget(this);
   start_butt = new QPushButton("start");

   start_layout = new QVBoxLayout;

   QLabel *label = new QLabel(menu_w);

   menu_w->setStyleSheet("background-color: rgb(215, 231, 247);");
   setFixedSize(610, 601);
   setCentralWidget(menu_w);

   start_butt->setFixedSize(100, 50);
   start_layout->addWidget(start_butt, 0, Qt::AlignCenter);
   menu_w->setLayout(start_layout);

   QFont font = label->font();
   font.setPointSize(60);

   label->setFont(font);
   label->setText("S N A K E");
   label->setGeometry(190, 100, 400, 60);



    connect(start_butt, &QPushButton::clicked, this, &::MainWindow::ClickedSlot_Start);
}


void MainWindow::ClickedSlot_Start()
{
 delete menu_w;
 menu_w = nullptr;

}



///////////-----------FILES------------///////////
int MainWindow::readFile() {
    bool ok;
    QString homePath = QDir::homePath();
    QString filePath = homePath + "/Record.txt";

    QFile file(filePath);
     file.open(QIODevice::ReadOnly | QIODevice::Text);

     if(file.isOpen()) {

         qDebug() << "ФАЙЛ ОТКРЫТ";
     }

    if(file.isOpen()) {
        QTextStream in(&file);
        while(!in.atEnd()) {
            QString line = in.readLine();
            old_record = line.toInt(&ok);
//            qDebug() << "ФАЙЛ ОТКРЫТ";
            qDebug()<< line;

        }
        q_snake.set_record(old_record);
    }

    else {
        qDebug() << "не открыл";
    }




    file.close();
    return old_record;
}

void MainWindow::writeFile() {
    QString homePath = QDir::homePath();
    QString filePath = homePath + "/Record.txt";
    QFile file(filePath);
    QTextStream out(&file);
    if(q_snake.get_score() > old_record) {
        q_snake.set_record(q_snake.get_score());
    }
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if(file.exists(filePath)) {
    out << q_snake.get_record();
    }
    qDebug() << q_snake.get_score();
    file.close();
}


//-----------------------LEVEL-----------------------//
void MainWindow::q_level_update(int *state) {

if(q_snake.get_level() < 10 && q_snake.get_level() >= 0) {
    int lvl = q_snake.get_score() / 5;
    q_snake.set_level(lvl);
}

else {

    *state = GAMEOVER;
}

q_snake.set_speed(1000 - (q_snake.get_level() * 100));
}


MainWindow::~MainWindow()

{

}



