#include "graphicitem.h"
#include <QDebug>


GraphicItem::GraphicItem(figure f)
{
    mFigure =f;

}


GraphicItem::~GraphicItem()
{
    qDebug() << "destroyed Graphic Item ";

}



void GraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem
*option, QWidget *widget)
{

    painter->setPen(mPen);
    switch(mFigure)
    {
    case linefigure:
        painter->drawLine(mLine);
    break;

    case pointfigure:
        painter->drawPoint(mXPoint,mYPoint);
    break;

    default:
        qDebug() << "Unknown figure";

    }

    QGraphicsTextItem::paint(painter, option, widget);
}



void GraphicItem::drawLine( qreal x1, qreal y1, qreal x2, qreal y2, QPen pen )
{
    mPen = pen;
    mLine.setLine(x1,y1,x2,y2);

    update();
}


void GraphicItem::drawPoint( qreal x, qreal y, QPen pen )
{
    mPen = pen;
    mXPoint=x;
    mYPoint=y;

    update();
}


