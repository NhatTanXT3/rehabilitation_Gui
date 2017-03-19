#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QtSerialPort/QtSerialPort>
#include <QFile>
#include <Qtimer>

#define ENABLE_PLAYER 1
#define DISABLE_PLAYER 2
#define RUN_PLAYER 3
#define RUN_MODE1 4
#define RUN_MODE3 5
#define STOP_PLAYER 6

/******************************************************************************
*
******************************************************************************/
namespace Ui {
    class Serial;
}

//class QSerialPort


class Serial : public QWidget
{
    Q_OBJECT

public:
    Serial();
    ~Serial();

    void sendCommand(int mode);
    int getSerialValue(void);

private:
    /* Serial port Properties */
    /* Arduino micro: VID = 9025, PID = 32823*/
    static const quint16 JRD_vendor_id = 9025;
    static const quint16 JRD_product_id = 32823;
    bool JRD_is_available = false;
    QString JRD_port_name;
    QTimer *SerialTimer;
    QSerialPort *serialPort;
    Ui::Serial *ui;

    /* Data Properties */
    QChar inChar;
    QString inString;
    bool stringcomplete = false;
    int serialValue = 0;
    void setupSerialPort();
    
private slots:
    void serialReceived();
};

#endif // SERIALTEST2_H
