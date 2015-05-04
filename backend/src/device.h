/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Nathan Osman
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 **/

#ifndef DEVICE_H
#define DEVICE_H

#include <QHostAddress>
#include <QHostInfo>
#include <QJsonObject>
#include <QObject>
#include <QUdpSocket>
#include <QTimer>

/**
 * @brief A single device capable of being awoken
 */
class Device : public QObject
{
    Q_OBJECT

public:

    Device();

    QString title() const { return mTitle; }
    bool local() const { return mLocal; }
    QString host() const { return mHost; }
    QString mac() const { return mMac; }
    quint16 port() const { return mPort; }

    bool isBusy() const { return mHostLookup != -1 || mTimer.isActive(); }

    void wake();
    void cancel();

    bool fromJson(const QJsonObject &object);
    QJsonObject toJson();

signals:

    void error(const QString &message);
    void finished();

private slots:

    void onLookupHost(const QHostInfo &info);
    void onTimeout();

private:

    QByteArray buildPacket();

    QString mTitle;
    bool mLocal;
    QString mHost;
    QString mMac;
    quint16 mPort;

    QUdpSocket mSocket;
    QHostAddress mAddress;
    int mHostLookup;

    QTimer mTimer;
    int mPacketsRemaining;
};

#endif // DEVICE_H
