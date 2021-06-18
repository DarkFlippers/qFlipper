#ifndef LIBUSBDEVICE_H
#define LIBUSBDEVICE_H

#include <QObject>

#include "usbdeviceinfo.h"

class USBDevice : public QObject
{
    Q_OBJECT

    struct USBDevicePrivate;

public:
    USBDevice(const USBDeviceInfo &info, QObject *parent = nullptr);
    virtual ~USBDevice();

    bool open();
    void close();

    bool claimInterface(int interfaceNum);
    bool releaseInterface(int interfaceNum);
    bool setInterfaceAltSetting(int interfaceNum, uint8_t alt);

    bool controlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, const QByteArray &data);
    QByteArray controlTransfer(uint8_t requestType, uint8_t request, uint16_t value, uint16_t index, uint16_t length);

    QByteArray extraInterfaceDescriptor(int interfaceNum, uint8_t type, int length);
    QByteArray stringInterfaceDescriptor(int interfaceNum);

private:
    USBDevicePrivate *m_p = nullptr;
    unsigned long m_timeout = 1000;
};

#endif // LIBUSBDEVICE_H
