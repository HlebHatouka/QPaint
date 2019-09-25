#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <QGraphicsObject>
#include <QVector>
#include <algorithm>
//#include <bits/stdc++.h>

class Polygon : public Shape
{
    Q_OBJECT

public:
    explicit Polygon(QPointF point);
    ~Polygon();

    void setSide (QGraphicsLineItem *side);
    bool isEnded();

private:
    bool polygon_ended;
    QPointF left_up_pointRect;
    QPointF right_down_pointRect;
    QVector<QPoint> polygon;
    QVector<QGraphicsLineItem *> sides;

    void setEndPoint(const QPointF &point) override;
    static bool xPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second);
    static bool yPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second);
    QRectF boundingRect() const override;
    void updatePoints(const QPointF &start) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // POLYGON_H
