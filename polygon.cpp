#include "polygon.h"

Polygon::Polygon(QPointF point) : Figure(point)
{
    polygon_ended = false;
    left_up_pointRect = QPointF();
    right_down_pointRect = QPointF();
    polygon = QVector<QPoint>();
    sides = QVector<QGraphicsLineItem *>();
    Q_UNUSED(point)
}

Polygon::~Polygon()
{

}

void Polygon::setSide (QGraphicsLineItem *side)
{
    sides.push_back(side);

    if(sides.size() > 2 && (qAbs((*sides.begin())->line().p1().x() - (*(sides.end()-1))->line().p2().x()) < 10)
                        && (qAbs((*sides.begin())->line().p1().y() - (*(sides.end()-1))->line().p2().y()) < 10))
    {
        (*(sides.end()-1))->line().p2() = (*sides.begin())->line().p1();
        //(*sides.begin())->line().p1() = (*(sides.end()-1))->line().p2();
        for (auto &side : sides)
            polygon << side->line().p2().toPoint();
        polygon_ended = true;

    }
    updatePoints();
}

bool Polygon::isEnded()
{
    return polygon_ended;
}

void Polygon::setEndPoint(const QPointF point)
{
    this->end_point = point;
}

bool Polygon::xPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second)
{
    return first->line().p2().x() < second->line().p2().x();
}

bool Polygon::yPredicate(const QGraphicsLineItem *first, const QGraphicsLineItem *second)
{
    return first->line().p2().y() < second->line().p2().y();
}

QRectF Polygon::boundingRect() const
{
    return QRectF(left_up_pointRect, right_down_pointRect);
}

void Polygon::updatePoints()
{
    QGraphicsLineItem *p2_with_min_x = *std::min_element(sides.begin(), sides.end(), Polygon::xPredicate);
    QGraphicsLineItem *p2_with_min_y = *std::min_element(sides.begin(), sides.end(), Polygon::yPredicate);
    QGraphicsLineItem *p2_with_max_x = *std::max_element(sides.begin(), sides.end(), Polygon::xPredicate);
    QGraphicsLineItem *p2_with_max_y = *std::max_element(sides.begin(), sides.end(), Polygon::yPredicate);

    left_up_pointRect = QPointF(p2_with_min_x->line().p2().x(), p2_with_min_y->line().p2().y());
    right_down_pointRect = QPointF(p2_with_max_x->line().p2().x(), p2_with_max_y->line().p2().y());

    //boundingRect();
}

void Polygon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::gray);
    painter->drawPolygon(polygon);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
