#include <QApplication>
#include <QWidget>
#include "mainwindow.h"
#include <Windows.h>
#include <iostream>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mw;
    mw.show();
    return app.exec();
}