#include "parser.h"
#include <QtNetwork>
#include <QDebug>
#include <iostream>
#include "weatherdata.h"
#include "mainwindow.h"

//void Parser::baroChange(double newValue)
//{
//    baroPressB.changeValue(double newValue);
//}
//int ctr=0;
//void Parser::readPort(WeatherData *baroPressB)
void Parser::readPort()
{
//    ctr++;
    double tempVal;
    QString fullData;
    QString dataLine;
    //char *data;
    //qint64 maxlen = 1074;
    //data = new char[maxlen];
    //char buf[1075];
    //qint64 gotlen = tcpSocket->readLineData(data);
    //dataLine=tcpSocket->readLine(buf,sizeof(buf));
    fullData=tcpSocket->readAll();//  readLine();
//    tcpSocket->flush();
//    qDebug() << ctr << ": " << fullData;
    QStringList fullList = fullData.split(QRegExp("\n"));
    dataLine = fullList.at(0);
    QStringList sList = dataLine.split(QRegExp("[$,*]"), QString::SkipEmptyParts);
//    qDebug() << sList;
  //    qDebug() << sList;
    if ( sList.size() > 1 ){
      switch ( nmeaStrings.indexOf( sList.at(0) )) {
      case 0: //"$WIMWD":
//        qDebug() << "wind:" << sList.size();
        if ( sList.size() == 10 ){
          windDirM->setValue( QString(sList.at(1)).toDouble() );
          //windDirM->setValue( QString(sList.at(3)).toDouble() );
          windSpdK->setValue( QString(sList.at(5)).toDouble() );
          //windSpdM->setValue( QString(sList.at(7)).toDouble() );
        }
        break;
      case 1: //"$WIMDA"
//        qDebug() << "general stuff:" << sList.size();
        if ( sList.size() == 19 ){
          baroPressB->setValue(1000 * QString(sList.at(3)).toDouble() );
//          airTempC->setValue( QString(sList.at(5)).toDouble() );
          airTempF->setValue( (9 * QString(sList.at(5)).toDouble() / 5 ) + 32 );
//          dpTempC->setValue( QString(sList.at(8)).toDouble() );
          dpTempF->setValue( ( 9 * QString(sList.at(8)).toDouble() / 5 ) + 32 );
          rhPercent->setValue( QString(sList.at(7)).toDouble() );
          windDirT->setValue( QString(sList.at(10)).toDouble() );
//          windDirM->setValue( QString(sList.at(12)).toDouble() );
          windSpdK->setValue( QString(sList.at(14)).toDouble() );
          //windSpdM->setValue( QString(sList.at(16)).toDouble() );
        }
        break;
      case 2: //"$WIMWV" --relative to boat:
//        qDebug() << "relative wind:"<< sList.size();
        if ( sList.size() == 7 ){
          windDirRT->setValue( QString(sList.at(1)).toDouble() );
          windSpdRK->setValue( QString(sList.at(3)).toDouble() );
        }
        break;
      case 3: //"$HCHDG":
//          qDebug() << "boat heading and mag var:" << sList.size(); //--still need direction EW/+-: (5)";
        if ( sList.size() == 7 ){
          boatHdgM->setValue( QString(sList.at(1)).toDouble() );
          /*
          boatHdgT->setValue( QString(sList.at(1)).toDouble() );
          if ( sList.at(5) == "E" ) {
             boatHdgT->setOffsetVal( QString(sList.at(1)).toDouble() );
          }
          else if ( sList.at(5) == "W" ){
             boatHdgT->setOffsetVal( - QString(sList.at(1)).toDouble() );
          }
          boatMagVar->setValue( QString(sList.at(4)).toDouble() );
          */
        }
        break;
      case 4: //"$GPVTG"
//        qDebug() << "GPS cmg and sog:" << sList.size();
//        qDebug() << sList;
        if ( sList.size() == 11 ){
  //        boatCmgT->setValue( QString(sList.at(1)).toDouble() );
          boatCmgM->setValue( QString(sList.at(3)).toDouble() );
          boatVmgK->setValue( QString(sList.at(5)).toDouble() );
        }
        break;
      case 5: //"$GPZDA"
//          qDebug() << "GPS UTC Time:" << sList.size();
//          qDebug() << sList;
          if ( sList.size() == 8 ){
            utcTime->setValue( QString(sList.at(1)).toDouble() );
            utcDay->setValue( QString(sList.at(2)).toDouble() );
          }
          break;
      case 6: //"$YXMTW"
//          qDebug() << "Water temp:" << sList.size();
//          qDebug() << sList;
          if ( sList.size() == 4 ){
            waterTempF->setValue((  9 * QString(sList.at(1)).toDouble() / 5 ) + 32);
          }
          break;
      case 7: //"$SDDBT"
//          qDebug() << "Water depth:" << sList.size();
//          qDebug() << sList;
          if ( sList.size() == 8 ){
            waterDepthF->setValue( QString(sList.at(1)).toDouble() );
          }
          break;
      case 8: //"$GPGGA"
//          qDebug() << "GPS Pos:" << sList.size();
//          qDebug() << sList;
          if ( sList.size() == 12 ){
            utcTime->setValue( QString(sList.at(1)).toDouble() );
            if ( sList.at(3) == "N" ) {
               positionLatD->setScalarVal( 1 );
            }
            else if ( sList.at(3) == "S" ){
               positionLatD->setScalarVal( - 1 );
            }
            if ( sList.at(5) == "E" ) {
                positionLonD->setScalarVal( 1 );
            }
            else if ( sList.at(5) == "W" ){
               positionLonD->setScalarVal( - 1 );
            }

            tempVal = double(int(QString(sList.at(2)).toDouble() / 100) );
 //           qDebug() << "Lat: " << tempVal;
            positionLatD->setValue( tempVal );
            positionLatM->setValue( QString(sList.at(2)).toDouble() - ( tempVal * 100 ) );

            tempVal = double(int(QString(sList.at(4)).toDouble() / 100 ));
//            qDebug() << "Lon: " << tempVal;
            positionLonD->setValue( tempVal );
            positionLonM->setValue( QString(sList.at(4)).toDouble() - ( tempVal * 100 ) );
          }
          //MainWindow::computeDistance();
          break;
      //default:
         // qDebug() << "Skip all others: " << sList;
      }
//      qDebug() << sList;
//      tcpSocket->flush();
   }
  //  printf("%s",dataLine);
//    textBrowser->append(currentFortune);
}


