#include "figure.h"

Figure::Figure(QPointF point, QObject *parent) :
    QGraphicsObject()
{
    this->setStartPoint(mapFromScene(point));
    this->setEndPoint(mapFromScene(point));

    Q_UNUSED(parent)
}

Figure::~Figure()
{

}

void Figure::setStartPoint(const QPointF point)
{
    start_point = mapFromScene(point);
}

void Figure::setEndPoint(const QPointF point)
{
    end_point = mapFromScene(point);
}

QPointF Figure::getStartPoint() const
{
    return start_point;
}

QPointF Figure::getEndPoint() const
{
    return end_point;
}

QRectF Figure::boundingRect() const
{
    return QRectF((getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x()),
                  (getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y()),
                  qAbs(getEndPoint().x() - getStartPoint().x()),
                  qAbs(getEndPoint().y() - getStartPoint().y()));
}
void Figure::updatePoints()
{

}
void Figure::addLine(QGraphicsLineItem *line, bool is_first)
{
/*
    if(is_first)
        line->setLine(QLineF(boundingRect().center(), line->line().p2()));
    else
        line->setLine(QLineF(line->line().p1(), boundingRect().center()));
*/
    added_lines.push_back({line, is_first});
    moveLineToCenter(QPointF());
}

QVariant Figure::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF new_pos = value.toPointF();
        //updatePoints();
        moveLineToCenter(new_pos);
    }
    return QGraphicsItem::itemChange(change, value);
}

void Figure::moveLineToCenter(QPointF new_pos)
{
    if(!added_lines.isEmpty())
    {
        qreal x_offset = boundingRect().x() + boundingRect().width()/2;
        qreal y_offset = boundingRect().y() + boundingRect().height()/2;

        QPointF newCenterPos = QPointF(new_pos.x() + x_offset, new_pos.y() + y_offset);

        for (auto &line : added_lines)
        {
            if(line.is_first)
                line.line->setLine(QLineF(newCenterPos, line.line->line().p2()));
            else
            line.line->setLine(QLineF(line.line->line().p1(), newCenterPos));
        }
    }
}
