#include "ellipse.h"

Ellipse::Ellipse(QPointF point) : Figure(point)
{
    Q_UNUSED(point)
}

Ellipse::~Ellipse()
{

}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);

    QRectF rect = QRectF(getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x(),
                getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y(),
                qAbs(getEndPoint().x() - getStartPoint().x()),
                qAbs(getEndPoint().y() - getStartPoint().y()));

    painter->drawEllipse(rect);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

