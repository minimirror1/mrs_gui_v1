#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_usbButton_clicked();
    void on_sendButton_clicked();

    void on_sendButton_pressed();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort; // 시리얼 포트 객체를 멤버 변수로 선언
};
#endif // MAINWINDOW_H
