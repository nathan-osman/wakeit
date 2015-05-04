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

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "devicemodel.h"

DeviceModel::DeviceModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

DeviceModel::~DeviceModel()
{
    qDeleteAll(mDevices);
}

int DeviceModel::rowCount(const QModelIndex &parent) const
{
    return mDevices.count();
}

QVariant DeviceModel::data(const QModelIndex &index, int role) const
{
    if(index.row() >= mDevices.count()) {
        return QVariant();
    }

    Device *device = mDevices.at(index.row());

    switch(role) {
    case Title:
        return device->title;
    case Type:
        return device->type;
    case Host:
        return device->host;
    case MAC:
        return device->mac;
    case Port:
        return device->port;
    case Busy:
        return true;
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DeviceModel::roleNames() const
{
    return {
        { Title, "title" },
        { Type, "type" },
        { Host, "host" },
        { MAC, "mac" },
        { Port, "port" },
        { Busy, "busy" }
    };
}

bool DeviceModel::load()
{
    QFile dataFile("data.json");

    // First check to see if the file even exists
    // If not, this is the first run, so return true
    if(!dataFile.exists()) {
        return true;
    }

    // The file exists, try to open it
    if(!dataFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    // If the JSON is valid, the devices variable should be an array
    QJsonDocument document = QJsonDocument::fromJson(dataFile.readAll());
    QJsonObject root = document.object();
    QJsonValue devices = root.value("devices");
    if(!devices.isArray()) {
        return false;
    }

    // Empty the current list
    qDeleteAll(mDevices);

    // Add the new items to the model
    beginResetModel();
    foreach(QJsonValue device, devices.toArray()) {
        if(device.isObject()) {
            mDevices.append(new Device(device.toObject()));
        }
    }
    endResetModel();

    return true;
}

bool DeviceModel::save()
{
    QFile dataFile("data.json");

    // Attempt to open the file
    if(!dataFile.open(QIODevice::ReadWrite)) {
        return false;
    }

    QJsonArray devices;

    foreach(Device *device, mDevices) {
        devices.append(device->toJson());
    }
}

void DeviceModel::add(const QString &title, AddressType type, const QString &host, const QString &mac, quint16 port)
{
    Device *device = new Device;
    device->title = title;
    device->type = type;
    device->host = host;
    device->mac = mac;
    device->port = port;

    beginInsertRows(QModelIndex(), mDevices.count(), mDevices.count());
    mDevices.append(device);
    endInsertRows();
}

void DeviceModel::remove(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    delete mDevices.takeAt(index);
    endRemoveRows();
}

void DeviceModel::wake(int index)
{
    //...
}