#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QTcpSocket>
#include <QStringList>
#include "weatherdata.h"

QT_BEGIN_NAMESPACE
//class QDialogButtonBox;
//class QLabel;
//class QLineEdit;
//class QPushButton;
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

//namespace MainWindow
//namespace {
//class MainWindow;
//}

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = 0, QString ihost="", QString iport="0", \
            WeatherData *baro=0, \
            WeatherData *airTC=0, \
            WeatherData *airTF=0, \
            WeatherData *dpTC=0, \
            WeatherData *dpTF=0, \
            WeatherData *rhP=0, \
            WeatherData *windDT=0, \
            WeatherData *windDRT=0, \
            WeatherData *windDM=0, \
            WeatherData *windSK=0, \
            WeatherData *windSRK=0, \
            WeatherData *windSM=0, \
            WeatherData *boatHM=0, \
            WeatherData *boatCT=0, \
            WeatherData *boatCM=0, \
            WeatherData *boatVK=0, \
            WeatherData *boatMV=0, \
            WeatherData *utcT=0, \
            WeatherData *utcD=0, \
            WeatherData *waterTF=0, \
            WeatherData *waterDF=0, \
            WeatherData *posLatD=0, \
            WeatherData *posLatM=0, \
            WeatherData *posLonD=0, \
            WeatherData *posLonM=0 );

    //Parser(QWidget *parent = 0);

signals:
//    void baroChange(double newValue);
    //baroPressB.changeValue(double newValue);
    //void readWindSpd();
    //other data too
    //void windSpdK.changeValue(QString newValue);
//    double changeBaroPress(double baroPress);
//    double changeAirTempC(double airTempC);
//    double changeDpTempC(double dpTempC);
//    double changeRhPercent(double rhPercent);

public slots:
//    void readRaw();
    //void startParser();

private slots:
    //void readPort(WeatherData *baroPressB);
    void readPort();

private:
    QTcpSocket *tcpSocket;
    quint16 blockSize;
    QStringList nmeaStrings;
    WeatherData *baroPressB;
    WeatherData *airTempC;
    WeatherData *airTempF;
    WeatherData *dpTempC;
    WeatherData *dpTempF;
    WeatherData *rhPercent;
    WeatherData *windDirT;
    WeatherData *windDirRT;
    WeatherData *windDirM;
    WeatherData *windSpdK;
    WeatherData *windSpdRK;
    WeatherData *windSpdM;
    WeatherData *boatHdgM;
    WeatherData *boatCmgT;
    WeatherData *boatCmgM;
    WeatherData *boatVmgK;
    WeatherData *boatMagVar;
    WeatherData *utcTime;
    WeatherData *utcDay;
    WeatherData *waterTempF;
    WeatherData *waterDepthF;
    WeatherData *positionLatD;
    WeatherData *positionLatM;
    WeatherData *positionLonD;
    WeatherData *positionLonM;
};

#endif // PARSER_H
