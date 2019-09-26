#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QVector>
#include <algorithm>

class Polygon : public Shape
{
    Q_OBJECT

public:
    explicit Polygon(QPointF point);
    ~Polygon();

    void setSide (QGraphicsLineItem *side);

private:
    QPointF left_up_pointRect;
    QPointF right_down_pointRect;
    QVector<QPoint> polygon;
    QVector<QGraphicsLineItem *> sides;

    static bool xPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second);
    static bool yPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second);
    QRectF boundingRect() const override;
    void updatePoints();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // POLYGON_H
