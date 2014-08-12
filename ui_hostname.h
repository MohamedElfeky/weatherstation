/********************************************************************************
** Form generated from reading UI file 'hostname.ui'
**
** Created: Tue Apr 1 21:52:46 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOSTNAME_H
#define UI_HOSTNAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Hostname
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEditHostname;
    QLineEdit *lineEditHostport;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButtonGetData;
    QTextBrowser *textBrowser;
    QPushButton *pushButtonDefaultPort;
    QLabel *statusLabel;

    void setupUi(QDialog *Hostname)
    {
        if (Hostname->objectName().isEmpty())
            Hostname->setObjectName(QString::fromUtf8("Hostname"));
        Hostname->resize(480, 640);
        buttonBox = new QDialogButtonBox(Hostname);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 600, 461, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEditHostname = new QLineEdit(Hostname);
        lineEditHostname->setObjectName(QString::fromUtf8("lineEditHostname"));
        lineEditHostname->setGeometry(QRect(130, 10, 331, 24));
        lineEditHostport = new QLineEdit(Hostname);
        lineEditHostport->setObjectName(QString::fromUtf8("lineEditHostport"));
        lineEditHostport->setGeometry(QRect(130, 50, 171, 24));
        label = new QLabel(Hostname);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 111, 16));
        label_2 = new QLabel(Hostname);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 60, 91, 16));
        pushButtonGetData = new QPushButton(Hostname);
        pushButtonGetData->setObjectName(QString::fromUtf8("pushButtonGetData"));
        pushButtonGetData->setGeometry(QRect(20, 100, 151, 25));
        textBrowser = new QTextBrowser(Hostname);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 140, 451, 451));
        pushButtonDefaultPort = new QPushButton(Hostname);
        pushButtonDefaultPort->setObjectName(QString::fromUtf8("pushButtonDefaultPort"));
        pushButtonDefaultPort->setGeometry(QRect(310, 50, 151, 21));
        statusLabel = new QLabel(Hostname);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(180, 100, 281, 21));

        retranslateUi(Hostname);
        QObject::connect(buttonBox, SIGNAL(accepted()), Hostname, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Hostname, SLOT(reject()));

        QMetaObject::connectSlotsByName(Hostname);
    } // setupUi

    void retranslateUi(QDialog *Hostname)
    {
        Hostname->setWindowTitle(QApplication::translate("Hostname", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Hostname", "Host Name or IP:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Hostname", "Port Number:", 0, QApplication::UnicodeUTF8));
        pushButtonGetData->setText(QApplication::translate("Hostname", "Check Configuration", 0, QApplication::UnicodeUTF8));
        pushButtonDefaultPort->setText(QApplication::translate("Hostname", "Use Default", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QApplication::translate("Hostname", "Status", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Hostname: public Ui_Hostname {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOSTNAME_H
