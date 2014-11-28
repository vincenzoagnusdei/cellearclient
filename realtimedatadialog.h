#ifndef REALTIMEDATADIALOG_H
#define REALTIMEDATADIALOG_H

#include "connectwrapper.h"
#include "filehandler.h"
#include <QDialog>
#include <cantcoap/cantcoap.h>
#include <QShowEvent>


#define BUF_LEN 500

namespace Ui {
class RealtimeDataDialog;
}

class RealtimeDataDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RealtimeDataDialog(QWidget *parent = 0);
    ~RealtimeDataDialog();

    int connectToRemote();
    int getData();    

private:
     void showEvent( QShowEvent* event );

    Ui::RealtimeDataDialog *ui;
    CoapPDU *mpdu;
    int msockfd;
    ConnectWrapper mConnectWrapper;
    FileHandler *mpFH;
    bool isConnected;

private slots:
    void on_read_data();

};

#endif // REALTIMEDATADIALOG_H
