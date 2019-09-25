#ifndef Shape_H
#define Shape_H

#include <QGraphicsObject>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QVector>
//#include <QCursor>

class Shape : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Shape(QPointF point, QObject *parent = nullptr);
    ~Shape();

    QPointF getStartPoint() const;
    QPointF getEndPoint() const;

    void setStartPoint(const QPointF &point);
    virtual void setEndPoint(const QPointF &point); //TODO polygon

    void addLine(QGraphicsLineItem *line, bool is_first);

protected:
    //QRectF rect;
    bool touched;
    QPointF start_point;
    QPointF end_point;
    QPointF center;
    void updateCenter(const QPointF &new_pos = QPointF());
    QRectF boundingRect() const override;

private:

    virtual void updatePoints(const QPointF &start); //TODO polygon

    struct Lines
    {
        QGraphicsLineItem *line;
        bool is_first;
    };

    QVector<Lines> added_lines;

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void moveLinesToCenter();

};

#endif // Shape_H
