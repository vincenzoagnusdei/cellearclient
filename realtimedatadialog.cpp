#include <sys/types.h>
#include <sys/socket.h>
#define __USE_POSIX 1
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <math.h>
#include "nethelper.h"
#include <cantcoap/cantcoap.h>
#include <QDebug>

#include "realtimedatadialog.h"
#include "ui_realtimedatadialog.h"
#include "mainwindow.h"
#include <assert.h>



using namespace std;

RealtimeDataDialog::RealtimeDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RealtimeDataDialog)
{
    this->isConnected = false;
    ui->setupUi(this);

    mpFH = ((MainWindow *) this->parent())->getFileHanlder();
    connect(this->ui->readBtn,SIGNAL(clicked()), this,
            SLOT(on_read_data()));

}

RealtimeDataDialog::~RealtimeDataDialog()
{

    mConnectWrapper.remoteClose(msockfd);
    delete ui;        

}



int RealtimeDataDialog::connectToRemote()
{
    struct addrinfo *remoteAddress;
    int ret;
    QStringList parameters;
    char *listenAddressString;
    char *listenPortString;
    char *remoteAddressString;
    char *remotePortString;  

    string listenadd = mpFH->getListenAddress().toUtf8().constData();
    string listenport = mpFH->getListenPort().toUtf8().constData();
    string remoteadd = mpFH->getRemoteAddress().toUtf8().constData();
    string remoteport = mpFH->getRemotePort().toUtf8().constData();

    listenAddressString = (char *) listenadd.c_str();
    listenPortString = (char *) listenport.c_str();
    remoteAddressString = (char *) remoteadd.c_str();
    remotePortString = (char *) remoteport.c_str();

    // setup bind address
    struct addrinfo *bindAddr;
    qDebug("Setting up bind address");
    ret = setupAddress(listenAddressString,listenPortString,&bindAddr,SOCK_DGRAM,AF_INET);
    if(ret!=0) {
        qDebug("Error setting up bind address, exiting.");
        return -1;
    }

    // iterate through returned structure to see what we got
    printAddressStructures(bindAddr);

    // setup socket
    msockfd = socket(bindAddr->ai_family,bindAddr->ai_socktype,bindAddr->ai_protocol);

    // call bind
    qDebug("Binding socket.");
    if(bind(msockfd,bindAddr->ai_addr,bindAddr->ai_addrlen)!=0) {
        qDebug("Error binding socket");

    }

    //
    printAddress(bindAddr);



    ret = setupAddress(remoteAddressString,remotePortString,&remoteAddress,SOCK_DGRAM,AF_INET);
    if(ret!=0) {
        qDebug("Error setting up remote address, exiting.");
        return -1;
    }

    // call connect to associate remote address with socket
    ret = mConnectWrapper.remoteConnect(msockfd,remoteAddress->ai_addr,remoteAddress->ai_addrlen);
    if(ret!=0) {
        qDebug("Error: %s.",gai_strerror(ret));
        qDebug("Error connecting to remote host.");
        return -1;
    }
    printAddress(remoteAddress);

    return 1;
}

int RealtimeDataDialog::getData()
{

    // receive packet
    char buffer[BUF_LEN];
    int ret;
    QString response;

    CoapPDU *mpdu = new CoapPDU();
    // construct CoAP packet

    mpdu->setVersion(1);
    mpdu->setType(CoapPDU::COAP_CONFIRMABLE);
    mpdu->setCode(CoapPDU::COAP_GET);
    mpdu->setToken((uint8_t*)"\3\2\1\1",4);
    mpdu->setMessageID(0x0005);
    mpdu->setURI((char*)"currenttemperature",18);
    mpdu->addOption(CoapPDU::COAP_OPTION_CONTENT_FORMAT,1,(uint8_t*)")");

    // send packet
    ret = send(msockfd,mpdu->getPDUPointer(),mpdu->getPDULength(),0);
    if(ret!=mpdu->getPDULength()) {
        qDebug("Error sending packet.");
        return -1;
    }
    qDebug("Packet sent");


    ret = recv(msockfd,&buffer,BUF_LEN,0);
    if(ret==-1) {
        qDebug("Error receiving data");
        return -1;
    }

    // validate packet
    CoapPDU *recvPDU = new CoapPDU((uint8_t*)buffer,ret);    

    // validate packet
    if(ret>BUF_LEN) {
        qDebug("PDU too large to fit in pre-allocated buffer");
    }
    else
    {

        if(recvPDU->validate()!=1)
        {
            qDebug("Malformed CoAP packet");
        }
        else
        {
            qDebug("Valid CoAP PDU received");

            uint8_t *payloadptr = recvPDU->getPayloadPointer();



            for(int j=0; j<recvPDU->getPayloadLength(); j++) {
                char c = payloadptr[j];
                 response.append(c);

            }


            qDebug() << response;


        }

   }
    return 0;
}


void RealtimeDataDialog::on_read_data()
{
    this->getData();

}


void RealtimeDataDialog::showEvent( QShowEvent* event ) {
    QWidget::showEvent( event );

    if (!this->isConnected)
    {
        this->connectToRemote();
    }
    this->getData();
}
