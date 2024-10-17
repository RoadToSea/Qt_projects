#ifndef SERIALASSISTANT_H
#define SERIALASSISTANT_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

class SerialAssistant : public QWidget {
    Q_OBJECT

public:
    SerialAssistant(QWidget *parent = nullptr);

private slots:
    void updatePorts();
    void openSerialPort();
    void readData();
    void sendData();

private:
    QSerialPort *m_serial;
    QComboBox *m_portComboBox;
    QLineEdit *m_baudRateEdit;
    QTextEdit *m_receiveEdit;
    QLineEdit *m_sendEdit;
};

#endif // SERIALASSISTANT_H
