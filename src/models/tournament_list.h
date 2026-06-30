#pragma once

#include <QAbstractListModel>
#include <QObject>

#include "../db/databaseworker.h"
#include "../utils/resource.h"
#include "../utils/mapper.h"

class ListTournament : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListTournament(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);

    enum Roles {
        kId,
        kName,
        kPlace,
        kDate,
        kReferre,
        kSecretary
    };

    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void update();

public slots:
    void onAdded();
    void onUpdated(int pos);
    void onDeleted(int pos);

private:
    DatabaseWorker *m_dw;
    Resources *m_resource;
};
