#ifndef ADD_FIELD_H
#define ADD_FIELD_H

#include <QWidget>
#include <QPainter>

class add_field : public QWidget
{
public:
    add_field();
protected:
    void paintEvent(QPaintEvent *e) override;
};



#endif // ADD_FIELD_H
