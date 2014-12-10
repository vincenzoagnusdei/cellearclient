#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "assert.h"
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDir::setCurrent(FileHandler::FILE_DIRECTORY);
    ui->setupUi(this);
    mpRealtimeDataDlg = new RealtimeDataDialog(this);
    mpNetworkParamDialog = new NetworkParamDialog(this);
    mptempGraphDialog = new TemperatureGraphicDialog();
    mpXvalueRetriever = new ThresholdCrossingRetriervers(this);
}

MainWindow::~MainWindow()
{    

    delete mpRealtimeDataDlg;
    delete mpNetworkParamDialog;
    delete ui;
    delete mptempGraphDialog;

}

void MainWindow::on_actionNetwork_Parameter_triggered()
{  
    mpNetworkParamDialog->exec();
}

void MainWindow::on_actionTemperature_triggered()
{
    mpRealtimeDataDlg->exec();
}


FileHandler* MainWindow::getFileHanlder()
{
    return &mFH;
}

void MainWindow::on_actionGraphicTemperature_triggered()
{
    mptempGraphDialog->exec();
}
