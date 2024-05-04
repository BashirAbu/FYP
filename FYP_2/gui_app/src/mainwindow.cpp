#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QListWidget>
#include <QtCore/QtCore>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    QListWidgetItem* listItem = new QListWidgetItem(ui->txtTask->text(), ui->listWidget);
    listItem->setFlags(listItem->flags() | Qt::ItemIsEditable);
    ui->listWidget->addItem(listItem);
    ui->txtTask->clear();
    ui->txtTask->setFocus();
}


void MainWindow::on_btnRemove_clicked()
{
    delete ui->listWidget->takeItem(ui->listWidget->currentRow());
}


void MainWindow::on_btnReamoveAll_clicked()
{
    ui->listWidget->clear();
}

