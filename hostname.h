#ifndef HOSTNAME_H
#define HOSTNAME_H

#include <QDialog>
#include <QTcpSocket>
#include "ui_hostname.h"

QT_BEGIN_NAMESPACE
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

namespace Ui {
class Hostname;
}

class Hostname : public QDialog, public Ui::Hostname
{
    Q_OBJECT
    
public:
    explicit Hostname(QWidget *parent = 0, QString ihost="", QString iport="0");
//    ~Hostname();
    
private:
    QString host;
    QString port;
    QString defaultport;//="27644";
//    Ui::Hostname *ui;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;

    QNetworkSession *networkSession;
private slots:
    void setDefaultPort();
//    void openPort();
    void requestNewData();
    void readPort();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // HOSTNAME_H
