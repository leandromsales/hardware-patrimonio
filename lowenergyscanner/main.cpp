/***************************************************************************
**
** Copyright (C) 2013 BlackBerry Limited. All rights reserved.
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtBluetooth module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

//#include <QtCore/QLoggingCategory>
//#include <QQmlContext>
//#include <QGuiApplication>
//#include <QQuickView>
#include <QCoreApplication>
#include "device.h"
#include <iostream>
#include <QDebug>
#include <time.h>
#include <QEventLoop>
#include <QObject>

using namespace std;

void sleep(clock_t wait)
{
    clock_t goal = (wait + clock());
    while (goal > clock());

}

int main(int argc, char *argv[])
{
    //QLoggingCategory::setFilterRules(QStringLiteral("qt.bluetooth* = true"));
    QCoreApplication app(argc, argv);

    string address, serv_uuid;
    Device d;
    QEventLoop loop;
    d.startDeviceDiscovery();
    QObject::connect(&d, SIGNAL(stateChanged()), &loop, SLOT(quit()));
    loop.exec(); //wait for the scan response
    qDebug() << "\nBluetooth address to connect:";
    cin >> address;

//    qDebug() << QString (address.c_str());
    d.scanServices(QString (address.c_str()));
//    sleep(100000);

    QObject::connect(&d, SIGNAL(serviceScanDone2()), &loop, SLOT(quit()));
    loop.exec();

    qDebug() << "\nservice to connect:";
    cin >> serv_uuid;

    d.connectToService(QString (serv_uuid.c_str()));

//    QObject::connect(&d, SIGNAL(addCharacteristics()), &loop, SLOT(quit()));
//    loop.exec();




//    QQuickView *view = new QQuickView;
//    view->rootContext()->setContextProperty("device", &d);

//    view->setSource(QUrl("qrc:/assets/main.qml"));
//    view->setResizeMode(QQuickView::SizeRootObjectToView);
//    view->show();
    return app.exec();
}