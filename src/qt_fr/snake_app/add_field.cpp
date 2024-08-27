#include "add_field.h"
#include <QPainter>
#include <QWidget>

add_field::add_field() { setFixedSize(300, 50); }

void add_field::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter painter;
  painter.begin(this);
  painter.drawRect(5, 5, width() - 10, height() - 10);
  painter.setFont(QFont("Calibri", 14, 100));
  painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter,
                   " S C O R E ");
  painter.end();
}
