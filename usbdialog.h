#ifndef USBDIALOG_H
#define USBDIALOG_H

#include <QDialog>
#include <QStringList>
#include <QSerialPort>
namespace Ui {
class UsbDialog;
}

class UsbDialog : public QDialog {
    Q_OBJECT

public:
    explicit UsbDialog(QWidget *parent = nullptr);
    ~UsbDialog();
    QString getSelectedDevice() const;

private slots:
    void onOkButtonClicked();

private:
    Ui::UsbDialog *ui;
    void populateUsbList();
    QStringList getConnectedSerialDevices();
    QString selectedDevice;
};

#endif // USBDIALOG_H
