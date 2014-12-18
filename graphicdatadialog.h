#ifndef GRAPHICDATADIALOG_H
#define GRAPHICDATADIALOG_H

#include <QDialog>

namespace Ui {
class GraphicDataDialog;
}

class GraphicDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicDataDialog(QWidget *parent = 0);
    ~GraphicDataDialog();

private:
    Ui::GraphicDataDialog *ui;
};

#endif // GRAPHICDATADIALOG_H
