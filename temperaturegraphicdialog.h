#ifndef TEMPERATUREGRAPHICDIALOG_H
#define TEMPERATUREGRAPHICDIALOG_H

#include <QDialog>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>

namespace Ui {
class TemperatureGraphicDialog;
}

class TemperatureGraphicDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TemperatureGraphicDialog(QWidget *parent = 0);
    ~TemperatureGraphicDialog();
    enum Shape { Line, Points, Polyline, Polygon, Rect, RoundedRect, Ellipse, Arc,
                    Chord, Pie, Path, Text, Pixmap };

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setShape(Shape shape);
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setAntialiased(bool antialiased);
    void setTransformed(bool transformed);

protected:
     void paintEvent(QPaintEvent *event);


private:
    Ui::TemperatureGraphicDialog *ui;

    Shape shape;
    QPen pen;
    QBrush brush;
    bool antialiased;
    bool transformed;
    QPixmap pixmap;
};

#endif // TEMPERATUREGRAPHICDIALOG_H