Parser::Parser(QObject *parent, QString ihost, QString iport, \
               WeatherData *baro, \
               WeatherData *airTC, \
               WeatherData *airTF, \
               WeatherData *dpTC, \
               WeatherData *dpTF, \
               WeatherData *rhP, \
               WeatherData *windDT, \
               WeatherData *windDRT, \
               WeatherData *windDM, \
               WeatherData *windSK, \
               WeatherData *windSRK, \
               WeatherData *windSM, \
               WeatherData *boatHM, \
               WeatherData *boatCT, \
               WeatherData *boatCM, \
               WeatherData *boatVK, \
               WeatherData *boatMV, \
               WeatherData *utcT,   \
               WeatherData *utcD,   \
               WeatherData *waterTF, \
               WeatherData *waterDF, \
               WeatherData *posLatD, \
               WeatherData *posLatM, \
               WeatherData *posLonD, \
               WeatherData *posLonM) :
    QObject(parent)
{

 //   nmeaStrings->QStringList()  append(QString("WIMDA"));
//    nmeaStrings->append(QString("WIMWV"));
    nmeaStrings << "WIMWD" << "WIMDA" << "WIMWV" << "HCHDG" << "GPVTG" << "GPZDA" << "YXMTW" << "SDDBT" << "GPGGA";
    baroPressB=baro;
    airTempC=airTC;
    airTempF=airTF;
    dpTempC=dpTC;
    dpTempF=dpTF;
    rhPercent=rhP;
    windDirT=windDT;
    windDirRT=windDRT;
    windDirM=windDM;
    windSpdK=windSK;
    windSpdRK=windSRK;
    windSpdM=windSM;
    boatHdgM=boatHM;
    boatCmgT=boatCT;
    boatCmgM=boatCM;
    boatVmgK=boatVK;
    boatMagVar=boatMV;
    utcTime=utcT;
    utcDay=utcD;
    waterTempF=waterTF;
    waterDepthF=waterDF;
    positionLatD=posLatD;
    positionLatM=posLatM;
    positionLonD=posLonD;
    positionLonM=posLonM;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readPort()));
//    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
 //   QObject::connect(&baroPressB,SIGNAL(stringChanged(QString)),MainWindow.ui,SLOT(setBaro(QString)));
    //QObject::connect(,SIGNAL())
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ihost,iport.toInt());
 //   qDebug() << "Starting readPort...";
 //   readPort();
}

