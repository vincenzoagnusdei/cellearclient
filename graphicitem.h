#ifndef GRAPHICITEM_H
#define GRAPHICITEM_H

#include <QGraphicsTextItem>
#include <QWidget>
#include <QPainter>
#include <QLineF>
#include <QPen>
#include <QPointF>


class GraphicItem : public QGraphicsTextItem
{
public:
    enum figure {linefigure, pointfigure};
    GraphicItem(figure f);
    ~GraphicItem();


    enum { Type = UserType + 4 };
    void drawLine( qreal x1, qreal y1, qreal x2, qreal y2, QPen pen );
    void drawPoint( qreal x, qreal y, QPen pen );

signals:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


private:
    QLineF mLine;
    QPen mPen;
    figure mFigure;
    int mXPoint;
    int mYPoint;


};


#endif // GRAPHICITEM_H
