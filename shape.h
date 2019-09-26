#ifndef Shape_H
#define Shape_H

#include <QGraphicsObject>
#include <QPainter>
#include <QGraphicsLineItem>
#include <QVector>

class Shape : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit Shape(QPointF point, QObject *parent = nullptr);
    virtual ~Shape();

    QPointF getStartPoint() const;
    QPointF getEndPoint() const;

    void setStartPoint(const QPointF &point);
    void setEndPoint(const QPointF &point);
    void addLine(QGraphicsLineItem *line, bool is_first);

protected:

    QPointF start_point;
    QPointF end_point;
    QPointF center;
    QRectF boundingRect() const override;
    void updateCenter(const QPointF &new_pos = QPointF());

private:
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
