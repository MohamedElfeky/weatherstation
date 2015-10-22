#include "hostname.h"
//#include "ui_hostname.h"
#include <QFileDialog>
#include <QtNetwork>

//need to verify port is an integer


void Hostname::setDefaultPort()
{
    this->lineEditHostport->setText(defaultport);
}

void Hostname::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        textBrowser->setText(tr("Airmar Weather Client"
                                "The server host was not found. Please check the "
                                "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        textBrowser->setText(tr("Airmar Weather Client"
                                "The connection was refused by the peer. "
                                "Make sure the Airmar Weather Server is running, "
                                "and check that the host name and port "
                                "settings are correct."));
        break;
    default:
        textBrowser->setText(tr("Airmar Weather Client"
                                "The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }

//    getFortuneButton->setEnabled(true);
}
/*void Hostname::openPort()
{
  tcpSocket = new QTcpSocket(this);
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readPort()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

  QNetworkConfigurationManager manager;
  if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
      // Get saved network configuration
      QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
      settings.beginGroup(QLatin1String("QtNetwork"));
      const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
      settings.endGroup();

      // If the saved network configuration is not currently discovered use the system default
      QNetworkConfiguration config = manager.configurationFromIdentifier(id);
      if ((config.state() & QNetworkConfiguration::Discovered) !=
          QNetworkConfiguration::Discovered) {
          config = manager.defaultConfiguration();
      }

      networkSession = new QNetworkSession(config, this);
      connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

      //getFortuneButton->setEnabled(false);
      statusLabel->setText(tr("Opening network session."));
      networkSession->open();
  }  networkSession = new QNetworkSession(config, this);


//getFortuneButton->setEnabled(false);
//  statusLabel->setText(tr("Opening network session."));
//  networkSession->open();

}*/
void Hostname::requestNewData()
{
//    getFortuneButton->setEnabled(false);
    host=lineEditHostname->text();
    port=lineEditHostport->text();
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(host,port.toInt());
}
void Hostname::readPort()
{

 //   QDataStream in(tcpSocket);
 //   in.setVersion(QDataStream::Qt_4_0);

//    QObject::connect(tcpSocket, &QTcpSocket::readyRead, [tcpSocket] () {
//           qDebug()<< "GOT DATA "<< tcpSocket->readLine());//  readAll();
//       });
/*    if (blockSize == 0) {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
        return;
*/
//    QString nextFortune;
//    in >> nextFortune;
      currentFortune = tcpSocket->readLine();

    //if (nextFortune == currentFortune) {
    //    QTimer::singleShot(0, this, SLOT(requestNewFortune()));
    //    return;
    //}
//    currentFortune = nextFortune;
      textBrowser->append(currentFortune);
    //
     // statusLabel->setText(currentFortune);
  //  getFortuneButton->setEnabled(true);
}

Hostname::Hostname(QWidget *parent, QString ihost, QString iport) :
    QDialog(parent), networkSession(0)
//    ui(new Ui::Hostname)
{
  //  ui->
    defaultport="23000";
    host=ihost;
    port=iport;
    setupUi(this);
    this->lineEditHostname->setText(host);
    this->lineEditHostport->setText(port);
    this->pushButtonDefaultPort->setText(tr("Default port ")+defaultport);
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readPort()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));

    QObject::connect(this->pushButtonDefaultPort,SIGNAL(clicked()),this,SLOT(setDefaultPort()));
    QObject::connect(this->pushButtonGetData,SIGNAL(clicked()),this,SLOT(requestNewData()));

}

//Hostname::~Hostname()
//{
 //   delete ui;
//}
