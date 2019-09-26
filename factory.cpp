#include "factory.h"

Factory::~Factory()
{

}

Shape* RectangleFactory::createShape(const QPointF &point)
{
    return new Rectangle(point);
}

Shape* EllipseFactory::createShape(const QPointF &point)
{
     return new Ellipse(point);
}

Shape* StarFactory::createShape(const QPointF &point)
{
     return new Star(point);
}

Shape* PolygonFactory::createShape(const QPointF &point)
{
     return new Polygon(point);
}
