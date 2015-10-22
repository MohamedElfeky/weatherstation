#include "mainwindow.h"
#include "hostname.h"
#include "parser.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtGui>
#include "weatherdata.h"
#include "qwt_compass.h"
#include "qwt_dial.h"
#include "qwt_dial_needle.h"
//#include <QtDeclarative>
#include "qwt_compass_rose.h"
#include <QDebug>

#define compiledate __DATE__
#define compiletime __TIME__

//void MainWindow::setBaro(const QString &str)
//{
//    ui->windSpeedLabel->setText(str);
//}

void MainWindow::computeBaroCorrection(double newAirTemp)
{
//    baro correction: babinet's formula (alpha=16000 + 64 Tc
//   P=P0[(alpha-Hm)/(alpha+Hm)]
//   where Tc is temp in C and Hm is height in meters
  double alpha, baroCorrection, mastHeight=20;
  //alpha =  16000 + ( 64 * newAirTemp);
  alpha =  16000 + ( 64 * airTempC->value());
  baroCorrection = (alpha + mastHeight) / (alpha - mastHeight);
  baroPressB->setScalarVal(baroCorrection);
  ui->baroCorrectionFactorVal->setText(QString::number(baroCorrection,'f',6));
}

void MainWindow::setPositionAlarm(bool newState)
{
    positionAlarmSet = newState;
}

void MainWindow::computeDistanceStr(QString newVal)
{
#ifdef linux
  #ifdef RPI
    QString alarmSoundCommand="/home/david/bin/pulsegpio.sh 2";
  #else
    QString alarmSoundCommand="aplay ";
    QString alarmSoundFile="/usr/share/sounds/info.wav /usr/share/sounds/error.wav ";
    //QString alarmSoundFileList=alarmSoundFile;
    int alarmRepeats=5;
    for ( int i=0;i<alarmRepeats;i++) alarmSoundCommand=alarmSoundCommand+alarmSoundFile;
  #endif
#endif

    if ( distanceLatD->checkInitialized() && distanceLatM->checkInitialized() && distanceLonD->checkInitialized() && distanceLonM->checkInitialized() ) {
      computeDistance();
      if ( positionAlarmSet ) {
//          qDebug() << "Check alarm state";
          if ( positionOffsetFeet >= QString(ui->lineEditPositionHigh->text()).toDouble() ) {
               ui->radioButtonPositionAlarm->setChecked(true);
               qDebug() << "Sound position high alarm";
#ifdef linux
               QProcess *alarmSound = new QProcess(this);
               //QString file = "beep";
               alarmSound->start(alarmSoundCommand);
#else
               QApplication::beep();
               //beep();
#endif
          }
          if ( positionOffsetFeet < QString(ui->lineEditPositionLow->text()).toDouble() ) {
               ui->radioButtonPositionAlarm->setChecked(true);
               qDebug() << "Sound position low alarm";
#ifdef linux
               QProcess *alarmSound = new QProcess(this);
               //QString file = "beep";
               alarmSound->start(alarmSoundCommand);
#else
               QApplication::beep();
               //beep();
#endif
          }
      }
    }
}
void MainWindow::computeInitialDistance()
{
      positionMaxOffsetFeet=0;
      ui->positionMaxDistanceF->setText(QString::number(positionMaxOffsetFeet,'f',1));
      this->computeDistance();
}

void MainWindow::computeDistance()
{
    int carry;
    double nmToFeet=6015;
    double hzNm;
    double vertNm;
    double posLatD=positionLatD->value();
    double posLatM=positionLatM->value();
    double posLonD=positionLonD->value();
    double posLonM=positionLonM->value();
    ui->radioButtonPositionUpdate->toggle();
    //qDebug() << "latD offset: " << distanceLatD->offsetValue();
    //qDebug() << "latM offset: " << distanceLatM->offsetValue();
    //qDebug() << "lonD offset: " << distanceLonD->offsetValue();
    //qDebug() << "lonM offset: " << distanceLonM->offsetValue();
    carry = distanceLatM->setValue(posLatM);
    distanceLatD->setValue(posLatD);
    vertNm = ((( distanceLatD->value() + carry ) * 60 ) + distanceLatM->value() );
    //qDebug() << "LatD: " << distanceLatD->value() << " LatM: " << distanceLatM->value();
    //qDebug() << "Vert minutes: " << vertNm << " Carry: " << carry;
    carry = distanceLonM->setValue(posLonM);
    distanceLonD->setValue(posLonD);
    hzNm = ((( distanceLonD->value() + carry ) * 60 ) + distanceLonM->value()) * cos( ( ( posLatD + ( posLatM / 60 )) / 180 ) * 3.14 );
    //qDebug() << "LonD: " << distanceLonD->value() << " LonM: " << distanceLonM->value() << " cos: " << cos( ( ( posLatD + ( posLatM / 60 )) / 180 ) * 3.14 );
    //qDebug() << "Hz minutes: " << hzNm << " Carry: " << carry;
    positionOffsetFeet = nmToFeet  * sqrt(( vertNm * vertNm ) + ( hzNm * hzNm ));
    if ( positionOffsetFeet >= positionMaxOffsetFeet ) {
        positionMaxOffsetFeet = positionOffsetFeet;
        ui->positionMaxDistanceF->setText(QString::number(positionMaxOffsetFeet,'f',1));
    }
    ui->positionDistanceF->setText(QString::number(positionOffsetFeet,'f',1));
    ui->positionNSDistanceF->setText(QString::number(vertNm * nmToFeet,'f',1));
    ui->positionWEDistanceF->setText(QString::number(- hzNm * nmToFeet,'f',1));
}

