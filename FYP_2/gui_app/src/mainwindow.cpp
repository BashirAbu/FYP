#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QListWidget>
#include <QtCore/QtCore>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Servo Controller");
    ui->buadRateLineEdit->setText("9600");
    ui->speedLineEdit->setText("0");
    ui->positionLineEdit->setText("0");

    ui->buadRateLineEdit->setValidator(new QIntValidator(ui->buadRateLineEdit));
    ui->speedLineEdit->setValidator(new QIntValidator(ui->speedLineEdit));
    ui->positionLineEdit->setValidator(new QIntValidator(ui->positionLineEdit));
    QObject::connect(ui->updatePushbutton, &QPushButton::clicked, this, &MainWindow::OnUpdateButtonClicked);
    QObject::connect(ui->connectPushbutton, &QPushButton::clicked, this, &MainWindow::OnConnectButtonClicked);
    QObject::connect(ui->setPushbutton, &QPushButton::clicked, this, &MainWindow::OnSetButtonClicked);
    QObject::connect(ui->buadRateLineEdit, &QLineEdit::textEdited, this, &MainWindow::OnBuadRateLineEditEdited);


    UpdateCOMComboBox();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::ConnectCOMPort(QString COMPortName)
{
    QString portName = "\\\\.\\" + COMPortName;
    hSerial = CreateFileA(portName.toLatin1().data(), // Replace COM3 with your COM port
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        qCritical() << "Error opening serial port\n";
        return false; // or appropriate error handling
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        qCritical() << "Error getting serial port state\n";
        return false;
    }

    dcbSerialParams.BaudRate = buadRate; // Set baud rate to 9600, you can change as needed
    dcbSerialParams.ByteSize = 8;        // 8 data bits
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        qCritical()<< "Error setting serial port state\n";
        return false;
    }
    return true;
}


void MainWindow::OnConnectButtonClicked()
{
    if(connected)
    {
        //Disconnect button is pressed
        connected = false;
        CloseHandle(hSerial);
        ui->connectPushbutton->setText("Connect");
    }
    else
    {
        //Connect button is pressed
        connected = true;
        ui->connectPushbutton->setText("Disconnect");
        if(!ConnectCOMPort(ui->COMComboBox->currentText()))
        {
            qCritical() << "Failed to connect to COM Port:" << ui->COMComboBox->currentText() << "\n";
        }
    }
}

void MainWindow::OnBuadRateLineEditEdited()
{
    buadRate = ui->buadRateLineEdit->text().toInt();
}

void MainWindow::OnSetButtonClicked()
{
    if(!connected)
        return;
    
    servoController.SetSpeed(ui->speedLineEdit->text().toUInt());
    servoController.SetPosition(ui->positionLineEdit->text().toInt());


    DWORD bytesWritten;
    if (!WriteFile(hSerial, &servoController.data, sizeof(servoController.data), &bytesWritten, NULL)) 
    {
        qCritical() << "Failed to send data!\n";
    }
}

void MainWindow::UpdateCOMComboBox()
{
    QVector<QString> portsList = GetCOMPorts();
    ui->COMComboBox->clear();
    for(QString port : portsList)
    {
        ui->COMComboBox->addItem(port);
    }
}

void MainWindow::OnUpdateButtonClicked()
{
    UpdateCOMComboBox();
}


QVector<QString> MainWindow::GetCOMPorts()
{
    QVector<QString> result;

    HKEY hKey;
    char portName[256];
    DWORD portNameLen;
    DWORD type;
    int index = 0;

    // Open the "HARDWARE\DEVICEMAP\SERIALCOMM" key in the registry
    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        // Enumerate all values under this key
        while (TRUE) {
            portNameLen = sizeof(portName);
            // Read each entry in the registry key
            if (RegEnumValueA(hKey, index, portName, &portNameLen, NULL, &type, NULL, NULL) != ERROR_SUCCESS) {
                break;
            }
            if (type == REG_SZ) {  // Ensure it's a string type (REG_SZ)
                char portValue[256];
                DWORD portValueLen = sizeof(portValue);
                // Get the name of the port
                if (RegQueryValueExA(hKey, portName, NULL, NULL, (LPBYTE)portValue, &portValueLen) == ERROR_SUCCESS) {
                    result.append(portValue);
                }
            }
            index++;
        }
        RegCloseKey(hKey);
    } else {
        fprintf(stderr, "Failed to open registry key\n");
    }

    return result;
}

