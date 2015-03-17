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

#include "udpsocket.h"

// Number of packets to send at a time
const int numPackets = 4;

// Number of MS to wait between packets
const int packetDelay = 1000;

UdpSocket::UdpSocket(QObject *parent)
    : QObject(parent)
{
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.setInterval(packetDelay);
    mTimer.setSingleShot(true);
}

void UdpSocket::sendPackets(const QString &host, const QString &mac)
{
    mHost = host;
    mMac = mac;
    mPacketsRemaining = numPackets;

    // Attempt to parse the host address as an IP address
    QHostAddress address(mHost);
    if(address.isNull()) {

        // It's not a valid IP address, attempt to resolve it
        QHostInfo::lookupHost(mHost, this, SLOT(onLookupHost(QHostInfo)));

    } else {
        onTimeout();
    }
}

void UdpSocket::cancel()
{
    mTimer.stop();
}

void UdpSocket::onLookupHost(const QHostInfo &host)
{
    // Check to see if an error occurred and if not, grab the first
    if(host.error() != QHostInfo::NoError) {
        Q_EMIT error(host.errorString());
    } else {
        mHost = host.addresses().first().toString();
        onTimeout();
    }
}

void UdpSocket::onTimeout()
{
    // Attempt to construct the packet
    QByteArray packet = buildPacket();
    if(packet.isNull()) {
        Q_EMIT error(tr("invalid MAC address specified"));
        return;
    }

    // Attempt to write the packet
    if(mSocket.writeDatagram(packet, QHostAddress(mHost), 9) == -1) {
        Q_EMIT error(mSocket.errorString());
        return;
    }

    // Decrement the number of packets remaining to be written
    // and check to see if the process is complete
    --mPacketsRemaining;
    if(!mPacketsRemaining) {
        Q_EMIT completed();
    } else {
        mTimer.start();
    }
}

QByteArray UdpSocket::buildPacket()
{
    // The first six bytes contain the value 255
    QByteArray packet(6, '\xff');

    // Parse the MAC address by interpreting the data as hexadecimal
    QByteArray macAddress = QByteArray::fromHex(mMac.toUtf8());

    // Make sure that the address is valid
    if(macAddress.count() != 6) {
        return QByteArray();
    }

    // Append sixteen repetitions of the MAC address
    for(int i = 0; i < 16; ++i) {
        packet.append(macAddress);
    }

    return packet;
}
