/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QComboBox *COMComboBox;
    QLabel *COMLabel;
    QLabel *buadRateLabel_2;
    QLineEdit *buadRateLineEdit;
    QPushButton *connectPushbutton;
    QLabel *speedLabel;
    QLabel *positionLabel;
    QLineEdit *speedLineEdit;
    QLineEdit *positionLineEdit;
    QPushButton *updatePushbutton;
    QPushButton *setPushbutton;
    QPlainTextEdit *console;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(682, 527);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        COMComboBox = new QComboBox(centralwidget);
        COMComboBox->setObjectName("COMComboBox");
        COMComboBox->setGeometry(QRect(550, 50, 72, 24));
        COMLabel = new QLabel(centralwidget);
        COMLabel->setObjectName("COMLabel");
        COMLabel->setGeometry(QRect(480, 50, 49, 16));
        buadRateLabel_2 = new QLabel(centralwidget);
        buadRateLabel_2->setObjectName("buadRateLabel_2");
        buadRateLabel_2->setGeometry(QRect(480, 80, 61, 16));
        buadRateLineEdit = new QLineEdit(centralwidget);
        buadRateLineEdit->setObjectName("buadRateLineEdit");
        buadRateLineEdit->setGeometry(QRect(550, 80, 71, 24));
        connectPushbutton = new QPushButton(centralwidget);
        connectPushbutton->setObjectName("connectPushbutton");
        connectPushbutton->setGeometry(QRect(560, 110, 80, 24));
        speedLabel = new QLabel(centralwidget);
        speedLabel->setObjectName("speedLabel");
        speedLabel->setGeometry(QRect(30, 60, 81, 16));
        positionLabel = new QLabel(centralwidget);
        positionLabel->setObjectName("positionLabel");
        positionLabel->setGeometry(QRect(30, 90, 81, 16));
        speedLineEdit = new QLineEdit(centralwidget);
        speedLineEdit->setObjectName("speedLineEdit");
        speedLineEdit->setGeometry(QRect(110, 60, 71, 24));
        positionLineEdit = new QLineEdit(centralwidget);
        positionLineEdit->setObjectName("positionLineEdit");
        positionLineEdit->setGeometry(QRect(110, 90, 71, 24));
        updatePushbutton = new QPushButton(centralwidget);
        updatePushbutton->setObjectName("updatePushbutton");
        updatePushbutton->setGeometry(QRect(470, 110, 80, 24));
        setPushbutton = new QPushButton(centralwidget);
        setPushbutton->setObjectName("setPushbutton");
        setPushbutton->setGeometry(QRect(80, 120, 80, 24));
        console = new QPlainTextEdit(centralwidget);
        console->setObjectName("console");
        console->setGeometry(QRect(60, 280, 551, 201));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 682, 21));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        COMLabel->setText(QCoreApplication::translate("MainWindow", "COM:", nullptr));
        buadRateLabel_2->setText(QCoreApplication::translate("MainWindow", "Buad Rate:", nullptr));
        connectPushbutton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "Speed (RPM):", nullptr));
        positionLabel->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        updatePushbutton->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        setPushbutton->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
