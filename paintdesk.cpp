#include "paintdesk.h"
#include <QException>
#include <iostream>

PaintDesk::PaintDesk(QObject *parent) : QGraphicsScene(parent)
{
    setMode(PaintDesk::NoMode);
    first_touch = QPointF();
    temp_Shape = nullptr;
    line = nullptr;
    sides_of_Polygon = QList<QGraphicsLineItem *>();
}

PaintDesk::~PaintDesk()
{

}

PaintDesk::Mode PaintDesk::getMode() const
{
    return mode;
}

void PaintDesk::setMode(const PaintDesk::Mode mode)
{
    this->mode = mode;
    setFirstTouchIsNull();
}

void PaintDesk::setFirstTouchIsNull()
{
    this->first_touch = QPointF();
}

void PaintDesk::addItemToDesk(QGraphicsSceneMouseEvent *event = nullptr,
                              Shape *temp_Shape = nullptr)
{
    if(event != nullptr && temp_Shape != nullptr)
    {
        this->temp_Shape = temp_Shape;
        this->temp_Shape->setPos(event->pos());
    }
    this->addItem(this->temp_Shape);
    this->temp_Shape->setFlags(QGraphicsItem::ItemIsMovable);
    this->temp_Shape->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void PaintDesk::uniteShapesWithLine(const QPointF &second_touch)
{
    Shape  *first_Shape = (dynamic_cast<Shape *>(this->items(first_touch).first()));
    Shape  *second_Shape = (dynamic_cast<Shape *>(this->items(second_touch).first()));

    this->line = this->addLine(QLineF (first_touch.x(), first_touch.y(),
                                second_touch.x(), second_touch.y()));
    first_Shape->addLine(line, true);
    second_Shape->addLine(line, false);
    setFirstTouchIsNull();
}

void PaintDesk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mode)
    {
        case NoMode:
        {
            QGraphicsScene::mousePressEvent(event);
            break;
        }
        case UnitMode:
        {
            if (!(this->items(event->scenePos()).isEmpty()))
            {
                if (first_touch.isNull())
                    first_touch = event->scenePos();
                else if (this->items(first_touch).first() != this->items(event->scenePos()).first())
                    uniteShapesWithLine(event->scenePos());
            }
            break;
        }
        case StarMode:
        {
            addItemToDesk(event, new Star(event->scenePos()));
            break;
        }
        case EllipseMode:
        {
            addItemToDesk(event, new Ellipse(event->scenePos()));
            break;
        }
        case RectangleMode:
        {
             addItemToDesk(event, new Rectangle(event->scenePos()));
             break;
        }
        case PolygonMode:
        {
            if(first_touch.isNull())
            {
                temp_Shape = new Polygon(event->scenePos());
                dynamic_cast<Polygon *>(temp_Shape)->setPos(event->pos());
                first_touch = event->scenePos();
            }
            else
            {
                QGraphicsLineItem *side = this->addLine(QLineF (first_touch.x(), first_touch.y(),
                                         event->scenePos().x(), event->scenePos().y()));
                dynamic_cast<Polygon *>(temp_Shape)->setSide(side);
                sides_of_Polygon.push_back(side);
                first_touch = event->scenePos();

                if (dynamic_cast<Polygon *>(temp_Shape)->isEnded())
                {
                    addItemToDesk();
                    for (auto &side : sides_of_Polygon)
                        delete  side;
                    sides_of_Polygon.clear();
                    temp_Shape = nullptr;
                    setFirstTouchIsNull();
                }
            }
            break;
        }
    }
}

void PaintDesk::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mode)
    {
        case NoMode:
        {
            QGraphicsScene::mouseMoveEvent(event);
            break;
        }
        case UnitMode:
            break;
        case PolygonMode:
            break;
        default:
        {
            temp_Shape->setEndPoint(event->scenePos());
            this->update();
            break;
        }
    }
}

void PaintDesk::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}
