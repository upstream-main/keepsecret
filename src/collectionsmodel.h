// SPDX-License-Identifier: GPL-2.0-or-later
// SPDX-FileCopyrightText: 2025 Marco Martin <notmart@gmail.com>

#pragma once

#include "secretserviceclient.h"
#include <QAbstractListModel>

class SecretServiceClient;

class CollectionsModel : public QAbstractListModel
{
    Q_OBJECT

    // Exposed to QML so we can react to the number of wallets
    Q_PROPERTY(int count READ count NOTIFY countChanged)

    Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)

public:
    enum Roles {
        DbusPathRole = Qt::UserRole + 1,
        LockedRole
    };
    Q_ENUM(Roles)

    explicit CollectionsModel(SecretServiceClient *secretServiceClient, QObject *parent = nullptr);
    ~CollectionsModel() override;

    QString collectionPath() const;
    void setCollectionPath(const QString &collectionPath);

    int currentIndex() const;

    // Helper for QML to read the number of wallets
    int count() const;

    Q_INVOKABLE QString dbusPathAt(int row) const;

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

Q_SIGNALS:
    void currentIndexChanged();
    void countChanged();

protected:
    void reloadWallets();

private:
    SecretServiceClient *const m_secretServiceClient;
    QList<SecretServiceClient::CollectionEntry> m_wallets;
    QString m_currentCollectionPath;
};
