#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "shape.h"
#include "rectangle.h"
#include "ellipse.h"
#include "star.h"
#include "polygon.h"

class Factory
{
public:
    virtual Shape* createShape(const QPointF &point) = 0;
    virtual ~Factory();
};

class RectangleFactory : public Factory
{
public:
    Shape* createShape(const QPointF &point) override;
};

class EllipseFactory : public Factory
{
public:
    Shape* createShape(const QPointF &point) override;
};

class StarFactory : public Factory
{
public:
    Shape* createShape(const QPointF &point) override;
};

class PolygonFactory : public Factory
{
public:
    Shape* createShape(const QPointF &point) override;
};

#endif // FACTORY_HPP
