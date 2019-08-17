#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QVector>
//#include <QCursor>

class Figure : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Figure(QPointF point, QObject *parent = nullptr);
    ~Figure();

    QPointF getStartPoint() const;
    QPointF getEndPoint() const;

    void setStartPoint(const QPointF point);
    virtual void setEndPoint(const QPointF point);

    void addLine(QGraphicsLineItem *line, bool is_first);

protected:
    //QRectF rect;
    QPointF start_point;
    QPointF end_point;

private:
    QRectF boundingRect() const override;
    virtual void updatePoints();
    struct Lines
    {
        QGraphicsLineItem *line;
        bool is_first;
    };

    QVector<Lines> added_lines;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void moveLineToCenter(QPointF new_pos);

};

#endif // FIGURE_H
