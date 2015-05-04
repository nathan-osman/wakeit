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

#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QAbstractListModel>
#include <QList>

/**
 * @brief Models a list of devices
 */
class DeviceModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(AddressType)

public:

    /**
     * @brief Roles for retrieving data from the model
     */
    enum Role {
        /// Title displayed for the device
        Title = Qt::UserRole,
        /// Type of address used for host
        Type,
        /// Hostname or IP address
        Host,
        /// MAC address of the device
        MAC,
        /// Port to send packets to
        Port,
        /// Whether the device is currently busy
        Busy
    };

    /**
     * @brief Address used for sending packets to
     */
    enum AddressType {
        /// Send packets to the broadcast address
        LAN = 0,
        /// Send packets to an IP address
        WAN
    };

    /**
     * @brief Create a new device model
     * @param parent parent QObject
     */
    explicit DeviceModel(QObject *parent = nullptr);

    /**
     * @brief Destroy the device model
     */
    virtual ~DeviceModel();

    /**
     * @brief Reimplementation of QAbstractListModel::rowCount()
     */
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     * @brief Reimplementation of QAbstractListModel::data()
     */
    virtual QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief Reimplementation of QAbstractListModel::roleNames()
     */
    virtual QHash<int, QByteArray> roleNames() const;

    /**
     * @brief Attempt to load model data from disk
     * @return true if no error occurred
     */
    Q_INVOKABLE bool load();

    /**
     * @brief Attempt to save model data to disk
     * @return true if no error occurred
     */
    Q_INVOKABLE bool save();

    /**
     * @brief Add a new device to the model
     * @param title descriptive name for the device
     * @param type type of address
     * @param host device host
     * @param mac device MAC address
     * @param port port for magic packet
     */
    Q_INVOKABLE void add(const QString &title, AddressType type, const QString &host, const QString &mac, quint16 port);

    /**
     * @brief Remove a device from the model
     * @param index device index
     */
    Q_INVOKABLE void remove(int index);

    /**
     * @brief Wake a device from the model
     * @param index device index
     */
    Q_INVOKABLE void wake(int index);

private:

    // Data for an individual item
    class Device
    {
    public:

        //Device();
        //~Device();

        QString title;
        AddressType type;
        QString host;
        QString mac;
        quint16 port;
    };

    QList<Device*> mDevices;
};

#endif // DEVICEMODEL_H
