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
    ui->buadRateLineEdit->setValidator(new QDoubleValidator(ui->buadRateLineEdit));
    ui->speedLineEdit->setValidator(new QDoubleValidator(ui->speedLineEdit));
    ui->positionLineEdit->setValidator(new QDoubleValidator(ui->positionLineEdit));
    ui->encoderPulsesLineEdit->setValidator(new QDoubleValidator(ui->encoderPulsesLineEdit));
    ui->gearRatioLineEdit->setValidator(new QDoubleValidator(ui->gearRatioLineEdit));
    ui->accelerationLineEdit->setValidator(new QDoubleValidator(ui->accelerationLineEdit));
    ui->decelerationLineEdit->setValidator(new QDoubleValidator(ui->decelerationLineEdit));
    ui->accelerationTimeLineEdit->setValidator(new QDoubleValidator(ui->accelerationTimeLineEdit));
    ui->decelerationTimeLineEdit->setValidator(new QDoubleValidator(ui->decelerationTimeLineEdit));
    ui->kpLineEdit->setValidator(new QDoubleValidator(ui->kpLineEdit));
    ui->kiLineEdit->setValidator(new QDoubleValidator(ui->kiLineEdit));
    ui->kdLineEdit->setValidator(new QDoubleValidator(ui->kdLineEdit));

    ui->buadRateLineEdit->setText("9600");
    ui->speedLineEdit->setText("0");
    ui->positionLineEdit->setText("0");
    ui->encoderPulsesLineEdit->setText("500");
    ui->gearRatioLineEdit->setText(QString::number(3249.0 / 121.0));
    ui->accelerationLineEdit->setText("0");
    ui->decelerationLineEdit->setText("0");
    ui->accelerationTimeLineEdit->setText("0");
    ui->decelerationTimeLineEdit->setText("0");
    ui->kiLineEdit->setText("0");
    ui->kdLineEdit->setText("0");
    ui->kpLineEdit->setText("0");


    ui->console->setReadOnly(true);

    QObject::connect(ui->updatePushbutton, &QPushButton::clicked, this, &MainWindow::OnUpdateButtonClicked);
    QObject::connect(ui->connectPushbutton, &QPushButton::clicked, this, &MainWindow::OnConnectButtonClicked);
    QObject::connect(ui->setPushbutton, &QPushButton::clicked, this, &MainWindow::OnSetButtonClicked);
    QObject::connect(ui->buadRateLineEdit, &QLineEdit::textEdited, this, &MainWindow::OnBuadRateLineEditEdited);
    QObject::connect(serialPort, &QSerialPort::errorOccurred, this, &MainWindow::OnSerialPortHandleError);
    QObject::connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::OnSerialPortReadyRead);

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
    connected = true;
    ui->connectPushbutton->setText("Disconnect");
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
    ui->COMComboBox->setCurrentIndex(-1);
    ui->COMComboBox->clear();
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
    
    servoController.SetSpeed((float)ui->speedLineEdit->text().toDouble());
    servoController.SetPosition((float)ui->positionLineEdit->text().toDouble());
    servoController.SetEncoderPulses((float)ui->encoderPulsesLineEdit->text().toDouble());
    servoController.SetGearRatio((float)ui->gearRatioLineEdit->text().toDouble());
    servoController.SetKd((float)ui->kdLineEdit->text().toDouble());
    servoController.SetKi((float)ui->kiLineEdit->text().toDouble());
    servoController.SetKp((float)ui->kpLineEdit->text().toDouble());
    servoController.SetAcceleration((float)ui->accelerationLineEdit->text().toDouble());
    servoController.SetAccelerationTime((float)ui->accelerationTimeLineEdit->text().toDouble());
    servoController.SetDeceleration((float)ui->decelerationLineEdit->text().toDouble());
    servoController.SetDecelerationTime((float)ui->decelerationTimeLineEdit->text().toDouble());

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

void MainWindow::OnSerialPortHandleError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError) {
        ConsoleLogError("Serial port error or device disconnected:" + serialPort->errorString());
        DisconnectCOMPort();
    }
}

void MainWindow::OnSerialPortReadyRead()
{
    rxBuffer.append(serialPort->readAll());

    
    printf("%s", rxBuffer.data());
    rxBuffer.clear();
    // if(rxBuffer.size() > sizeof(servoController.status_data))
    // {
    //     //memcpy(&servoController.status_data, rxBuffer.constData(), sizeof(servoController.status_data));
    //     ServoController::StatusData* sd = (ServoController::StatusData*) rxBuffer.data();
    //     rxBuffer.remove(0, sizeof(servoController.status_data));

    //     ui->s_PostionLabel->setText("Position: " + QString::number(sd->position));
    //     ui->s_AccelerationLabel->setText("Acceleration: " + QString::number(sd->acceleration));
    //     ui->s_SpeedLabel->setText("Speed: " + QString::number(sd->speed));
    // }
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

void MainWindow::ConsoleLogMsg(QString msg)
{
    QTextCursor cursor(ui->console->document());
    cursor.movePosition(QTextCursor::End);
    QTextCharFormat textFormat;
    textFormat.setForeground(Qt::red);
    

    cursor.mergeCharFormat(textFormat);
    cursor.insertText(msg);
    cursor = ui->console->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->console->setTextCursor(cursor);
}

