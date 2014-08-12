#ifndef WEATHERDATA_H
#define WEATHERDATA_H

#include <QObject>
#include "QLocale"
//#include <QSoundEffect>
//#include <QAudioOutput>
//#include <QSound>

class WeatherData : public QObject
{
    Q_OBJECT
public:
    explicit WeatherData(QObject *parent = 0);
    double value() const { return m_value; }
    double offsetValue() const { return offsetVal; }
    QString string() const { return QString("%1").arg(m_value,valLeftPad,'f',valPrecision,QChar('0')); }
    int setValue(double newValue);
    void setName(QString &name);
    double max() const { return maxVal; }
    double min() const { return minVal; }
    double precision() const { return valPrecision; }
    double padding() const { return valLeftPad; }
    double maxAllowedVal() const { return maxAllowed; }
    double minAllowedVal() const { return minAllowed; }
    double defaultValue() const { return defaultVal; }
    double reset(); // const { return m_value; }
    bool checkInitialized() const { return isInitialized; }
    void setPrecision(int newValue);
    void setLeftPad(int newValue);
    void setAvgNumVals(int newValue);
    void setIsCircular(bool newValue);
    void setOffsetVal(double newValue);
    void setScalarVal(double newValue);
public slots:
    //void setValue(int newValue);
    void changeValue(double newValue);
    void setMinAllowed(double newMin);
    void setMaxAllowed(double newMaxl);
    void setDefaultVal(double newValue);
    void resetVal();
    void setAlarm(bool newValue);
    void setAlarmLow(QString newValue);
    void setAlarmHigh(QString newValue);
    void setValueString(QString newValue);
    void setOffsetString(QString newValue);
    void setOffsetNegString(QString newValue);
signals:
//    void valueChanged(int newValue);
    void valueChanged(double newValue);
    void stringChanged(QString newStr);
    void maxChanged(double newMax);
    void stringMaxChanged(QString newStr);
    void minChanged(double newMin);
    void stringMinChanged(QString newStr);
    void valIncreasing(bool isIncreasing);
    void valDecreasing(bool isDecreasing);
    void alarmLowChanged(QString newValue);
    void alarmHighChanged(QString newValue);
    void alarmTriggered(bool newValue);
    //void alarmTriggered();
private:
    double defaultVal;
    double m_value;
    double minAllowed;
    double maxAllowed;
    double maxVal;
    double minVal;
    QString str;
    bool isInitialized;
    bool isCircular;
    bool alarmEnable;
    bool alarmOn;
    double alarmHighThreshold;
    double alarmLowThreshold;
    bool isIncreasing;
    bool isDecreasing;
    int valPrecision;
    int valLeftPad;
    int avgNumVals;
    double offsetVal;
    double scalarVal;
    int carry;

 //   QSound * alarmSound;

};

#endif // WEATHERDATA_H
