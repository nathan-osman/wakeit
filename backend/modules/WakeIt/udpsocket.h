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

#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QHostInfo>
#include <QTimer>
#include <QUdpSocket>

/**
 * @brief QML interface to a UDP socket
 */
class UdpSocket : public QObject
{
    Q_OBJECT

public:

    explicit UdpSocket(QObject *parent = 0);

Q_SIGNALS:

    /**
     * @brief Indicate that an error occurred while sending a packet
     * @param message a brief description of the error
     */
    void error(const QString &message);

    /**
     * @brief Indicate that packets were sent without error
     */
    void completed();

public Q_SLOTS:

    /**
     * @brief Send magic packets to the specified host
     * @param host hostname or IP address
     * @param mac MAC address used when crafting the magic packet
     */
    void sendPackets(const QString &host, const QString &mac);

    /**
     * @brief Immediately stop sending packets
     */
    void cancel();

private Q_SLOTS:

    void onLookupHost(const QHostInfo &host);
    void onTimeout();

private:

    QByteArray buildPacket();

    QUdpSocket mSocket;
    QString mHost;
    QString mMac;

    QTimer mTimer;
    int mPacketsRemaining;
};

#endif // UDPSOCKET_H