void MainWindow::setRefPosHere()
{
    positionRefLatD->setValue(positionLatD->value());
    positionRefLatM->setValue(positionLatM->value());
    positionRefLonD->setValue(positionLonD->value());
    positionRefLonM->setValue(positionLonM->value());
    distanceLatD->setOffsetVal(- positionRefLatD->value());
    distanceLatM->setOffsetVal(- positionRefLatM->value());
    distanceLonD->setOffsetVal(- positionRefLonD->value());
    distanceLonM->setOffsetVal(- positionRefLonM->value());
    ui->lineEditRefPosLatD->setText(positionRefLatD->string());
    ui->lineEditRefPosLatM->setText(positionRefLatM->string());
    ui->lineEditRefPosLonD->setText(positionRefLonD->string());
    ui->lineEditRefPosLonM->setText(positionRefLonM->string());
    positionMaxOffsetFeet=0;
    ui->positionMaxDistanceF->setText(QString::number(positionMaxOffsetFeet,'f',1));
    this->computeDistance();
}

QString MainWindow::formatTime(double newVal)
{
    int hour, minute, second;
    QString hourStr, minStr, secStr;
    hour = int(newVal) / 10000;
    minute = (int(newVal) - ( hour * 10000)) / 100;
    second = (int(newVal) - ( hour * 10000) - ( minute * 100));
    hourStr = QString("%1").arg(hour,2,'d',0,QChar('0'));
    minStr = QString("%1").arg(minute,2,'d',0,QChar('0'));
    secStr = QString("%1").arg(second,2,'d',0,QChar('0'));
    //qDebug() <<  "hour " << hourStr << " minute " << minStr << " second " << secStr;
    return hourStr+":"+minStr+":"+secStr;
}

void MainWindow::outputTime(double newVal)
{
    ui->utcTimeVal->setText(utcDay->string()+" "+formatTime(newVal));
}

void MainWindow::globalReset()
{
    if ( utcTime->checkInitialized() ) {
        ui->globalResetVal->setText(utcDay->string()+" "+formatTime(utcTime->value()));
    } else {
        ui->globalResetVal->setText("Not Avail");
    }
    windSpdK->reset();
    windSpdRK->reset();
    windDirT->reset();
    windDirRT->reset();
    airTempF->reset();
    waterTempF->reset();
    waterDepthF->reset();
    dpTempF->reset();
    rhPercent->reset();
    baroPressB->reset();
    boatVmgK->reset();
    boatHdgM->reset();
    boatCmgM->reset();
}

void MainWindow::baroListVals(QString newVal)
{
  int hour;
  int min;
  if ( utcTime->checkInitialized() && ( newVal != "0.00" )) {
    int timeNow=int(utcTime->value());
    hour = timeNow / 10000;
    min = ( timeNow - ( hour * 10000 ) ) / 100;
    if ( lastBaroValUTC == -99 ){
      lastBaroValUTC=timeNow;
      lastBaroUTCHour = hour;
      ui->textBrowserBaro->append(utcDay->string()+" "+QString("%1").arg(hour,2,'d',0,QChar('0'))+":"+QString("%1").arg(min,2,'d',0,QChar('0'))+" "+newVal);
//      ui->textBrowserBaro->append(QString("%1").arg(utcDay->value(),2,'d',0,QChar('0'))+" "+QString("%1").arg(hour,2,'d',0,QChar('0'))+":"+QString("%1").arg(min,2,'d',0,QChar('0'))+" "+newVal);
    } else {
      if ( lastBaroUTCHour != hour ){
        lastBaroValUTC = timeNow;
        lastBaroUTCHour = hour;
        ui->textBrowserBaro->append(utcDay->string()+" "+QString("%1").arg(hour,2,'d',0,QChar('0'))+":"+QString("%1").arg(min,2,'d',0,QChar('0'))+" "+newVal);
//        ui->textBrowserBaro->append(QString("%1").arg(utcDay->value(),2,'d',0,QChar('0'))+" "+QString("%1").arg(hour,2,'d',0,QChar('0'))+":"+QString("%1").arg(min,2,'d',0,QChar('0'))+" "+newVal);
      }
    }
  } //else qDebug() << "Time not initialized";
}

