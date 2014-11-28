#ifndef NETWORKPARAMDIALOG_H
#define NETWORKPARAMDIALOG_H

#include <QDialog>
#include "filehandler.h"

namespace Ui {
class NetworkParamDialog;
}

class NetworkParamDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetworkParamDialog(QWidget *parent = 0);
    ~NetworkParamDialog();


private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    void initParameters();
    Ui::NetworkParamDialog *ui;
    FileHandler *mFH;

};

#endif // NETWORKPARAMDIALOG_H
