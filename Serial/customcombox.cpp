#include "customcombox.h"
#include <QSerialPort>
#include <QSerialPortInfo>

customCombox::customCombox(QWidget *parent) : QComboBox(parent) {}

void customCombox::showPopup()
{
    clear();
    // 获取系统中的串口信息
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        // 将可用串口添加到 comboBox
        addItem(info.portName());
    }
    QComboBox::showPopup();
}
