#include "BLBluetoothLEScanner.hpp"
#include <QDebug>
#include <QTimer>

BLBluetoothLEScanner::BLBluetoothLEScanner(uint64_t scanInterval, QObject *parent) :
    QObject(parent), m_scanIntervalMs(scanInterval)
{
    m_blDiscoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(m_blDiscoveryAgent, SIGNAL(deviceDiscovered(const QBluetoothDeviceInfo&)),
            this, SLOT(addDevice(const QBluetoothDeviceInfo&)));
    connect(m_blDiscoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(onError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(m_blDiscoveryAgent, SIGNAL(finished()), this, SLOT(finished()));
}

void BLBluetoothLEScanner::addDevice(const QBluetoothDeviceInfo &device)
{
    qDebug() << __FUNCTION__ << "Found new device:" << device.name() << '(' << device.address().toString()
             << ')' << device.address() << "LE"
             << (device.coreConfigurations() == QBluetoothDeviceInfo::LowEnergyCoreConfiguration);

    this->finished();
}

void BLBluetoothLEScanner::onError(QBluetoothDeviceDiscoveryAgent::Error err)
{
    qDebug() << __FUNCTION__ << err;
}

void BLBluetoothLEScanner::finished()
{
    qDebug() << __FUNCTION__;
    QTimer::singleShot(m_scanIntervalMs, this, SLOT(startScan()));
}

void BLBluetoothLEScanner::startScan()
{
    qDebug() << __FUNCTION__;
    m_blDiscoveryAgent->start();
}
