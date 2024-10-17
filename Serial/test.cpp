#include "test.h"
#include <QHBoxLayout>
#include <QMessageBox>

SerialAssistant::SerialAssistant(QWidget *parent) : QWidget(parent), m_serial(new QSerialPort(this)) {
    // UI Setup
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_portComboBox = new QComboBox(this);
    m_baudRateEdit = new QLineEdit("9600", this);
    m_receiveEdit = new QTextEdit(this);
    m_sendEdit = new QLineEdit(this);
    QPushButton *openButton = new QPushButton("Open Port", this);
    QPushButton *sendButton = new QPushButton("Send", this);

    layout->addWidget(new QLabel("Select Port:"));
    layout->addWidget(m_portComboBox);
    layout->addWidget(new QLabel("Baud Rate:"));
    layout->addWidget(m_baudRateEdit);
    layout->addWidget(openButton);
    layout->addWidget(new QLabel("Received Data:"));
    layout->addWidget(m_receiveEdit);
    layout->addWidget(new QLabel("Send Data:"));
    layout->addWidget(m_sendEdit);
    layout->addWidget(sendButton);

    setLayout(layout);
    setWindowTitle("Simple Serial Assistant");

    // Populate ports
    updatePorts();

    // Connect signals and slots
    connect(openButton, &QPushButton::clicked, this, &SerialAssistant::openSerialPort);
    connect(sendButton, &QPushButton::clicked, this, &SerialAssistant::sendData);
    connect(m_serial, &QSerialPort::readyRead, this, &SerialAssistant::readData);
}

void SerialAssistant::updatePorts() {
    m_portComboBox->clear();
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports) {
        m_portComboBox->addItem(port.portName());
    }
}

void SerialAssistant::openSerialPort() {
    if (m_serial->isOpen()) {
        m_serial->close();
    }

    m_serial->setPortName(m_portComboBox->currentText());
    m_serial->setBaudRate(m_baudRateEdit->text().toInt());

    if (m_serial->open(QIODevice::ReadWrite)) {
        QMessageBox::information(this, "Success", "Serial port opened successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to open serial port!");
    }
}

void SerialAssistant::readData() {
    const QByteArray data = m_serial->readAll();
    m_receiveEdit->append(QString(data));
}

void SerialAssistant::sendData() {
    const QString data = m_sendEdit->text();
    m_serial->write(data.toUtf8());
}