void MainWindow::setHostname()
{
    QSettings settings;
    Hostname * editHost;
    editHost = new Hostname(this, host, port);
    editHost->setWindowTitle(tr("Change Airmar Hostname"));
    bool ok = editHost->exec();
    if ( ok ) {
        host = editHost->lineEditHostname->text();
        port = editHost->lineEditHostport->text();
//        ui->lineEditHostname->setText(host);
//        ui->lineEditPort->setText(port);
//        ui->hostLabel->setText(tr("Server Host is: ")+host);
//        ui->portLabel->setText(tr("Airmar Port is: ")+port);
        ui->hostLabel->setText(host);
        ui->portLabel->setText(port);
        ipAddress = host;
        settings.setValue("host", host);
        settings.setValue("port", port);
    }
}

void MainWindow::startParser()
{
    runParser = new Parser(this, host, port, \
                           baroPressB, \
                           airTempC, \
                           airTempF, \
                           dpTempC, \
                           dpTempF, \
                           rhPercent, \
                           windDirT, \
                           windDirRT, \
                           windDirM, \
                           windSpdK, \
                           windSpdRK, \
                           windSpdM, \
                           boatHdgM, \
                           boatCmgT, \
                           boatCmgM, \
                           boatVmgK, \
                           boatMagVar, \
                           utcTime, \
                           utcDay, \
                           waterTempF, \
                           waterDepthF, \
                           positionLatD, \
                           positionLatM, \
                           positionLonD, \
                           positionLonM );
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkSession(0)
{
    lastBaroValUTC=-99;
    positionMaxOffsetFeet=0;
    ui->setupUi(this);
    setWindowTitle(tr("Airmar Weather Client: Compiled on ")+compiledate+" at "+compiletime);
    QSettings settings;
    host = settings.value("host").toString();
    port = settings.value("port").toString();
    ui->hostLabel->setText(host);
    ui->portLabel->setText(port);
//    ui->hostLabel->setText(tr("Server Host is: ")+host);
//    ui->portLabel->setText(tr("Airmar Port is: ")+port);
    //Initialize weather data:
    baroPressB = new WeatherData();
    baroPressB->setPrecision(2);
    baroPressB->setAvgNumVals(100);
    airTempC = new WeatherData();
    airTempF = new WeatherData();
    airTempF->setAvgNumVals(10);
    dpTempC = new WeatherData();
    dpTempF = new WeatherData();
    dpTempF->setAvgNumVals(10);
    rhPercent = new WeatherData();
    rhPercent->setAvgNumVals(10);
    rhPercent->setMinAllowed(0);
    rhPercent->setMaxAllowed(100);
    windDirT = new WeatherData();
    windDirT->setIsCircular(true);
    windDirT->setMinAllowed(0);
    windDirT->setMaxAllowed(360);
    windDirRT = new WeatherData();
    windDirRT->setIsCircular(true);
    windDirRT->setMinAllowed(0);
    windDirRT->setMaxAllowed(360);
    windDirM = new WeatherData();
    windDirM->setIsCircular(true);
    windDirM->setMinAllowed(0);
    windDirM->setMaxAllowed(360);
    windSpdK = new WeatherData();
    windSpdK->setMinAllowed(0.0);
    windSpdRK = new WeatherData();
    windSpdRK->setMinAllowed(0.0);
    windSpdM = new WeatherData();
    windSpdM->setMinAllowed(0.0);
    boatHdgM = new WeatherData();
    boatHdgM->setIsCircular(true);
    boatHdgM->setMinAllowed(0.0);
    boatHdgM->setMaxAllowed(360.0);
    boatCmgT = new WeatherData();
    boatCmgT->setIsCircular(true);
    boatCmgT->setMinAllowed(0.0);
    boatCmgT->setMaxAllowed(360.0);
    boatCmgM = new WeatherData();
    boatCmgM->setIsCircular(true);
    boatCmgM->setMinAllowed(0.0);
    boatCmgM->setMaxAllowed(360.0);
    boatVmgK = new WeatherData();
    boatVmgK->setMinAllowed(0.0);
    boatMagVar = new WeatherData();
    utcTime = new WeatherData();
    utcTime->setPrecision(0);
    utcTime->setLeftPad(6);
    utcDay = new WeatherData();
    utcDay->setPrecision(0);
    utcDay->setLeftPad(2);
    waterTempF = new WeatherData();
    waterTempF->setPrecision(1);
    waterDepthF = new WeatherData();
    waterDepthF->setMinAllowed(0.0);
    waterDepthF->setOffsetVal(1.9);
    positionLatD = new WeatherData();
    positionLatD->setMinAllowed(-90.0);
    positionLatD->setMaxAllowed(90.0);
    positionLatD->setPrecision(0);
    positionLatM = new WeatherData();
    positionLatM->setMinAllowed(0);
    positionLatM->setMaxAllowed(60);
    positionLatM->setPrecision(4);
    positionLatM->setIsCircular(true);
    positionLonD = new WeatherData();
    positionLonD->setMinAllowed(-180);
    positionLonD->setMaxAllowed(180);
    positionLonD->setIsCircular(true);
    positionLonD->setPrecision(0);
    positionLonM = new WeatherData();
    positionLonM->setMinAllowed(0);
    positionLonM->setMaxAllowed(60);
    positionLonM->setIsCircular(true);
    positionLonM->setPrecision(4);

    positionRefLatD = new WeatherData();
    positionRefLatD->setMinAllowed(-90.0);
    positionRefLatD->setMaxAllowed(90.0);
    positionRefLatD->setPrecision(0);
    positionRefLatM = new WeatherData();
    positionRefLatM->setMinAllowed(0);
    positionRefLatM->setMaxAllowed(60);
    positionRefLatM->setPrecision(4);
    positionRefLatM->setIsCircular(true);
    positionRefLonD = new WeatherData();
    positionRefLonD->setMinAllowed(-180);
    positionRefLonD->setMaxAllowed(180);
    positionRefLonD->setIsCircular(true);
    positionRefLonD->setPrecision(0);
    positionRefLonM = new WeatherData();
    positionRefLonM->setMinAllowed(0);
    positionRefLonM->setMaxAllowed(60);
    positionRefLonM->setIsCircular(true);
    positionRefLonM->setPrecision(4);

    distanceLatD = new WeatherData();
    distanceLatD->setMinAllowed(-90.0);
    distanceLatD->setMaxAllowed(90.0);
    distanceLatD->setPrecision(0);
    distanceLatM = new WeatherData();
    distanceLatM->setMinAllowed(0);
    distanceLatM->setMaxAllowed(60);
    distanceLatM->setPrecision(4);
    distanceLatM->setIsCircular(true);
    distanceLonD = new WeatherData();
    distanceLonD->setMinAllowed(-180);
    distanceLonD->setMaxAllowed(180);
    distanceLonD->setIsCircular(true);
    distanceLonD->setPrecision(0);
    distanceLonM = new WeatherData();
    distanceLonM->setMinAllowed(0);
    distanceLonM->setMaxAllowed(60);
    distanceLonM->setIsCircular(true);
    distanceLonM->setPrecision(4);
    //QObject::connect(&host,SIGNAL()  ui->lineEditHostname)
//    hostLabel = new QLabel(tr("&Server name:"));
//    portLabel = new QLabel(tr("&Server port:"));

    // find out which IP to connect to
    /*
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    host = ipAddress;
    */
//    ui->lineEditHostname->setText(host);
//    ui->lineEditPort->setText(port);

    QObject::connect(ui->pushButtonChangeHost,SIGNAL(clicked()),this,SLOT(setHostname()));

    //Wind Dir
    windDirNeedle = new QwtCompassWindArrow(QwtCompassWindArrow::Style2,Qt::blue,Qt::red)  ;
    ui->Compass->setNeedle(windDirNeedle);
    QwtSimpleCompassRose *rose = new QwtSimpleCompassRose(12,1);
    ui->Compass->setRose(rose);

    //Wind spd
    ui->Dial->setRange(0,50);//  Scale(10,1);
    //ui->Dial->setScale();
    ui->Dial->setScaleArc(20,340);
    //ui->Dial->setObjectName(QString("Knots"));
    //ui->Dial->drawNeedle(painter, center, radius, direction);
//    ui->Dial->drawNeedle(painter, center, 100, 0);
    //    QwtDialNeedle windDirNeedle;
    //    windSpeedNeedle = new QwtDialNeedle;
    windSpeedNeedle=new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow,true,Qt::red,Qt::blue) ;
    ui->Dial->setNeedle(windSpeedNeedle);

    //Rel Wind Dir
    boatRelWindNeedle = new QwtCompassWindArrow(QwtCompassWindArrow::Style2,Qt::blue,Qt::red)  ;
    ui->CompassRelWind->setNeedle(boatRelWindNeedle);
    QwtSimpleCompassRose *roseRelWind = new QwtSimpleCompassRose(12,1);
    ui->CompassRelWind->setRose(roseRelWind);

    //Rel Wind spd
    ui->DialRelWindSpd->setRange(0,50);//  Scale(10,1);
    ui->DialRelWindSpd->setScaleArc(20,340);
    relWindSpeedNeedle=new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow,true,Qt::red,Qt::blue) ;
    ui->DialRelWindSpd->setNeedle(relWindSpeedNeedle);

    //Boat VMG K
    ui->DialBoatSpd->setRange(0,20);//  Scale(10,1);
    ui->DialBoatSpd->setScaleArc(20,340);
    boatSpeedNeedle=new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow,true,Qt::red,Qt::blue) ;
    ui->DialBoatSpd->setNeedle(boatSpeedNeedle);
    QObject::connect(boatVmgK,SIGNAL(valueChanged(double)),ui->DialBoatSpd,SLOT(setValue(double)));

    //Boat CMG T
    boatCmgHdgNeedle=new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow,true,Qt::red,Qt::blue) ;
    ui->CompassCmgT->setNeedle(boatCmgHdgNeedle);
    QwtSimpleCompassRose *roseCmg = new QwtSimpleCompassRose(12,1);
    ui->CompassCmgT->setRose(roseCmg);
    //QObject::connect(boatHdgM,SIGNAL(valueChanged(double)),ui->CompassMagHdg,SLOT()
    QObject::connect(boatCmgM,SIGNAL(valueChanged(double)),ui->CompassCmgT,SLOT(setValue(double)));

    //Boat Mag Hdg
    boatMagHdgNeedle=new QwtDialSimpleNeedle(QwtDialSimpleNeedle::Arrow,true,Qt::red,Qt::blue) ;
    ui->CompassMagHdg->setNeedle(boatMagHdgNeedle);
    QwtSimpleCompassRose *roseHdg = new QwtSimpleCompassRose(12,1);
    ui->CompassMagHdg->setRose(roseHdg);
    //QObject::connect(boatHdgM,SIGNAL(valueChanged(double)),ui->CompassMagHdg,SLOT()
    QObject::connect(boatHdgM,SIGNAL(valueChanged(double)),ui->CompassMagHdg,SLOT(setValue(double)));

    //ui->Dial->needle();

    //connect parser signals to slots here
    QObject::connect(windSpdK,SIGNAL(valueChanged(double)),ui->Dial,SLOT(setValue(double)));
    QObject::connect(windSpdK,SIGNAL(stringChanged(QString)),ui->windSpeedData,SLOT(setText(QString)));
    QObject::connect(windSpdK,SIGNAL(stringMinChanged(QString)),ui->windSpeedMinData,SLOT(setText(QString)));
    QObject::connect(windSpdK,SIGNAL(stringMaxChanged(QString)),ui->windSpeedMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonWindSpd,SIGNAL(clicked()),windSpdK,SLOT(resetVal()));
    QObject::connect(ui->pushButtonWindSpdAlarm,SIGNAL(clicked(bool)),windSpdK,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditWindSpdLow,SIGNAL(textEdited(QString)),windSpdK,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditWindSpdHigh,SIGNAL(textEdited(QString)),windSpdK,SLOT(setAlarmHigh(QString)));
    QObject::connect(windSpdK,SIGNAL(alarmHighChanged(QString)),ui->lineEditWindSpdHigh,SLOT(setText(QString)));
    QObject::connect(windSpdK,SIGNAL(alarmLowChanged(QString)),ui->lineEditWindSpdLow,SLOT(setText(QString)));
    QObject::connect(windSpdK,SIGNAL(alarmTriggered(bool)),ui->radioButtonWindAlarm,SLOT(setChecked(bool)));

    QObject::connect(windSpdRK,SIGNAL(valueChanged(double)),ui->DialRelWindSpd,SLOT(setValue(double)));
    QObject::connect(windSpdRK,SIGNAL(stringChanged(QString)),ui->relWindSpeedData,SLOT(setText(QString)));
    QObject::connect(windSpdRK,SIGNAL(stringMinChanged(QString)),ui->relWindSpeedMinData,SLOT(setText(QString)));
    QObject::connect(windSpdRK,SIGNAL(stringMaxChanged(QString)),ui->relWindSpeedMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonRelWindSpd,SIGNAL(clicked()),windSpdRK,SLOT(resetVal()));
    QObject::connect(ui->pushButtonRelWindSpdAlarm,SIGNAL(clicked(bool)),windSpdRK,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditRelWindSpdLow,SIGNAL(textEdited(QString)),windSpdRK,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditRelWindSpdHigh,SIGNAL(textEdited(QString)),windSpdRK,SLOT(setAlarmHigh(QString)));
    QObject::connect(windSpdRK,SIGNAL(alarmHighChanged(QString)),ui->lineEditRelWindSpdHigh,SLOT(setText(QString)));
    QObject::connect(windSpdRK,SIGNAL(alarmLowChanged(QString)),ui->lineEditRelWindSpdLow,SLOT(setText(QString)));
    QObject::connect(windSpdRK,SIGNAL(alarmTriggered(bool)),ui->radioButtonRelWindSpdAlarm,SLOT(setChecked(bool)));

    QObject::connect(windDirT,SIGNAL(valueChanged(double)),ui->Compass,SLOT(setValue(double)));
    QObject::connect(windDirT,SIGNAL(stringChanged(QString)),ui->windDirData,SLOT(setText(QString)));
    QObject::connect(windDirT,SIGNAL(stringMinChanged(QString)),ui->windDirMinData,SLOT(setText(QString)));
    QObject::connect(windDirT,SIGNAL(stringMaxChanged(QString)),ui->windDirMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonWindDir,SIGNAL(clicked()),windDirT,SLOT(resetVal()));
    QObject::connect(ui->pushButtonWindDirAlarm,SIGNAL(clicked(bool)),windDirT,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditWindDirLow,SIGNAL(textEdited(QString)),windDirT,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditWindDirHigh,SIGNAL(textEdited(QString)),windDirT,SLOT(setAlarmHigh(QString)));
    QObject::connect(windDirT,SIGNAL(alarmHighChanged(QString)),ui->lineEditWindDirHigh,SLOT(setText(QString)));
    QObject::connect(windDirT,SIGNAL(alarmLowChanged(QString)),ui->lineEditWindDirLow,SLOT(setText(QString)));
    QObject::connect(windDirT,SIGNAL(alarmTriggered(bool)),ui->radioButtonWindDirAlarm,SLOT(setChecked(bool)));

    QObject::connect(windDirRT,SIGNAL(valueChanged(double)),ui->CompassRelWind,SLOT(setValue(double)));
    QObject::connect(windDirRT,SIGNAL(stringChanged(QString)),ui->relWindDirData,SLOT(setText(QString)));
    QObject::connect(windDirRT,SIGNAL(stringMinChanged(QString)),ui->relWindDirMinData,SLOT(setText(QString)));
    QObject::connect(windDirRT,SIGNAL(stringMaxChanged(QString)),ui->relWindDirMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonRelWindDir,SIGNAL(clicked()),windDirRT,SLOT(resetVal()));
    QObject::connect(ui->pushButtonRelWindDirAlarm,SIGNAL(clicked(bool)),windDirRT,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditRelWindDirLow,SIGNAL(textEdited(QString)),windDirRT,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditRelWindDirHigh,SIGNAL(textEdited(QString)),windDirRT,SLOT(setAlarmHigh(QString)));
    QObject::connect(windDirRT,SIGNAL(alarmHighChanged(QString)),ui->lineEditRelWindDirHigh,SLOT(setText(QString)));
    QObject::connect(windDirRT,SIGNAL(alarmLowChanged(QString)),ui->lineEditRelWindDirLow,SLOT(setText(QString)));
    QObject::connect(windDirRT,SIGNAL(alarmTriggered(bool)),ui->radioButtonRelWindDirAlarm,SLOT(setChecked(bool)));

    QObject::connect(airTempF,SIGNAL(stringChanged(QString)),ui->airTempData,SLOT(setText(QString)));
    QObject::connect(airTempF,SIGNAL(stringMinChanged(QString)),ui->airTempMinData,SLOT(setText(QString)));
    QObject::connect(airTempF,SIGNAL(stringMaxChanged(QString)),ui->airTempMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonAirT,SIGNAL(clicked()),airTempF,SLOT(resetVal()));
    QObject::connect(ui->pushButtonAirTempAlarm,SIGNAL(clicked(bool)),airTempF,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditAirTempLow,SIGNAL(textEdited(QString)),airTempF,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditAirTempHigh,SIGNAL(textEdited(QString)),airTempF,SLOT(setAlarmHigh(QString)));
    QObject::connect(airTempF,SIGNAL(alarmHighChanged(QString)),ui->lineEditAirTempHigh,SLOT(setText(QString)));
    QObject::connect(airTempF,SIGNAL(alarmLowChanged(QString)),ui->lineEditAirTempLow,SLOT(setText(QString)));
    QObject::connect(airTempF,SIGNAL(alarmTriggered(bool)),ui->radioButtonAirTempAlarm,SLOT(setChecked(bool)));
    QObject::connect(airTempF,SIGNAL(valueChanged(double)),this,SLOT(computeBaroCorrection(double)));

    QObject::connect(waterTempF,SIGNAL(stringChanged(QString)),ui->waterTempData,SLOT(setText(QString)));
    QObject::connect(waterTempF,SIGNAL(stringMinChanged(QString)),ui->waterTempMinData,SLOT(setText(QString)));
    QObject::connect(waterTempF,SIGNAL(stringMaxChanged(QString)),ui->waterTempMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonWaterT,SIGNAL(clicked()),waterTempF,SLOT(resetVal()));

    QObject::connect(waterDepthF,SIGNAL(stringChanged(QString)),ui->waterDepthData,SLOT(setText(QString)));
    QObject::connect(waterDepthF,SIGNAL(stringMinChanged(QString)),ui->waterDepthMinData,SLOT(setText(QString)));
    QObject::connect(waterDepthF,SIGNAL(stringMaxChanged(QString)),ui->waterDepthMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonWaterD,SIGNAL(clicked()),waterDepthF,SLOT(resetVal()));
    QObject::connect(ui->pushButtonWaterDepthAlarm,SIGNAL(clicked(bool)),waterDepthF,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditWaterDepthLow,SIGNAL(textEdited(QString)),waterDepthF,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditWaterDepthHigh,SIGNAL(textEdited(QString)),waterDepthF,SLOT(setAlarmHigh(QString)));
    QObject::connect(waterDepthF,SIGNAL(alarmHighChanged(QString)),ui->lineEditWaterDepthHigh,SLOT(setText(QString)));
    QObject::connect(waterDepthF,SIGNAL(alarmLowChanged(QString)),ui->lineEditWaterDepthLow,SLOT(setText(QString)));
    QObject::connect(waterDepthF,SIGNAL(alarmTriggered(bool)),ui->radioButtonWaterDepthAlarm,SLOT(setChecked(bool)));

    QObject::connect(dpTempF,SIGNAL(stringChanged(QString)),ui->dpTempData,SLOT(setText(QString)));
    QObject::connect(dpTempF,SIGNAL(stringMinChanged(QString)),ui->dpTempMinData,SLOT(setText(QString)));
    QObject::connect(dpTempF,SIGNAL(stringMaxChanged(QString)),ui->dpTempMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonDpT,SIGNAL(clicked()),dpTempF,SLOT(resetVal()));

    QObject::connect(rhPercent,SIGNAL(stringChanged(QString)),ui->rhPercentData,SLOT(setText(QString)));
    QObject::connect(rhPercent,SIGNAL(stringMinChanged(QString)),ui->rhPercentMinData,SLOT(setText(QString)));
    QObject::connect(rhPercent,SIGNAL(stringMaxChanged(QString)),ui->rhPercentMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonRhP,SIGNAL(clicked()),rhPercent,SLOT(resetVal()));

    QObject::connect(baroPressB,SIGNAL(stringChanged(QString)),ui->baroPressData,SLOT(setText(QString)));
    QObject::connect(baroPressB,SIGNAL(stringChanged(QString)),this,SLOT(baroListVals(QString)));
