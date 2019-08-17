#include "paintdesk.h"
#include <QException>
#include <iostream>

PaintDesk::PaintDesk(QObject *parent) : QGraphicsScene(parent)
{
    setMode(PaintDesk::NoMode);
    first_touch = QPointF();
    temp_Figure = nullptr;
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

void PaintDesk::addItemToDesk(QGraphicsSceneMouseEvent *event = nullptr, Figure *temp_Figure = nullptr)
{
    if(event != nullptr && temp_Figure != nullptr)
    {
        this->temp_Figure = temp_Figure;
        this->temp_Figure->setPos(event->pos());
    }
    this->addItem(this->temp_Figure);
    this->temp_Figure->setFlags(QGraphicsItem::ItemIsMovable);
    this->temp_Figure->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

void PaintDesk::uniteFiguresWithLine(QPointF &&second_touch)
{
    Figure  *first_Figure = (dynamic_cast<Figure *>(this->items(first_touch).first()));
    Figure  *second_Figure = (dynamic_cast<Figure *>(this->items(second_touch).first()));

    this->line = this->addLine(QLineF (first_touch.x(), first_touch.y(),
                                second_touch.x(), second_touch.y()));
    first_Figure->addLine(line, true);
    second_Figure->addLine(line, false);
    setFirstTouchIsNull();
}

void PaintDesk::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    switch (mode)
    {
        case NoMode:
        {
            //if(auto touch = this->items(event->scenePos()); !(touch.isEmpty()))
                //touch.first()->setCursor(QCursor(Qt::ClosedHandCursor));
            QGraphicsScene::mousePressEvent(event);
            break;
        }
        case UnitMode:
        {
            if(first_touch.isNull())
            {
                if(!(this->items(event->scenePos()).isEmpty()))
                    first_touch = event->scenePos();
            }
            else if(!(this->items(event->scenePos()).isEmpty()) &&
                    this->items(first_touch).first() != this->items(event->scenePos()).first())
                uniteFiguresWithLine(event->scenePos());
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
                temp_Figure = new Polygon(event->scenePos());
                dynamic_cast<Polygon *>(temp_Figure)->setPos(event->pos());
                first_touch = event->scenePos();
            }
            else
            {
                QGraphicsLineItem *side = this->addLine(QLineF (first_touch.x(), first_touch.y(),
                                         event->scenePos().x(), event->scenePos().y()));
                dynamic_cast<Polygon *>(temp_Figure)->setSide(side);
                sides_of_Polygon.push_back(side);
                first_touch = event->scenePos();

                if (dynamic_cast<Polygon *>(temp_Figure)->isEnded())
                {
                    addItemToDesk();
                    for (auto &side : sides_of_Polygon)
                        delete  side;
                    sides_of_Polygon.clear();
                    temp_Figure = nullptr;
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
            temp_Figure->setEndPoint(event->scenePos());
            this->update();
            break;
        }
    }
}

void PaintDesk::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
}
