#include "shape.h"
#include <iostream>

Shape::Shape(QPointF point, QObject *parent) :
    QGraphicsObject(), is_ended(false)
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    Q_UNUSED(parent)
}

Shape::~Shape()
{

}

void Shape::setStartPoint(const QPointF &point)
{
    start_point = point;
}

void Shape::setEndPoint(const QPointF &point)
{
    end_point = point;
    updateCenter();
}

QPointF Shape::getStartPoint() const
{
    return start_point;
}

QPointF Shape::getEndPoint() const
{
    return end_point;
}

bool Shape::isEnded() const
{
    return is_ended;
}

QRectF Shape::boundingRect() const
{
    return QRectF((getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x()),
                  (getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y()),
                  qAbs(getEndPoint().x() - getStartPoint().x()),
                  qAbs(getEndPoint().y() - getStartPoint().y()));
}

void Shape::updateCenter(const QPointF &new_pos)
{
    qreal x_offset = boundingRect().x() + boundingRect().width()/2;
    qreal y_offset = boundingRect().y() + boundingRect().height()/2;

    this->center = QPointF(new_pos.x() + x_offset, new_pos.y() + y_offset);
}

void Shape::addLine(QGraphicsLineItem *line, bool is_first)
{
    if(is_first)
        line->setLine(QLineF(center, line->line().p2()));
    else
        line->setLine(QLineF(line->line().p1(), center));

    added_lines.push_back({line, is_first});
}

QVariant Shape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF new_pos = value.toPointF();
        updateCenter(new_pos);
        moveLinesToCenter();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Shape::moveLinesToCenter()
{
    if(!added_lines.isEmpty())
    {
        for (auto &line : added_lines)
        {
            if(line.is_first)
                line.line->setLine(QLineF(center, line.line->line().p2()));
            else
                line.line->setLine(QLineF(line.line->line().p1(), center));
        }
    }
}
