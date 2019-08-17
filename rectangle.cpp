#include "rectangle.h"

Rectangle::Rectangle(QPointF point) : Figure(point)
{
    Q_UNUSED(point)
}

Rectangle::~Rectangle()
{

}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = QRectF(getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x(),
                getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y(),
                qAbs(getEndPoint().x() - getStartPoint().x()),
                qAbs(getEndPoint().y() - getStartPoint().y()));

    painter->setPen(Qt::black);
    painter->setBrush(Qt::red);
    painter->drawRect(rect);

    Q_UNUSED(option)
    Q_UNUSED(widget)
}
