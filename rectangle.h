#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "figure.h"
#include <QGraphicsObject>

class Rectangle : public Figure
{
    Q_OBJECT

public:
    explicit Rectangle(QPointF point);
    ~Rectangle();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


#endif // RECTANGLE_H
