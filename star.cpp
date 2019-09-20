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

    qreal halfWidthEllipse = rect.width()/2;
    qreal halfHeightEllipse = rect.height()/2;
    qreal Xcenter = rect.center().x();
    qreal Ycenter = rect.center().y();

/*
    qreal R18 = (halfHeightEllipse*halfWidthEllipse)
            / sqrt(pow(halfWidthEllipse, 2)*pow(sin(18*3.1415/180), 2)
                    + pow(halfHeightEllipse, 2)*pow(cos(18*3.1415/180) , 2));
    qreal R144 = (halfHeightEllipse*halfWidthEllipse)
            / sqrt(pow(halfWidthEllipse, 2)*pow(sin((-144)*3.1415/180), 2)
                    + pow(halfHeightEllipse, 2)*pow(cos((-144)*3.1415/180) , 2));

    qreal CD = halfWidthEllipse*cos(18*3.1415/180)/3;
    qreal CDy = halfWidthEllipse*sin(18*3.1415/180)*2;
    qreal CDx = sqrt (pow(x,2) - pow(y,2));
    qreal DcenterX = -z +halfWidthEllipse*cos(18*3.1415/180)/2;

    //QPoint (Xcenter+halfWidthEllipse*sin(36*3.1415/180),
                         //Ycenter+halfHeightEllipse*sin(36*3.1415/180)/2)//D
*/

    star << QPoint (Xcenter, Ycenter - halfHeightEllipse)

         << QPoint (Xcenter + halfWidthEllipse * sin(13*3.1415/180),
                    Ycenter - halfHeightEllipse * sin(18*3.1415/180))

         << QPoint (Xcenter + halfWidthEllipse * cos(18*3.1415/180),
                    Ycenter - halfHeightEllipse * sin(18*3.1415/180))

         << QPoint (Xcenter + halfWidthEllipse * sin(18*3.1415/180),
                    Ycenter + halfHeightEllipse * sin(18*3.1415/180)/2)

         << QPoint (Xcenter + halfWidthEllipse * sin(36*3.1415/180),
                    Ycenter + halfHeightEllipse * cos(36*3.1415/180))

         << QPoint (Xcenter, Ycenter + halfHeightEllipse / 3)

         << QPoint (Xcenter - halfWidthEllipse * sin(36*3.1415/180),
                    Ycenter + halfHeightEllipse * cos(36*3.1415/180))

         << QPoint (Xcenter - halfWidthEllipse * sin(18*3.1415/180),
                    Ycenter + halfHeightEllipse * sin(18*3.1415/180)/2)

         << QPoint (Xcenter - halfWidthEllipse * cos(18*3.1415/180),
                    Ycenter - halfHeightEllipse * sin(18*3.1415/180))

         << QPoint (Xcenter - halfWidthEllipse * sin(13*3.1415/180),
                    Ycenter - halfHeightEllipse * sin(18*3.1415/180))

         << QPoint (Xcenter, Ycenter - halfHeightEllipse);

/*
    star << QPoint(Xcenter-R18, Ycenter+R18)
         << QPoint(Xcenter, Ycenter-halfHeightEllipse*2)
         << QPoint(Xcenter+R18, Ycenter+R18)
         << QPoint(Xcenter-R18, Ycenter-R18)
         << QPoint(Xcenter+R18, Ycenter-R18)
         << QPoint(Xcenter-R18, Ycenter+R18);
*/

    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);

    painter->drawPolygon(star);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
