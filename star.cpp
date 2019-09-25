#include "star.h"

Star::Star(QPointF point) : Shape(point)
{
    Q_UNUSED(point)
}

Star::~Star()
{

}

void Star::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPolygon star;

    QRectF rect = QRectF(getEndPoint().x() > getStartPoint().x() ? getStartPoint().x() : getEndPoint().x(),
                getEndPoint().y() > getStartPoint().y() ? getStartPoint().y() : getEndPoint().y(),
                qAbs(getEndPoint().x() - getStartPoint().x()),
                qAbs(getEndPoint().y() - getStartPoint().y()));

    qreal halfWidth = rect.width()/2;
    qreal halfHeight= rect.height()/2;
    qreal Xcenter = rect.center().x();
    qreal Ycenter = rect.center().y();

    star << QPoint (Xcenter, Ycenter - halfHeight)

         << QPoint (Xcenter + halfWidth * sin(13*3.1415/180),
                    Ycenter - halfHeight * sin(18*3.1415/180))

         << QPoint (Xcenter + halfWidth * cos(18*3.1415/180),
                    Ycenter - halfHeight * sin(18*3.1415/180))

         << QPoint (Xcenter + halfWidth * sin(18*3.1415/180),
                    Ycenter + halfHeight * sin(18*3.1415/180)/2)

         << QPoint (Xcenter + halfWidth * sin(36*3.1415/180),
                    Ycenter + halfHeight * cos(36*3.1415/180))

         << QPoint (Xcenter, Ycenter + halfHeight / 3)

         << QPoint (Xcenter - halfWidth * sin(36*3.1415/180),
                    Ycenter + halfHeight * cos(36*3.1415/180))

         << QPoint (Xcenter - halfWidth * sin(18*3.1415/180),
                    Ycenter + halfHeight * sin(18*3.1415/180)/2)

         << QPoint (Xcenter - halfWidth * cos(18*3.1415/180),
                    Ycenter - halfHeight * sin(18*3.1415/180))

         << QPoint (Xcenter - halfWidth * sin(13*3.1415/180),
                    Ycenter - halfHeight * sin(18*3.1415/180))

         << QPoint (Xcenter, Ycenter - halfHeight);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);

    painter->drawPolygon(star);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
