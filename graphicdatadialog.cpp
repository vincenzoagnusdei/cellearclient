#include "graphicdatadialog.h"
#include "ui_graphicdatadialog.h"
#include "QGraphicsScene"
#include <QMatrix>
#include <QPointF>
#include <QPen>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QString>
#include <QFontMetrics>
#include <QFont>
#include <QLineF>
#include <QDateEdit>
#include <QDate>
#include <QDebug>
#include "labelgraphicitem.h"
#include "graphicitem.h"
#include "measure.h"
#include "filehandler.h"


const QString GraphicDataDialog::X_LABEL = "Time";
const QString GraphicDataDialog::Y_LABEL = "Temp.";

GraphicDataDialog::GraphicDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicDataDialog),mBlackpen(Qt::black),
    mBluepen(Qt::blue),mRedpen(Qt::red)
{

    ui->setupUi(this);



    QFont defaultfont;
    int fontsize = defaultfont.defaultFamily().size();
    mBluepen.setWidth(BLUE_PEN_WIDTH);
    mBlackpen.setWidth(BLACK_PEN_WIDTH);
    mRedpen.setWidth(RED_PEN_WIDTH);
    mRedpen.setCapStyle( Qt::RoundCap);

    mpDataSensor = new DataSensorParser(this);


    mpGraphicScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(mpGraphicScene);

    mLocalviewwidth = ui->graphicsView->width()-HORIZONTAL_EMPTY_SPACE;
    mLocalviewheight = ui->graphicsView->height()-VERTICAL_EMPTY_SPACE;


    int y_offset_from_window_border=mLocalviewheight/VERTICAL_VALUES_AVAILABLE_TO_PAINT*NEGATIV_VALUES;
    int x_scaled_system = Y_LABEL.size()*fontsize;
    int y_scaled_system = mLocalviewheight - y_offset_from_window_border;

    mMatrix.translate( x_scaled_system, y_scaled_system );
    mMatrix.scale( 1, -1 );

    mpGraphicScene->addLine(0, y_scaled_system, mLocalviewwidth, y_scaled_system,mBluepen);
    mpGraphicScene->addLine(x_scaled_system, 0, x_scaled_system, mLocalviewheight ,mBluepen);


    mYlbl.setPos(Y_LABEL_X_,Y_LABEL_Y);
    mYlbl.setPlainText(Y_LABEL);
    mYlbl.setDefaultTextColor(Qt::black);
    mpGraphicScene->addItem(&mYlbl);

    mXlbl.setPos(mLocalviewwidth-X_LABEL_X_OFFSET,y_scaled_system-X_LABEL_Y_OFFSET);
    mXlbl.setPlainText(X_LABEL);
    mXlbl.setDefaultTextColor(Qt::black);
    mpGraphicScene->addItem(&mXlbl);

    int pixelxlabel= mLocalviewheight/VERTICAL_VALUES_AVAILABLE_TO_PAINT;

    LabelGraphicItem *ptextitem;

    int grad = -NEGATIV_VALUES;
    int ytext= mLocalviewheight-fontsize/2;
    while (ytext > pixelxlabel +fontsize/2)
    {
        if  (grad != 0)
        {
             // skip label for origin point
             ptextitem = new LabelGraphicItem();
             ptextitem->setBoundingRect(x_scaled_system-Y_LABEL_SPACE_PIXEL,ytext, WIDTH_LABEL_Y , HEIGHT_LABEL_Y);
             ptextitem->setText(QString::number(grad));
             ptextitem->setDefaultTextColor(Qt::black);
             mpGraphicScene->addItem(ptextitem);
             mLabelList.append(ptextitem);
        }
        grad+=OFFSET_FOR_Y_LABELS;
        ytext-= pixelxlabel*OFFSET_FOR_Y_LABELS;
    }

    GraphicItem *pline;

    for (int liney=-NEGATIV_VALUES; liney <VERTICAL_VALUES_AVAILABLE_TO_PAINT-NEGATIV_VALUES; liney+=OFFSET_FOR_Y_LABELS)
    {

        pline = new GraphicItem(GraphicItem::linefigure);
        pline->setMatrix(mMatrix);
        pline->drawLine(X1_FOR_DASH_SYMBOL, liney*pixelxlabel , X2_FOR_DASH_SYMBOL,liney*pixelxlabel ,mBluepen);
        mpGraphicScene->addItem(pline);
        mGraphicDashList.append(pline);

   }

    this->paintMeasurePoints();

}


