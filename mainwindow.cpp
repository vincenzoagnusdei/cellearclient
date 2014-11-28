#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "assert.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mpRealtimeDataDlg = new RealtimeDataDialog(this);
    mpNetworkParamDialog = new NetworkParamDialog(this);
}

MainWindow::~MainWindow()
{    

    delete mpRealtimeDataDlg;
    delete mpNetworkParamDialog;
    delete ui;

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