//    QObject::connect(baroPressB,SIGNAL(valIncreasing(bool)) ,ui->baroPressData,SLOT(set)
    QObject::connect(baroPressB,SIGNAL(stringMinChanged(QString)),ui->baroPressMinData,SLOT(setText(QString)));
    QObject::connect(baroPressB,SIGNAL(stringMaxChanged(QString)),ui->baroPressMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonBaro,SIGNAL(clicked()),baroPressB,SLOT(resetVal()));
    QObject::connect(ui->pushButtonBaroAlarm,SIGNAL(clicked(bool)),baroPressB,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditBaroLow,SIGNAL(textEdited(QString)),baroPressB,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditBaroHigh,SIGNAL(textEdited(QString)),baroPressB,SLOT(setAlarmHigh(QString)));
    QObject::connect(baroPressB,SIGNAL(alarmHighChanged(QString)),ui->lineEditBaroHigh,SLOT(setText(QString)));
    QObject::connect(baroPressB,SIGNAL(alarmLowChanged(QString)),ui->lineEditBaroLow,SLOT(setText(QString)));
    QObject::connect(baroPressB,SIGNAL(alarmTriggered(bool)),ui->radioButtonBaroAlarm,SLOT(setChecked(bool)));

    QObject::connect(boatVmgK,SIGNAL(stringChanged(QString)),ui->boatVmgKData,SLOT(setText(QString)));
    QObject::connect(boatVmgK,SIGNAL(stringMinChanged(QString)),ui->boatVmgKMinData,SLOT(setText(QString)));
    QObject::connect(boatVmgK,SIGNAL(stringMaxChanged(QString)),ui->boatVmgKMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonBoatVmgK,SIGNAL(clicked()),boatVmgK,SLOT(resetVal()));
    QObject::connect(ui->pushButtonBoatSogAlarm,SIGNAL(clicked(bool)),boatVmgK,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditBoatSogLow,SIGNAL(textEdited(QString)),boatVmgK,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditBoatSogHigh,SIGNAL(textEdited(QString)),boatVmgK,SLOT(setAlarmHigh(QString)));
    QObject::connect(boatVmgK,SIGNAL(alarmHighChanged(QString)),ui->lineEditBoatSogHigh,SLOT(setText(QString)));
    QObject::connect(boatVmgK,SIGNAL(alarmLowChanged(QString)),ui->lineEditBoatSogLow,SLOT(setText(QString)));
    QObject::connect(boatVmgK,SIGNAL(alarmTriggered(bool)),ui->radioButtonBoatSogAlarm,SLOT(setChecked(bool)));

    QObject::connect(boatHdgM,SIGNAL(stringChanged(QString)),ui->boatHdgMData,SLOT(setText(QString)));
    QObject::connect(boatHdgM,SIGNAL(stringMinChanged(QString)),ui->boatHdgMMinData,SLOT(setText(QString)));
    QObject::connect(boatHdgM,SIGNAL(stringMaxChanged(QString)),ui->boatHdgMMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonBoatHdgM,SIGNAL(clicked()),boatHdgM,SLOT(resetVal()));
    QObject::connect(ui->pushButtonBoatHdgAlarm,SIGNAL(clicked(bool)),boatHdgM,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditBoatHdgLow,SIGNAL(textEdited(QString)),boatHdgM,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditBoatHdgHigh,SIGNAL(textEdited(QString)),boatHdgM,SLOT(setAlarmHigh(QString)));
    QObject::connect(boatHdgM,SIGNAL(alarmHighChanged(QString)),ui->lineEditBoatHdgHigh,SLOT(setText(QString)));
    QObject::connect(boatHdgM,SIGNAL(alarmLowChanged(QString)),ui->lineEditBoatHdgLow,SLOT(setText(QString)));
    QObject::connect(boatHdgM,SIGNAL(alarmTriggered(bool)),ui->radioButtonBoatHdgAlarm,SLOT(setChecked(bool)));

    QObject::connect(boatCmgM,SIGNAL(stringChanged(QString)),ui->boatCmgTData,SLOT(setText(QString)));
    QObject::connect(boatCmgM,SIGNAL(stringMinChanged(QString)),ui->boatCmgTMinData,SLOT(setText(QString)));
    QObject::connect(boatCmgM,SIGNAL(stringMaxChanged(QString)),ui->boatCmgTMaxData,SLOT(setText(QString)));
    QObject::connect(ui->pushButtonBoatCmgT,SIGNAL(clicked()),boatCmgM,SLOT(resetVal()));
    QObject::connect(ui->pushButtonBoatCmgAlarm,SIGNAL(clicked(bool)),boatCmgM,SLOT(setAlarm(bool)));
    QObject::connect(ui->lineEditBoatCmgLow,SIGNAL(textEdited(QString)),boatCmgM,SLOT(setAlarmLow(QString)));
    QObject::connect(ui->lineEditBoatCmgHigh,SIGNAL(textEdited(QString)),boatCmgM,SLOT(setAlarmHigh(QString)));
    QObject::connect(boatCmgM,SIGNAL(alarmHighChanged(QString)),ui->lineEditBoatCmgHigh,SLOT(setText(QString)));
    QObject::connect(boatCmgM,SIGNAL(alarmLowChanged(QString)),ui->lineEditBoatCmgLow,SLOT(setText(QString)));
    QObject::connect(boatCmgM,SIGNAL(alarmTriggered(bool)),ui->radioButtonBoatCmgAlarm,SLOT(setChecked(bool)));

    QObject::connect(ui->pushButtonPositionAlarm,SIGNAL(clicked(bool)),this,SLOT(setPositionAlarm(bool)));

    QObject::connect(positionLatD,SIGNAL(stringChanged(QString)),ui->positionLatDData,SLOT(setText(QString)));
    QObject::connect(positionLatM,SIGNAL(stringChanged(QString)),ui->positionLatMData,SLOT(setText(QString)));
    QObject::connect(positionLonD,SIGNAL(stringChanged(QString)),ui->positionLonDData,SLOT(setText(QString)));
    QObject::connect(positionLonM,SIGNAL(stringChanged(QString)),ui->positionLonMData,SLOT(setText(QString)));

    QObject::connect(positionLatD,SIGNAL(stringChanged(QString)),this,SLOT(computeDistanceStr(QString)));
    QObject::connect(positionLatM,SIGNAL(stringChanged(QString)),this,SLOT(computeDistanceStr(QString)));
    QObject::connect(positionLonD,SIGNAL(stringChanged(QString)),this,SLOT(computeDistanceStr(QString)));
    QObject::connect(positionLonM,SIGNAL(stringChanged(QString)),this,SLOT(computeDistanceStr(QString)));

    QObject::connect(positionRefLatD,SIGNAL(stringChanged(QString)),ui->lineEditRefPosLatD,SLOT(setText(QString)));
    QObject::connect(ui->lineEditRefPosLatD,SIGNAL(textEdited(QString)),distanceLatD,SLOT(setOffsetNegString(QString)));
    QObject::connect(ui->lineEditRefPosLatD,SIGNAL(editingFinished()),this,SLOT(computeInitialDistance()));
    QObject::connect(positionRefLatM,SIGNAL(stringChanged(QString)),ui->lineEditRefPosLatM,SLOT(setText(QString)));
    QObject::connect(ui->lineEditRefPosLatM,SIGNAL(textEdited(QString)),distanceLatM,SLOT(setOffsetNegString(QString)));
    QObject::connect(ui->lineEditRefPosLatM,SIGNAL(editingFinished()),this,SLOT(computeInitialDistance()));
    QObject::connect(positionRefLonD,SIGNAL(stringChanged(QString)),ui->lineEditRefPosLonD,SLOT(setText(QString)));
    QObject::connect(ui->lineEditRefPosLonD,SIGNAL(textEdited(QString)),distanceLonD,SLOT(setOffsetNegString(QString)));
    QObject::connect(ui->lineEditRefPosLonD,SIGNAL(editingFinished()),this,SLOT(computeInitialDistance()));
    QObject::connect(positionRefLonM,SIGNAL(stringChanged(QString)),ui->lineEditRefPosLonM,SLOT(setText(QString)));
    QObject::connect(ui->lineEditRefPosLonM,SIGNAL(textEdited(QString)),distanceLonM,SLOT(setOffsetNegString(QString)));
    QObject::connect(ui->lineEditRefPosLonM,SIGNAL(editingFinished()),this,SLOT(computeInitialDistance()));

    QObject::connect(ui->pushButtonSetRefPosHere,SIGNAL(clicked()),this,SLOT(setRefPosHere()));

    QObject::connect(utcTime,SIGNAL(valueChanged(double)),this,SLOT(outputTime(double)));

    QObject::connect(ui->pushButtonGlobalReset,SIGNAL(clicked()),this,SLOT(globalReset()));

    //background parser here on hitting start button??
    QObject::connect(ui->pushButtonStart,SIGNAL(clicked()),this,SLOT(startParser()));
    ui->pushButtonStart->click();
}



MainWindow::~MainWindow()
{
    delete ui;
}
