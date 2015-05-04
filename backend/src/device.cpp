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
 */

#include <QNetworkInterface>

#include "device.h"

// TODO: make these configurable settings

// Number of packets to send and the delay (in MS) between packets
const int PacketCount = 4;
const int PacketDelay = 500;

Device::Device()
    : mHostLookup(-1)
{
    // Prepare the timer
    connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    mTimer.setInterval(PacketDelay);
    mTimer.setSingleShot(true);
}

void Device::wake()
{
    // If we're busy, ignore the request
    if(isBusy()) {
        qWarning("Device is busy");
        return;
    }

    // Reset the number of packets remaining to be sent
    mPacketsRemaining = PacketCount;

    // If this packet is to be sent locally, then don't bother doing anything
    // with the address, since we are using local addresses anyway
    if(mLocal) {

        onTimeout();

    } else {

        mAddress.setAddress(mHost);

        // If the address is invalid, it's probably a hostname - look it up
        // Otherwise, jump immediately to the timeout slot
        if(mAddress.isNull()) {
            mHostLookup = QHostInfo::lookupHost(mHost, this, SLOT(onLookupHost(QHostInfo)));
        } else {
            onTimeout();
        }
    }
}

void Device::cancel()
{
    if(isBusy()) {

        // We are either waiting for a lookup or timer
        if(mHostLookup != -1) {
            QHostInfo::abortHostLookup(mHostLookup);
        } else {
            mTimer.stop();
        }

        emit finished();
    }
}

bool Device::fromJson(const QJsonObject &object)
{
    // Make sure none of the fields are missing
    if(!object.contains("title") ||
            !object.contains("local") ||
            !object.contains("host") ||
            !object.contains("mac") ||
            !object.contains("port")) {
        return false;
    }

    // TODO: verify the data

    mTitle = object.value("title").toString();
    mLocal = object.value("local").toBool();
    mHost = object.value("host").toString();
    mMac = object.value("mac").toString();
    mPort = object.value("port").toInt();

    return true;
}

QJsonObject Device::toJson()
{
    QJsonObject object;

    object.insert("title", mTitle);
    object.insert("local", mLocal);
    object.insert("host", mHost);
    object.insert("mac", mMac);
    object.insert("port", mPort);

    return object;
}

void Device::onLookupHost(const QHostInfo &info)
{
    mHostLookup = -1;

    // Check to ensure that there was no error performing the lookup
    if(info.error() == QHostInfo::NoError) {

        // Grab the first address and jump to the timeout slot
        mAddress = info.addresses().first();
        onTimeout();

    } else {

        // Emit the error and indicate that the wake process finished
        emit error(info.errorString());
        emit finished();
    }
}

void Device::onTimeout()
{
    QByteArray packet = buildPacket();

    if(mLocal) {

        // For local broadcasts, enumerate all network interfaces and send the
        // packet on all of the ones that have a valid broadcast address
        foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces()) {
            if(interface.flags() & QNetworkInterface::CanBroadcast) {
                foreach(QNetworkAddressEntry entry, interface.addressEntries()) {
                    if(!entry.broadcast().isNull()) {

                        // TODO: failure is ignored here
                        mSocket.writeDatagram(packet, entry.broadcast(), mPort);
                    }
                }
            }
        }

    } else {

        // Write the packet to the socket
        if(mSocket.writeDatagram(packet, mAddress, mPort) == -1) {

            emit error(mSocket.errorString());
            emit finished();
            return;

        }
    }

    // Decrement the number of remaining packets
    --mPacketsRemaining;

    // Check to see if the last packet was sent
    if(mPacketsRemaining) {
        mTimer.start();
    } else {
        emit finished();
    }
}

QByteArray Device::buildPacket()
{
    // The first six bytes contain the value 255
    QByteArray packet(6, '\xff');

    // Parse the MAC address by interpreting the data as hexadecimal
    QByteArray macAddress = QByteArray::fromHex(mMac.toUtf8());

    // Append sixteen repetitions of the MAC address
    for(int i = 0; i < 16; ++i) {
        packet.append(macAddress);
    }

    return packet;
}
