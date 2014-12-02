#include "temperaturegraphicdialog.h"
#include "ui_temperaturegraphicdialog.h"

#include <QtGui>

 const int IdRole = Qt::UserRole;

TemperatureGraphicDialog::TemperatureGraphicDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemperatureGraphicDialog)
{
    ui->setupUi(this);

    this->pen = QPen(Qt::blue, 2,  Qt::SolidLine,  Qt::FlatCap, Qt::MiterJoin);

    antialiased = false;
    transformed = false;

     setBackgroundRole(QPalette::Base);
     setAutoFillBackground(true);

     this->setShape(Polyline);
 }

 QSize TemperatureGraphicDialog::minimumSizeHint() const
 {
     return QSize(400, 200);
 }

 QSize TemperatureGraphicDialog::sizeHint() const
 {
     return QSize(400, 200);
 }

 void TemperatureGraphicDialog::setShape(Shape shape)
 {
     this->shape = shape;
     update();
 }

 void TemperatureGraphicDialog::setPen(const QPen &pen)
 {
     this->pen = pen;
     update();
 }

 void TemperatureGraphicDialog::setBrush(const QBrush &brush)
 {
     this->brush = brush;
     update();
 }

 void TemperatureGraphicDialog::setAntialiased(bool antialiased)
 {
     this->antialiased = antialiased;
     update();
 }

 void TemperatureGraphicDialog::setTransformed(bool transformed)
 {
     this->transformed = transformed;
     update();
 }

 void TemperatureGraphicDialog::paintEvent(QPaintEvent * /* event */)
 {
     static const QPoint points[4] = {
         QPoint(10, 280),
         QPoint(20, 210),
         QPoint(80, 230),
         QPoint(90, 270)
     };


     QPainter painter(this);
     painter.setPen(pen);
     painter.setBrush(brush);

     if (antialiased)
         painter.setRenderHint(QPainter::Antialiasing, true);

     painter.drawPolyline(points, 4);

     painter.setRenderHint(QPainter::Antialiasing, false);
     painter.setPen(palette().dark().color());
     painter.setBrush(Qt::NoBrush);

 }


TemperatureGraphicDialog::~TemperatureGraphicDialog()
{
    delete ui;
}
