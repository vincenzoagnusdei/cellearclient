#include "labelgraphicitem.h"

LabelGraphicItem::LabelGraphicItem()
{

    myBoundRect.setRect( 0, 0, 0, 0 );

    textOp.setAlignment( Qt::AlignCenter );
    textOp.setWrapMode( QTextOption::WrapAtWordBoundaryOrAnywhere );
}

LabelGraphicItem::~LabelGraphicItem()
{

}



void LabelGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem
*option, QWidget *widget)
{
    //painter->drawRect( boundingRect() );

    painter->drawText(	boundingRect(),
                        text,
                        textOp);

    QGraphicsTextItem::paint(painter, option, widget);
}

QRectF LabelGraphicItem::boundingRect() const
{
    return myBoundRect;
}

void LabelGraphicItem::setBoundingRect( qreal x, qreal y, qreal w, qreal h)
{
    myBoundRect.setRect( x, y, w, h );
}

void LabelGraphicItem::setText( const QString &inText )
{
    text = inText;
    update();
}


