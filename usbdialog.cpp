#include "usbdialog.h"
#include "ui_usbdialog.h"
#include <QProcess>
#include <QDir>
#include <QCheckBox>
#include <QDebug>
#include <QMessageBox>
UsbDialog::UsbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsbDialog)
{
    ui->setupUi(this);
    populateUsbList();

    // OK 버튼 시그널 슬롯 연결
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &UsbDialog::onOkButtonClicked);
}

UsbDialog::~UsbDialog() {
    delete ui;
}

void UsbDialog::populateUsbList() {
    QStringList serialDevices = getConnectedSerialDevices();

    foreach (const QString &device, serialDevices) {
        QCheckBox *checkBox = new QCheckBox(device, this);
        ui->verticalLayout->addWidget(checkBox);
        qDebug() << "Added device:" << device;
    }
}

QStringList UsbDialog::getConnectedSerialDevices() {
    QStringList deviceList;

    // QProcess를 사용하여 ls /dev 명령 실행
    QProcess process;
    process.start("ls /dev");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());

    // 출력된 결과를 라인별로 분리하고 ttyUSB* 및 ttyACM* 포함된 항목 필터링
    QStringList lines = output.split('\n', QString::SkipEmptyParts);
    foreach (const QString &line, lines) {
        if (line.startsWith("ttyUSB") || line.startsWith("ttyACM")) {
            deviceList << line.trimmed();
            qDebug() << "Found device:" << line.trimmed();
        }
    }

    return deviceList;
}

void UsbDialog::onOkButtonClicked() {
    QList<QCheckBox *> checkBoxes = this->findChildren<QCheckBox *>();
    foreach (QCheckBox *checkBox, checkBoxes) {
        if (checkBox->isChecked()) {
            selectedDevice = checkBox->text();
            break;
        }
    }

    qDebug() << "Selected device:" << selectedDevice;
}

QString UsbDialog::getSelectedDevice() const {
    return selectedDevice;
}
