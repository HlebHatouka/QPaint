#include "shape.h"

Shape::Shape(QPointF point, QObject *parent) :
    QGraphicsObject()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));
    touched = false;

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
}

QPointF Shape::getStartPoint() const
{
    return start_point;
}

QPointF Shape::getEndPoint() const
{
    return end_point;
}

QRectF Shape::boundingRect() const
{
    return QRectF((getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x()),
                  (getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y()),
                  qAbs(getEndPoint().x() - getStartPoint().x()),
                  qAbs(getEndPoint().y() - getStartPoint().y()));
}

void Shape::updatePoints(const QPointF &start)
{
    QPointF new_start_point(start);
    QPointF new_end_point;

    new_end_point.setX(start.x() + boundingRect().x() + boundingRect().width());
    new_end_point.setY(start.y() + boundingRect().y() + boundingRect().height());


    // new_pos.x() + x_offset, new_pos.y() + y_offset

    this->setStartPoint(new_start_point);
    this->setEndPoint(new_end_point);
}

void Shape::updateCenter(const QPointF &new_pos)
{
    qreal x_offset = boundingRect().x() + boundingRect().width()/2;
    qreal y_offset = boundingRect().y() + boundingRect().height()/2;

    this->center = QPointF(new_pos.x() + x_offset, new_pos.y() + y_offset);
}

void Shape::addLine(QGraphicsLineItem *line, bool is_first)
{
    if(!touched)
        updateCenter();

    if(is_first)
        line->setLine(QLineF(center, line->line().p2()));
    else
        line->setLine(QLineF(line->line().p1(), center));

    added_lines.push_back({line, is_first});
    //moveLineToCenter(QPointF());
}

QVariant Shape::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF new_pos = value.toPointF();
        //updatePoints(new_pos);
        touched = true;
        updateCenter(new_pos);
        moveLinesToCenter();
    }
    return QGraphicsItem::itemChange(change, value);
}

void Shape::moveLinesToCenter()
{
    if(!added_lines.isEmpty())
    {
        /*
        qreal x_offset = boundingRect().x() + boundingRect().width()/2;
        qreal y_offset = boundingRect().y() + boundingRect().height()/2;

        QPointF newCenterPos = QPointF(new_pos.x() + x_offset, new_pos.y() + y_offset);
        */
        for (auto &line : added_lines)
        {
            if(line.is_first)
                line.line->setLine(QLineF(center, line.line->line().p2()));
            else
                line.line->setLine(QLineF(line.line->line().p1(), center));
        }
    }
}
