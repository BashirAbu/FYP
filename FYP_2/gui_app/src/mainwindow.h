#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <Windows.h>

#include "servo_controller.h"



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

    void UpdateCOMComboBox();
    bool ConnectCOMPort(QString COMPortName);
    void OnUpdateButtonClicked();
    void OnConnectButtonClicked();
    void OnBuadRateLineEditEdited();
    void OnSetButtonClicked();
public:
    uint32_t buadRate = 9600;
private:
    Ui::MainWindow *ui;
    bool connected = false;
    HANDLE hSerial;
    ServoController servoController;
};

#endif // MAINWINDOW_H
