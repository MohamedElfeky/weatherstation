#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTcpSocket>
//#include <QList>
#include "weatherdata.h"
#include "parser.h"
#include "qwt_compass.h"
#include "qwt_dial.h"
#include "qwt_dial_needle.h"

QT_BEGIN_NAMESPACE
//class QDialogButtonBox;
//class QLabel;
//class QLineEdit;
//class QPushButton;
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE


namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow//, public Ui::MainWindow *ui
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//    Ui::MainWindow *ui;
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
    WeatherData *positionRefLatD;
    WeatherData *positionRefLatM;
    WeatherData *positionRefLonD;
    WeatherData *positionRefLonM;
    WeatherData *distanceLatD;
    WeatherData *distanceLatM;
    WeatherData *distanceLonD;
    WeatherData *distanceLonM;

//public slots:
//     void baroPressB.setValue();

private slots:
    void setHostname();
    void startParser();
    void globalReset();
    void baroListVals(QString newVal);
    void outputTime(double newVal);
    QString formatTime(double newVal);
    void setRefPosHere();

//    void requestNewFortune();
//    void readFortune();
//    void displayError(QAbstractSocket::SocketError socketError);
//    void enableGetFortuneButton();
//    void sessionOpened();
public slots:
 //   void setBaro(const QString &str);
    void computeBaroCorrection(double newAirTemp);
    void computeInitialDistance();
    void computeDistance();
    void computeDistanceStr(QString newVal);
    void setPositionAlarm(bool newState);
private:
    Ui::MainWindow *ui;
    QString host;//="localhost";
    QString port;//="27644";
    QString ipAddress;
    Parser * runParser;
    QwtCompassWindArrow *windDirNeedle;
    QwtDialSimpleNeedle *windSpeedNeedle;
    QwtDialSimpleNeedle *boatSpeedNeedle;
    QwtDialSimpleNeedle *boatMagHdgNeedle;
    QwtDialSimpleNeedle *boatCmgHdgNeedle;
    QwtCompassWindArrow *boatRelWindNeedle;
    QwtDialSimpleNeedle *relWindSpeedNeedle;

//    QLabel *hostLabel;
//    QLabel *portLabel;
//    QLineEdit *hostLineEdit;
//    QLineEdit *portLineEdit;
//    QLabel *statusLabel;
////    QPushButton *getFortuneButton;
//    QPushButton *quitButton;
//    QDialogButtonBox *buttonBox;

    QTcpSocket *tcpSocket;
//    QString currentFortune;
//    quint16 blockSize;

    QNetworkSession *networkSession;
    int lastBaroValUTC;
    int lastBaroUTCHour;
    double positionOffsetFeet;
    double positionMaxOffsetFeet;
    bool positionAlarmSet;

};

#endif // MAINWINDOW_H
