#ifndef LABELGRAPHICITEM_H
#define LABELGRAPHICITEM_H

#include <QGraphicsTextItem>
#include <QWidget>
#include <QPainter>
#include <QString>
#include <QTextOption>
#include <QRectF>


class LabelGraphicItem : public QGraphicsTextItem
{

    Q_OBJECT

 public:
     LabelGraphicItem();
     ~LabelGraphicItem();
     enum { Type = UserType + 3 };

     void setBoundingRect( qreal x, qreal y, qreal w, qreal h);
     void setText( const QString &inText );

 signals:

 protected:
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
     QRectF boundingRect() const;

 private:
     QRectF myBoundRect;
     QTextOption textOp;
     QString text;
 };



#endif // LABELGRAPHICITEM_H

