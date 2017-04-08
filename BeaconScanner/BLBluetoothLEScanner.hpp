#ifndef BLBLUETOOTHLESCANNER_HPP
#define BLBLUETOOTHLESCANNER_HPP

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>

class BLBluetoothLEScanner : public QObject
{
    Q_OBJECT
public:
    explicit BLBluetoothLEScanner(uint64_t scanInterval = 10000, QObject *parent = 0);
signals:

public slots:
    void addDevice(const QBluetoothDeviceInfo& device);
    void onError(QBluetoothDeviceDiscoveryAgent::Error err);
    void finished();
    void startScan();

private:
    QBluetoothDeviceDiscoveryAgent *m_blDiscoveryAgent;
    uint64_t m_scanIntervalMs;
};

#endif // BLBLUETOOTHLESCANNER_HPP
