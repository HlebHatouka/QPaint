#ifndef STAR_H
#define STAR_H

#include "figure.h"
#include <QGraphicsObject>
#include <cmath>

class Star : public Figure
{
    Q_OBJECT

public:
    explicit Star(QPointF point);
    ~Star();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // STAR_H
