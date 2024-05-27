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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *gearRatioLabel;
    QLabel *encoderPulsesLabel;
    QLabel *speedLabel;
    QLabel *positionLabel;
    QLabel *accelerationLabel;
    QLabel *decelerationLabel;
    QLabel *accelerationTimeLabel;
    QLabel *decelerationTimeLabel;
    QLabel *kpLabel;
    QLabel *kiLabel;
    QLabel *kdLabel;
    QVBoxLayout *verticalLayout_5;
    QLineEdit *gearRatioLineEdit;
    QLineEdit *encoderPulsesLineEdit;
    QLineEdit *speedLineEdit;
    QLineEdit *positionLineEdit;
    QLineEdit *accelerationLineEdit;
    QLineEdit *decelerationLineEdit;
    QLineEdit *accelerationTimeLineEdit;
    QLineEdit *decelerationTimeLineEdit;
    QLineEdit *kpLineEdit;
    QLineEdit *kiLineEdit;
    QLineEdit *kdLineEdit;
    QPushButton *setPushbutton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *COMLabel;
    QLabel *buadRateLabel_2;
    QVBoxLayout *verticalLayout_2;
    QComboBox *COMComboBox;
    QLineEdit *buadRateLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *updatePushbutton;
    QPushButton *connectPushbutton;
    QPushButton *recordPushButton;
    QPushButton *stopRecordingPushButton;
    QLabel *StatusLabel;
    QLabel *s_PostionLabel;
    QLabel *s_SpeedLabel;
    QLabel *s_AccelerationLabel;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *console;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(682, 571);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_7 = new QVBoxLayout(centralwidget);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        gearRatioLabel = new QLabel(centralwidget);
        gearRatioLabel->setObjectName("gearRatioLabel");

        verticalLayout_4->addWidget(gearRatioLabel);

        encoderPulsesLabel = new QLabel(centralwidget);
        encoderPulsesLabel->setObjectName("encoderPulsesLabel");

        verticalLayout_4->addWidget(encoderPulsesLabel);

        speedLabel = new QLabel(centralwidget);
        speedLabel->setObjectName("speedLabel");

        verticalLayout_4->addWidget(speedLabel);

        positionLabel = new QLabel(centralwidget);
        positionLabel->setObjectName("positionLabel");

        verticalLayout_4->addWidget(positionLabel);

        accelerationLabel = new QLabel(centralwidget);
        accelerationLabel->setObjectName("accelerationLabel");

        verticalLayout_4->addWidget(accelerationLabel);

        decelerationLabel = new QLabel(centralwidget);
        decelerationLabel->setObjectName("decelerationLabel");

        verticalLayout_4->addWidget(decelerationLabel);

        accelerationTimeLabel = new QLabel(centralwidget);
        accelerationTimeLabel->setObjectName("accelerationTimeLabel");

        verticalLayout_4->addWidget(accelerationTimeLabel);

        decelerationTimeLabel = new QLabel(centralwidget);
        decelerationTimeLabel->setObjectName("decelerationTimeLabel");

        verticalLayout_4->addWidget(decelerationTimeLabel);

        kpLabel = new QLabel(centralwidget);
        kpLabel->setObjectName("kpLabel");

        verticalLayout_4->addWidget(kpLabel);

        kiLabel = new QLabel(centralwidget);
        kiLabel->setObjectName("kiLabel");

        verticalLayout_4->addWidget(kiLabel);

        kdLabel = new QLabel(centralwidget);
        kdLabel->setObjectName("kdLabel");

        verticalLayout_4->addWidget(kdLabel);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        gearRatioLineEdit = new QLineEdit(centralwidget);
        gearRatioLineEdit->setObjectName("gearRatioLineEdit");

        verticalLayout_5->addWidget(gearRatioLineEdit);

        encoderPulsesLineEdit = new QLineEdit(centralwidget);
        encoderPulsesLineEdit->setObjectName("encoderPulsesLineEdit");

        verticalLayout_5->addWidget(encoderPulsesLineEdit);

        speedLineEdit = new QLineEdit(centralwidget);
        speedLineEdit->setObjectName("speedLineEdit");

        verticalLayout_5->addWidget(speedLineEdit);

        positionLineEdit = new QLineEdit(centralwidget);
        positionLineEdit->setObjectName("positionLineEdit");

        verticalLayout_5->addWidget(positionLineEdit);

        accelerationLineEdit = new QLineEdit(centralwidget);
        accelerationLineEdit->setObjectName("accelerationLineEdit");

        verticalLayout_5->addWidget(accelerationLineEdit);

        decelerationLineEdit = new QLineEdit(centralwidget);
        decelerationLineEdit->setObjectName("decelerationLineEdit");

        verticalLayout_5->addWidget(decelerationLineEdit);

        accelerationTimeLineEdit = new QLineEdit(centralwidget);
        accelerationTimeLineEdit->setObjectName("accelerationTimeLineEdit");

        verticalLayout_5->addWidget(accelerationTimeLineEdit);

        decelerationTimeLineEdit = new QLineEdit(centralwidget);
        decelerationTimeLineEdit->setObjectName("decelerationTimeLineEdit");

        verticalLayout_5->addWidget(decelerationTimeLineEdit);

        kpLineEdit = new QLineEdit(centralwidget);
        kpLineEdit->setObjectName("kpLineEdit");

        verticalLayout_5->addWidget(kpLineEdit);

        kiLineEdit = new QLineEdit(centralwidget);
        kiLineEdit->setObjectName("kiLineEdit");

        verticalLayout_5->addWidget(kiLineEdit);

        kdLineEdit = new QLineEdit(centralwidget);
        kdLineEdit->setObjectName("kdLineEdit");

        verticalLayout_5->addWidget(kdLineEdit);


        horizontalLayout_3->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_3);

        setPushbutton = new QPushButton(centralwidget);
        setPushbutton->setObjectName("setPushbutton");

        verticalLayout_6->addWidget(setPushbutton);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        COMLabel = new QLabel(centralwidget);
        COMLabel->setObjectName("COMLabel");

        verticalLayout->addWidget(COMLabel);

        buadRateLabel_2 = new QLabel(centralwidget);
        buadRateLabel_2->setObjectName("buadRateLabel_2");

        verticalLayout->addWidget(buadRateLabel_2);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        COMComboBox = new QComboBox(centralwidget);
        COMComboBox->setObjectName("COMComboBox");

        verticalLayout_2->addWidget(COMComboBox);

        buadRateLineEdit = new QLineEdit(centralwidget);
        buadRateLineEdit->setObjectName("buadRateLineEdit");

        verticalLayout_2->addWidget(buadRateLineEdit);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        updatePushbutton = new QPushButton(centralwidget);
        updatePushbutton->setObjectName("updatePushbutton");

        horizontalLayout->addWidget(updatePushbutton);

        connectPushbutton = new QPushButton(centralwidget);
        connectPushbutton->setObjectName("connectPushbutton");

        horizontalLayout->addWidget(connectPushbutton);


        verticalLayout_3->addLayout(horizontalLayout);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(horizontalLayout_4);

        recordPushButton = new QPushButton(centralwidget);
        recordPushButton->setObjectName("recordPushButton");

        verticalLayout_7->addWidget(recordPushButton);

        stopRecordingPushButton = new QPushButton(centralwidget);
        stopRecordingPushButton->setObjectName("stopRecordingPushButton");

        verticalLayout_7->addWidget(stopRecordingPushButton);

        StatusLabel = new QLabel(centralwidget);
        StatusLabel->setObjectName("StatusLabel");

        verticalLayout_7->addWidget(StatusLabel);

        s_PostionLabel = new QLabel(centralwidget);
        s_PostionLabel->setObjectName("s_PostionLabel");

        verticalLayout_7->addWidget(s_PostionLabel);

        s_SpeedLabel = new QLabel(centralwidget);
        s_SpeedLabel->setObjectName("s_SpeedLabel");

        verticalLayout_7->addWidget(s_SpeedLabel);

        s_AccelerationLabel = new QLabel(centralwidget);
        s_AccelerationLabel->setObjectName("s_AccelerationLabel");

        verticalLayout_7->addWidget(s_AccelerationLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        console = new QPlainTextEdit(centralwidget);
        console->setObjectName("console");

        verticalLayout_7->addWidget(console);

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
        gearRatioLabel->setText(QCoreApplication::translate("MainWindow", "Gear Ratio", nullptr));
        encoderPulsesLabel->setText(QCoreApplication::translate("MainWindow", "Encoder Pulses", nullptr));
        speedLabel->setText(QCoreApplication::translate("MainWindow", "Speed (RPM):", nullptr));
        positionLabel->setText(QCoreApplication::translate("MainWindow", "Position:", nullptr));
        accelerationLabel->setText(QCoreApplication::translate("MainWindow", "Acceleration:", nullptr));
        decelerationLabel->setText(QCoreApplication::translate("MainWindow", "Deceleration:", nullptr));
        accelerationTimeLabel->setText(QCoreApplication::translate("MainWindow", "Acceleration Time:", nullptr));
        decelerationTimeLabel->setText(QCoreApplication::translate("MainWindow", "Deceleration Time:", nullptr));
        kpLabel->setText(QCoreApplication::translate("MainWindow", "Kp:", nullptr));
        kiLabel->setText(QCoreApplication::translate("MainWindow", "Ki:", nullptr));
        kdLabel->setText(QCoreApplication::translate("MainWindow", "Kd:", nullptr));
        setPushbutton->setText(QCoreApplication::translate("MainWindow", "Set", nullptr));
        COMLabel->setText(QCoreApplication::translate("MainWindow", "COM:", nullptr));
        buadRateLabel_2->setText(QCoreApplication::translate("MainWindow", "Buad Rate:", nullptr));
        updatePushbutton->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        connectPushbutton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        recordPushButton->setText(QCoreApplication::translate("MainWindow", "Record", nullptr));
        stopRecordingPushButton->setText(QCoreApplication::translate("MainWindow", "Stop Recording", nullptr));
        StatusLabel->setText(QCoreApplication::translate("MainWindow", "Status:", nullptr));
        s_PostionLabel->setText(QCoreApplication::translate("MainWindow", "Position: 0", nullptr));
        s_SpeedLabel->setText(QCoreApplication::translate("MainWindow", "Speed: 0", nullptr));
        s_AccelerationLabel->setText(QCoreApplication::translate("MainWindow", "Acceleration: 0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
