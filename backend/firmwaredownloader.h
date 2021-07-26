#ifndef FIRMWAREUPDATER_H
#define FIRMWAREUPDATER_H

#include <QObject>
#include <QQueue>

#include "flipperupdates.h"
#include "abstractfirmwareoperation.h"

class QIODevice;

namespace Flipper {

class FlipperZero;
class FirmwareDownloader : public QObject
{
    Q_OBJECT

    enum class State {
        Ready,
        Running
    };

public:
    FirmwareDownloader(QObject *parent = nullptr);

public slots:
    void downloadLocalFile(Flipper::FlipperZero *device, const QString &filePath);
    void downloadRemoteFile(Flipper::FlipperZero *device, const Updates::FileInfo &fileInfo);

    void downloadLocalFUS(Flipper::FlipperZero *device, const QString &filePath);
    void downloadLocalWirelessStack(Flipper::FlipperZero *device, const QString &filePath);

    void makeBootable(Flipper::FlipperZero *device);

private slots:
    void processQueue();

private:
    void enqueueOperation(AbstractFirmwareOperation *op);

    State m_state;
    QQueue<AbstractFirmwareOperation*> m_operationQueue;
};

}

#endif // FIRMWAREUPDATER_H