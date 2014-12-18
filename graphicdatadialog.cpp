#include "graphicdatadialog.h"
#include "ui_graphicdatadialog.h"

GraphicDataDialog::GraphicDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicDataDialog)
{
    ui->setupUi(this);
}

GraphicDataDialog::~GraphicDataDialog()
{
    delete ui;
}
