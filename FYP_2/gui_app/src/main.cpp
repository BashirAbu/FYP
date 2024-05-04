#include <QApplication>
#include <QWidget>
#include "mainwindow.h"
#include <Windows.h>
#include <iostream>

void ListSerialPorts() {
    HKEY hKey;
    char portName[256];
    DWORD portNameLen;
    DWORD type;
    int index = 0;

    // Open the "HARDWARE\DEVICEMAP\SERIALCOMM" key in the registry
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
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
                    printf("Port: %s\n", portValue);
                }
            }
            index++;
        }
        RegCloseKey(hKey);
    } else {
        fprintf(stderr, "Failed to open registry key\n");
    }
}

struct ConfigData
{
    uint32_t speed;
    int32_t pos;
    int32_t counts;
};

int main(int argc, char **argv) {
    // QApplication app(argc, argv);
    // MainWindow mw;
    // mw.show();
    // return app.exec();


// Define the serial port name (e.g., COM1)
    ListSerialPorts();
    const char* portName = "COM5";

    HANDLE hSerial = CreateFileA("\\\\.\\COM5", // Replace COM3 with your COM port
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening serial port" << std::endl;
        return 1; // or appropriate error handling
    }

    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error getting serial port state" << std::endl;
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600; // Set baud rate to 9600, you can change as needed
    dcbSerialParams.ByteSize = 8;        // 8 data bits
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity   = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error setting serial port state" << std::endl;
        return 1;
    }

    ConfigData data = {0};
    data.speed = 11;
    data.pos = 99;
    data.counts = 100;
    DWORD bytesWritten;
    if (!WriteFile(hSerial, &data, sizeof(ConfigData), &bytesWritten, NULL)) {
        std::cerr << "Error writing to serial port" << std::endl;
        return 1;
    }
    CloseHandle(hSerial);

    return 0;
}