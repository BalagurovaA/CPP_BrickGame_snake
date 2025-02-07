#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;


//    start_widget->show();




  //пример аделины
//  QWidget *wid = new QWidget(&w);
//  wid->resize(1000, 1000);
//  wid->setStyleSheet("color:red");

//  wid->show();

  w.show();
  return a.exec();
}
