#ifndef PAINTDESK_H
#define PAINTDESK_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include "star.h"
#include "rectangle.h"
#include "ellipse.h"
#include "polygon.h"

class PaintDesk : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PaintDesk(QObject *parent = nullptr);
    ~PaintDesk();

    enum Mode
    {
        NoMode, StarMode, RectangleMode, EllipseMode,
        PolygonMode, UnitMode
    };

    Mode getMode() const;
    void setMode(const PaintDesk::Mode mode);
    void setFirstTouchIsNull();

private:
    Mode mode;
    QPointF  first_touch;
    Shape *temp_Shape;
    QGraphicsLineItem *line;
    QList<QGraphicsLineItem *> sides_of_Polygon;
    void addItemToDesk(QGraphicsSceneMouseEvent *event, Shape *temp_Shape);
    void uniteShapesWithLine(const QPointF &second_touch);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTDESK_H
