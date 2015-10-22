# weatherstation
QT Weather Station that uses NMEA data such as provided by an Airmar PB150
This version is setup to be compiled on a Raspberry Pi 2.
The program can be configured to read data from a local or network port providing serial NMEA data.
There are various alarms that can be set on different types of data including a position alarm (anchor watch) and windspeed alarm.
The alarms can output to a piezo electric buzzer on one of the RPI GPIO ports.
Dynamic data is shown on dials, and more static data is shown as text numbers.  The max and min values are displayed.  Each data can have the max/min values reset, or all values can be reset globally.
Barometric data is also recorded hourly for trending.
