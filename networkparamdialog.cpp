#include <QStringList>
#include <QtNetwork/QHostInfo>

#include "networkparamdialog.h"
#include "ui_networkparamdialog.h"
#include "mainwindow.h"

NetworkParamDialog::NetworkParamDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkParamDialog)
{
    ui->setupUi(this);
    ui->remoteIPAddressLE->setInputMask( "000.000.000.000" );
    ui->localIPAddressLE->setInputMask( "000.000.000.000" );
    ui->localPortLE->setInputMask("00000");
    ui->remotePortLE->setInputMask("00000");   
    ui->serverPortLE->setInputMask("000000");
    this->initParameters();

}

NetworkParamDialog::~NetworkParamDialog()
{
    delete ui;
}

void NetworkParamDialog::on_buttonBox_rejected()
{

}

void NetworkParamDialog::on_buttonBox_accepted()
{

     QString listparameter;
      listparameter.append(ui->localIPAddressLE->text());
      listparameter.append("\n");
      listparameter.append(ui->localPortLE->text());
      listparameter.append("\n");
      listparameter.append(ui->remoteIPAddressLE->text());
      listparameter.append("\n");
      listparameter.append(ui->remotePortLE->text());
      listparameter.append("\n");
      listparameter.append(ui->serverPortLE->text());
      listparameter.append("\n");
      mFH->writeParameters(&listparameter);



}

void NetworkParamDialog::initParameters(){


    mFH = ((MainWindow *) this->parent())->getFileHanlder();    
    ui->remoteIPAddressLE->setText(mFH->getRemoteAddress());
    ui->localIPAddressLE->setText(mFH->getListenAddress());
    ui->remotePortLE->setText(mFH->getRemotePort());
    ui->localPortLE->setText(mFH->getListenPort());
    ui->serverPortLE->setText(mFH->getFileTransferPort());


}


