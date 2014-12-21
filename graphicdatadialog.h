#ifndef GRAPHICDATADIALOG_H
#define GRAPHICDATADIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QString>
#include <QGraphicsTextItem>
#include <graphicitem.h>
#include <labelgraphicitem.h>
#include "datasensorparser.h"

namespace Ui {
class GraphicDataDialog;
}

class GraphicDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicDataDialog(QWidget *parent = 0);
    ~GraphicDataDialog();

private slots:

    void on_dateValue_editingFinished();

private:
    Ui::GraphicDataDialog *ui;
    QGraphicsScene *mpGraphicScene;
    QList<GraphicItem *> mGraphicDashList;
    QList<GraphicItem *> mGraphicPointList;
    QList<LabelGraphicItem *> mLabelList;
    QGraphicsTextItem mYlbl;
    QGraphicsTextItem mXlbl;
    DataSensorParser *mpDataSensor;
    QMatrix mMatrix;
    QPen mBlackpen;
    QPen mBluepen;
    QPen mRedpen;


    int mLocalviewwidth;
    int mLocalviewheight;


    static const int X_OFFSET_FROM_WINDOW_BORDER=50;    
    static const int VERTICAL_VALUES_AVAILABLE_TO_PAINT = 40;
    static const int HORIZONTAL_SPACE_BETWEEN_POINTS = 20;
    static const int X_LABEL_X_OFFSET=50;
    static const int X_LABEL_Y_OFFSET=2;
    static const int Y_LABEL_X_=3;
    static const int Y_LABEL_Y=1;
    static const int Y_LABEL_SPACE_PIXEL = 30;
    static const int NEGATIV_VALUES = 10;
    static const int OFFSET_FOR_Y_LABELS=5;
    static const QString X_LABEL;
    static const QString Y_LABEL;
    static const int BLACK_PEN_WIDTH=3;
    static const int BLUE_PEN_WIDTH=3;
    static const int RED_PEN_WIDTH=8;
    static const int X1_FOR_DASH_SYMBOL=-2;
    static const int X2_FOR_DASH_SYMBOL=2;
    static const int WIDTH_LABEL_Y=30;
    static const int HEIGHT_LABEL_Y=11;
    static const int VERTICAL_EMPTY_SPACE=50;
    static const int HORIZONTAL_EMPTY_SPACE=20;

    enum date_enum {day, month, year};

    void paintMeasurePoints();
    void repaintMeasurePoints();
    void removePoints();

};

#endif // GRAPHICDATADIALOG_H
