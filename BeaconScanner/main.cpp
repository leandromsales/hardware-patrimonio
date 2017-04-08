#include <QCoreApplication>
#include "BLBluetoothLEScanner.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    BLBluetoothLEScanner *scanner = new BLBluetoothLEScanner(10000, &a);
    scanner->startScan();
    return a.exec();
}
