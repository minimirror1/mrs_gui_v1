#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "usbdialog.h"
#include <QMessageBox>
#include <QSerialPort>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialPort(new QSerialPort(this)) // 시리얼 포트 객체 초기화
{
    ui->setupUi(this);

    // sendButton 클릭 시그널 슬롯 연결
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_usbButton_clicked() {
    UsbDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString selectedDevice = dialog.getSelectedDevice();
        if (!selectedDevice.isEmpty()) {
            serialPort->setPortName("/dev/" + selectedDevice);

            if (serialPort->open(QIODevice::ReadWrite)) {
                QMessageBox::information(this, "Device Selected", "Connected to " + selectedDevice);
            } else {
                QMessageBox::warning(this, "Error", "Failed to connect to " + selectedDevice + ": " + serialPort->errorString());
            }
        } else {
            QMessageBox::warning(this, "No Device", "No device selected.");
        }
    }
}

void MainWindow::on_sendButton_clicked() {

}

void MainWindow::on_sendButton_pressed()
{
    qDebug() << "Send button clicked";
    if (serialPort->isOpen() && serialPort->isWritable()) {
        QByteArray data;
        data.append(0x12); // 송신할 데이터 추가
        serialPort->write(data);
        QMessageBox::information(this, "Data Sent", "0x12 has been sent.");
    } else {
        QMessageBox::warning(this, "Error", "Serial port is not open or not writable.");
    }
}

