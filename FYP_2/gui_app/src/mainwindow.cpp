#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QListWidget>
#include <QtCore/QtCore>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Servo Controller");

    serialPort = new QSerialPort(this);

    ui->buadRateLineEdit->setText("9600");
    ui->speedLineEdit->setText("0");
    ui->positionLineEdit->setText("0");

    ui->buadRateLineEdit->setValidator(new QIntValidator(ui->buadRateLineEdit));
    ui->speedLineEdit->setValidator(new QIntValidator(ui->speedLineEdit));
    ui->positionLineEdit->setValidator(new QIntValidator(ui->positionLineEdit));

    ui->console->setReadOnly(true);

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
    if(!CheckSerialPort(COMPortName))
        return false;
    serialPort->setPortName(COMPortName);  // Set the COM port. Adjust as necessary for your system.
    serialPort->setBaudRate(buadRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!serialPort->open(QIODevice::ReadWrite)) {
        ConsoleLogError("Error: Unable to open the port!");
        return false;
    }
    return true;
}

void MainWindow::DisconnectCOMPort()
{
    connected = false;
    serialPort->close();
    ui->connectPushbutton->setText("Connect");
}

bool MainWindow::CheckSerialPort(QString COMPortName)
{
    QVector<QString> ports = GetCOMPorts();

    for(QString port : ports)
    {
        if(port == COMPortName)
        {
            return true;
        }
    }
    return false;
}


void MainWindow::OnConnectButtonClicked()
{
    if(connected)
    {
        //Disconnect button is pressed
        DisconnectCOMPort();
    }
    else
    {
        //Connect button is pressed
        connected = true;
        ui->connectPushbutton->setText("Disconnect");
        if(!ConnectCOMPort(ui->COMComboBox->currentText()))
        {
            ConsoleLogError("Failed to connect to COM Port:" + ui->COMComboBox->currentText() + "\n");
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
    {
        ConsoleLogError("Serial port is not connected!");
        return;
    }
    
    servoController.SetSpeed(ui->speedLineEdit->text().toUInt());
    servoController.SetPosition(ui->positionLineEdit->text().toInt());


    QByteArray buffer;
    buffer.append(reinterpret_cast<const char*>(&servoController.data), sizeof(servoController.data));

    qint64 bytesWritten = serialPort->write(buffer);
    if (bytesWritten == -1) {
        ConsoleLogDebug("Failed to write the data to port");
    } else if (bytesWritten != sizeof(servoController.data)) {
        ConsoleLogDebug("Failed to write all the data to port");
    } else {
        ConsoleLogDebug("Data written to port successfully");
    }
    serialPort->flush(); // Ensure all data is sent
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

    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    ConsoleLogDebug("Total number of ports available: " + QString::number(ports.count()));

    for (const QSerialPortInfo &port : ports) {
        result.append(port.portName());
    }

    return result;
}

void MainWindow::ConsoleLogDebug(QString msg)
{
    QTextCursor cursor(ui->console->document());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat textFormat;
    textFormat.setForeground(Qt::green);
    cursor.mergeCharFormat(textFormat);
    cursor.insertText(msg);
    cursor.insertText("\n"); // Move to the next line after appending text

    
    cursor = ui->console->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->console->setTextCursor(cursor);
}

void MainWindow::ConsoleLogError(QString msg)
{
    QTextCursor cursor(ui->console->document());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat textFormat;
    textFormat.setForeground(Qt::red);
    cursor.mergeCharFormat(textFormat);
    cursor.insertText(msg);
    cursor.insertText("\n"); // Move to the next line after appending text

    cursor = ui->console->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->console->setTextCursor(cursor);
}

