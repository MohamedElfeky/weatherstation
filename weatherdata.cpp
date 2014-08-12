#include "weatherdata.h"
#include "QDebug"
//#include <QSoundEffect>
#include <QSound>
#include <QApplication>
#include <QProcess>

WeatherData::WeatherData(QObject *parent) :
    QObject(parent)
{
//    qDebug() << "Setting up new variable";
    isInitialized=false;
    isCircular=false;
    defaultVal=0.0;
    m_value=defaultVal;
    minAllowed=-10000000.0;
    maxAllowed= 10000000.0;
    maxVal=defaultVal;
    minVal=defaultVal;
    valPrecision=1;
    valLeftPad=0;
    avgNumVals=1;
    isIncreasing=false;
    isDecreasing=false;
    alarmEnable=false;
    alarmOn=false;
    alarmHighThreshold=maxAllowed;
    alarmLowThreshold=minAllowed;
    offsetVal=0;
    scalarVal=1;
  //  alarmSound = new QSound
  //  alarmSound.fileName("/usr/share/sounds/error.wav");
}
void WeatherData::setName(QString &datastr){
    str = datastr;
}
void WeatherData::setValueString(QString newValue){
    setValue(QString(newValue).toDouble());
}
void WeatherData::setOffsetString(QString newValue){
    setOffsetVal(QString(newValue).toDouble());
}
void WeatherData::setOffsetNegString(QString newValue){
    setOffsetVal(- QString(newValue).toDouble());
}
void WeatherData::changeValue(double newValue){
    setValue(newValue);
    // the below only changes if newValue is in range the setValue function sets as high or low as possible to be still in range

    /*if (m_value != newValue) {
      if (( newValue >= min_allowed ) && ( newValue <= max_allowed)){
        m_value = newValue;
        emit valueChanged(m_value);
        strval = QString::number(m_value);
        emit stringChanged(strval);
      }
    }*/
}
int WeatherData::setValue(double newValue) {//should we always emit if not initialized??
    QString strval;
    double limitNewValue;
    double temp_val;
    carry=0;
    limitNewValue = scalarVal * ( newValue + offsetVal );
#ifdef linux
  #ifdef RPI
    QString alarmSoundCommand="/home/david/bin/pulsegpio.sh";
  #else
    QString alarmSoundCommand="aplay ";
    QString alarmSoundFile="/usr/share/sounds/info.wav /usr/share/sounds/error.wav ";
    //QString alarmSoundFileList=alarmSoundFile;
    int alarmRepeats=1;
    for ( int i=0;i<alarmRepeats;i++) alarmSoundCommand=alarmSoundCommand+alarmSoundFile;
  #endif
#endif

    if ( isCircular ) {
      while ( limitNewValue < minAllowed ) {
//          qDebug() << "val below min: " << limitNewValue;
          limitNewValue += (maxAllowed - minAllowed);
          carry--;
//          qDebug() << "New val: " << limitNewValue << " with carry " << carry;
      }
      while ( limitNewValue > maxAllowed ) {
//          qDebug() << "val above max: " << limitNewValue;
          limitNewValue -= (maxAllowed - minAllowed);
          carry++;
//          qDebug() << "New val: " << limitNewValue << " with carry " << carry;
      }
    } else {
      if ( limitNewValue <= minAllowed ) { limitNewValue = minAllowed; }
      else if ( limitNewValue >= maxAllowed ) { limitNewValue = maxAllowed;}
    }
    //    qDebug() << "Checking for initialization=" << isInitialized;
    if ( !isInitialized ) {
//        qDebug() << "Initializing";
        isInitialized = true;
        if ( m_value != limitNewValue ) {
          m_value = limitNewValue;
          emit valueChanged(m_value);
          //strval = QString::number(m_value,'f',valPrecision);
          strval = QString("%1").arg(m_value,valLeftPad,'f',valPrecision,QChar('0'));
          emit stringChanged(strval);
        }
        if ( minVal != limitNewValue ) {
          minVal = limitNewValue;
          emit minChanged(minVal);
          //strval = QString::number(minVal,'f',valPrecision);
          strval = QString("%1").arg(minVal,valLeftPad,'f',valPrecision,QChar('0'));
         //strval = QString::number(minVal);
          emit stringMinChanged(strval);
      }
      if ( maxVal != limitNewValue ) {
          maxVal = limitNewValue;
          emit maxChanged(maxVal);
          //strval = QString::number(maxVal);
          //strval = QString::number(maxVal,'f',valPrecision);
          strval = QString("%1").arg(m_value,valLeftPad,'f',valPrecision,QChar('0'));
          emit stringMaxChanged(strval);
      }

    } else {

//        qDebug() << "Changing " << m_value << " to new Value: " << newValue;
//        qDebug() << "Range is: " << minAllowed << " to " << maxAllowed;
         //if ( newValue <= minAllowed ) { m_value = ( m_value + minAllowed ) / 2;}
         //else if ( newValue >= maxAllowed ) { m_value = ( m_value + maxAllowed ) / 2;}
         //else {
      //if ( avgNumVals < 2 ) m_value = limitNewValue;
      //else {
      temp_val = ( ( m_value * ( avgNumVals - 1 ) ) + limitNewValue ) / avgNumVals;// }
      //}
      if ( m_value != temp_val ) {
          /*
          if ( m_value < temp_val ) {
              if ( !isDecreasing ) {
                isDecreasing=true;
                emit valDecreasing(isDecreasing);
              }
              if ( isIncreasing ){
                isIncreasing=false;
                emit valIncreasing(isIncreasing);
              }
          } else { //m_value is increasing
              if ( isDecreasing ){
                isDecreasing=false;
                emit valDecreasing(isDecreasing);
              }
              if ( !isIncreasing ){
                isIncreasing=true;
                emit valIncreasing(isIncreasing);
              }
          }
          */
         m_value = temp_val;
         emit valueChanged(m_value);
         strval = QString::number(m_value,'f',valPrecision);
         //strval = QString::number(m_value,'f');
//         qDebug() << "From " << m_value << " New string: " << strval;
        emit stringChanged(strval);
         //emit stringChanged(QString::number(m_value,'f',1));
        if ( alarmEnable ) {
            if ( isCircular && ( alarmHighThreshold < alarmLowThreshold )) {
                if ( ( m_value >= alarmHighThreshold ) && ( m_value < alarmLowThreshold ) ) alarmOn = true;
                else alarmOn = false;
            } else {
                if ( ( m_value >= alarmHighThreshold ) || ( m_value < alarmLowThreshold ) ) alarmOn = true;
                else alarmOn = false;
            }
            if ( alarmOn ) {
                //if ( QSound::isAvailable() ) {
                  //qDebug() << "Alarm Sounding...";
                  emit alarmTriggered(true);
#ifdef linux
                  QProcess *alarmSound = new QProcess(this);
                  //QString file = "beep";
                  //QString file = "aplay /usr/share/sounds/error.wav";
                  alarmSound->start(alarmSoundCommand);
#else
                  //make sound here??
                  //QSound::play("/usr/share/sounds/warning.wav");

                  //QSound alarmSound("/usr/share/sounds/error.wav");

                  //alarmSound.setLoops(1);
                  //alarmSound.play();


                  QApplication::beep();
                  //beep();
                //} else qDebug() << "No System Sound for Alarm.";
#endif
            }
        }
      } /*else { //not changing
          if ( isDecreasing ){
            isDecreasing=false;
            emit valDecreasing(isDecreasing);
          }
          if ( isIncreasing ){
            isIncreasing=false;
            emit valIncreasing(isIncreasing);
      }*/
//      qDebug() << "Checking max min";
      //NEED LOGIC FOR CIRCULAR DATA HERE!!
      if ( limitNewValue < minVal ) {
          minVal = limitNewValue;
          emit minChanged(minVal);
         strval = QString::number(minVal,'f',valPrecision);
         //strval = QString::number(minVal);
          emit stringMinChanged(strval);
      }
      if ( limitNewValue > maxVal ) {
        maxVal = limitNewValue;
        emit maxChanged(maxVal);
         strval = QString::number(maxVal,'f',valPrecision);
         //strval = QString::number(maxVal);
        emit stringMaxChanged(strval);
      }
    }
    //return m_value;
    return carry;
}
void WeatherData::setIsCircular(bool newValue){
    isCircular = newValue;
}
void WeatherData::setAlarm(bool newValue){
    if ( newValue ) {    emit alarmTriggered(false); }
    alarmEnable = newValue;
    QString tempStr;
    tempStr=QString::number(alarmLowThreshold);
    emit alarmLowChanged(tempStr);
    tempStr=QString::number(alarmHighThreshold);
    emit alarmHighChanged(tempStr);
}
void WeatherData::setPrecision(int newValue){
    if ( newValue >= 0 ) valPrecision = newValue;
}
void WeatherData::setLeftPad(int newValue){
    if ( newValue >= 0 ) valLeftPad = newValue;
}
void WeatherData::setOffsetVal(double newValue){
    offsetVal = newValue;
}
void WeatherData::setScalarVal(double newValue){
    scalarVal = newValue;
}
void WeatherData::setAvgNumVals(int newValue){
    if ( newValue >= 1 ) avgNumVals = newValue;
}
void WeatherData::setDefaultVal(double newValue){
    if (( newValue >= minAllowed ) && ( newValue <= maxAllowed)) defaultVal = newValue;
}
void WeatherData::setMinAllowed(double newMin){
    if ( newMin < maxAllowed ) minAllowed = newMin;
    alarmLowThreshold=minAllowed;
}
void WeatherData::setMaxAllowed(double newMax){
    if ( newMax > minAllowed ) maxAllowed = newMax;
    alarmHighThreshold=maxAllowed;
}
void WeatherData::setAlarmLow(QString newString){
//    QString chgStr;
    double newVal;
    newVal=newString.toDouble();
    if (( newVal >= minAllowed ) && (newVal <= maxAllowed )) {
        alarmLowThreshold = newVal;
        if ( !isCircular && ( newVal > alarmHighThreshold )) {
            alarmHighThreshold = newVal;
            emit alarmHighChanged(newString);
        }
        emit alarmTriggered(false);
    } else { emit alarmLowChanged(QString::number(alarmLowThreshold));
        //emit alarmLowChanged(chgStr);
    }
}
void WeatherData::setAlarmHigh(QString newString){
//    QString tempStr;
//    tempStr = newString;
    double newVal;
    newVal=newString.toDouble();
    if (( newVal >= minAllowed ) && (newVal <= maxAllowed )) {
        alarmHighThreshold = newVal;
        if ( !isCircular && ( newVal < alarmLowThreshold )) {
            alarmLowThreshold = newVal;
            emit alarmLowChanged(newString);
        }
        emit alarmTriggered(false);
    } else {emit alarmHighChanged(QString::number(alarmHighThreshold));}
}
void WeatherData::resetVal(){
    reset();
}

double WeatherData::reset() {
    QString strval;
    if( m_value != defaultVal ) {
        m_value = defaultVal;
        emit valueChanged(m_value);
        //strval = QString::number(m_value);
        strval = QString::number(m_value,'f',valPrecision);
        emit stringChanged(strval);
    }
    isInitialized = false;
    if ( minVal != defaultVal ) {
        minVal = defaultVal;
        emit minChanged(minVal);
        //strval = QString::number(minVal);
        strval = QString::number(minVal,'f',valPrecision);
        emit stringMinChanged(strval);
    }
    if ( maxVal != defaultVal ) {
        maxVal = defaultVal;
        emit maxChanged(maxVal);
        //strval = QString::number(maxVal);
        strval = QString::number(maxVal,'f',valPrecision);
        emit stringMaxChanged(strval);
    }
    emit alarmTriggered(false);
    return m_value;
}