GraphicDataDialog::~GraphicDataDialog()
{

    mGraphicDashList.clear();
    mLabelList.clear();
    mGraphicPointList.clear();
    // delete mpGraphicScene; SIGNAL, investigare
    delete ui;

}



void GraphicDataDialog::on_dateValue_editingFinished()
{

    this->repaintMeasurePoints();
}

void GraphicDataDialog::paintMeasurePoints()
{


    QDate firstdate;
    QStringList ddmmyyyy;
     GraphicItem *pline;

    QList<Measure *> *pmeasurelist = mpDataSensor->getMeasureList();
    QList<Measure*>::iterator i;
    int j=1;
    i = (*pmeasurelist).begin();
    int numpointstopaint = 0;
    if (i !=  (*pmeasurelist).end())
    {
        numpointstopaint = mLocalviewwidth/HORIZONTAL_EMPTY_SPACE;
        ddmmyyyy=(*i)->getDate().split(FileHandler::SEPARATOR2);
        firstdate.setDate(ddmmyyyy.at(year).toInt(),
                          ddmmyyyy.at(month).toInt(),
                          ddmmyyyy.at(day).toInt());
        ui->dateValue->setDate(firstdate);
    }


    while (i !=  (*pmeasurelist).end() && j <= numpointstopaint)
    {

        pline = new GraphicItem(GraphicItem::pointfigure);
        pline->setMatrix(mMatrix);
        pline->drawPoint(j*HORIZONTAL_EMPTY_SPACE,
                         (*i)->getValue().toFloat()*mLocalviewheight/VERTICAL_VALUES_AVAILABLE_TO_PAINT, mRedpen);
        mpGraphicScene->addItem(pline);
        mGraphicPointList.append(pline);
        i++;
        j++;
    }



}

void GraphicDataDialog::repaintMeasurePoints()
{

    QDate date;
    QString ddmmyyyy;

    GraphicItem *pline;

    this->removePoints();

    QList<Measure *> *pmeasurelist = mpDataSensor->getMeasureList();
    QList<Measure*>::iterator i;
    int j=1;
    i = (*pmeasurelist).begin();
    int numpointstopaint = 0;
    if (i !=  (*pmeasurelist).end())
    {
        numpointstopaint = mLocalviewwidth/HORIZONTAL_EMPTY_SPACE;
        date = ui->dateValue->date();
        ddmmyyyy.append(QString::number(date.day()));
        ddmmyyyy.append(FileHandler::SEPARATOR2);
        ddmmyyyy.append(QString::number(date.month()));
        ddmmyyyy.append(FileHandler::SEPARATOR2);
        ddmmyyyy.append(QString::number(date.year()));
    }


    while (i !=  (*pmeasurelist).end() && j <= numpointstopaint)
    {

        if ((*i)->getDate().compare(ddmmyyyy) >=0)
        {
            pline = new GraphicItem(GraphicItem::pointfigure);
            pline->setMatrix(mMatrix);
            pline->drawPoint(j*HORIZONTAL_EMPTY_SPACE,
                             (*i)->getValue().toFloat()*mLocalviewheight/VERTICAL_VALUES_AVAILABLE_TO_PAINT, mRedpen);
            mpGraphicScene->addItem(pline);
            mGraphicPointList.append(pline);
            j++;
         }
         i++;
    }



}

void GraphicDataDialog::removePoints()
{
    GraphicItem *i;

    foreach (i, mGraphicPointList) {

        mpGraphicScene->removeItem(i);
    }
    mGraphicPointList.clear();

}
