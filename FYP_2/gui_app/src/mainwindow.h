#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtSerialPort/QSerialPort>
#include "servo_controller.h"
#include <QtSerialPort/QSerialPort>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QVector<QString> GetCOMPorts();

    void ConsoleLogDebug(QString msg);
    void ConsoleLogError(QString msg);
    
    void UpdateCOMComboBox();
    bool ConnectCOMPort(QString COMPortName);
    void DisconnectCOMPort();
    bool CheckSerialPort(QString COMPortName);
    void OnUpdateButtonClicked();
    void OnConnectButtonClicked();
    void OnBuadRateLineEditEdited();
    void OnSetButtonClicked();
    void OnSerialPortHandleError(QSerialPort::SerialPortError error);
    void OnSerialPortReadyRead();
public:
    uint32_t buadRate = 9600;
private:
    Ui::MainWindow *ui;
    bool connected = false;
    QSerialPort* serialPort;
    ServoController servoController;
    QByteArray rxBuffer;
};

#endif // MAINWINDOW_H
