#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networkparamdialog.h"
#include "realtimedatadialog.h"
#include "filehandler.h"
#include "temperaturegraphicdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    FileHandler *getFileHanlder();



private slots:
    void on_actionNetwork_Parameter_triggered();
    void on_actionTemperature_triggered();
    void on_actionGraphicTemperature_triggered();

private:
    Ui::MainWindow *ui;
    NetworkParamDialog *mpNetworkParamDialog;
    RealtimeDataDialog *mpRealtimeDataDlg;
    FileHandler mFH;
    TemperatureGraphicDialog *mptempGraphDialog;
};

#endif // MAINWINDOW_H
