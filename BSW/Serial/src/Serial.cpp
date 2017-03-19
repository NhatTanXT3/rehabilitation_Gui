#include "Serial.h"
#include <QtSerialPort/QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "jrdgui.h"

int flag_error=0;
int count=0;

Serial::Serial()
{
    setupSerialPort();
    inChar = '';
    inString = "";
}

Serial::~Serial()
{
    if(serialPort->isOpen()){
        serialPort->close();
    }
}

void Serial::sendCommand(int mode)
{
    qDebug() << mode;
    switch (mode) {
    case ENABLE_PLAYER:
        serialPort->write("e\n");
        break;
    case DISABLE_PLAYER:
        serialPort->write("f\n");
        break;
    case RUN_PLAYER:
        serialPort->write("c\n");
        break;
    case RUN_MODE1:
        serialPort->write("w1\n");
        break;
    case RUN_MODE3:
        serialPort->write("w3\n");
        SerialTimer->start(10);
        break;
    case STOP_PLAYER:
        serialPort->write("d\n");
        break;
    default:
        break;
    }
}

void Serial::setupSerialPort()
{
    /*
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
     */
//    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
//    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
//        qDebug() << "Description: " << serialPortInfo.description() << "\n";
//        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
//        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
//        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
//        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
//        qDebug() << JRD_product_id << "\n";
//        qDebug() << JRD_vendor_id << "\n";
//    }

    /*
    *  For each available serial port
    */
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == JRD_product_id)
                    && (serialPortInfo.vendorIdentifier() == JRD_vendor_id)){
                JRD_is_available = true; //    arduino uno is available on this port
                JRD_port_name = serialPortInfo.portName();
            }
        }
    }
    if(JRD_is_available){
        qDebug() <<" Found serial port" << "\n";
        serialPort = new QSerialPort(this);
        serialPort->setPortName(JRD_port_name);
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->setStopBits(QSerialPort::OneStop);
//        serialPort->setReadBufferSize(100);
        serialPort->open(QIODevice::ReadWrite);
         SerialTimer = new QTimer();
         connect(SerialTimer,SIGNAL(timeout()),this,SLOT(serialReceived()));
//        connect(serialPort,SIGNAL(readyRead()),this,SLOT(serialReceived()));

    }
    else{
        qDebug() <<" couldn't find serial port" << "\n";
    }

    /*
     *  Print properties of serial port
     */
}
/******************************************************************************
* Read all message
*******************************************************************************/
void Serial::serialReceived()
{
    while(0 != serialPort->bytesAvailable())
    {
        //get the new byte
        serialPort->getChar(&inChar);

        // if the incoming character is a newline, set a flag
        if('\n\r' == inChar)
        {
            stringComplete = true;
        }
        else /*('\n\r' == inChar)*/
        {
            inString.append(inChar);
        }
    }
    if(stringcomplete)
    {
        qDebug << inString;
        serialValue = inString.toInt();
        inString.clear();
    }
}

int Serial::getSerialValue()
{
    return serialValue;
}
