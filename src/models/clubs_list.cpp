#include "clubs_list.h"

ListClubs::ListClubs(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QAbstractListModel{parent}
{}


int ListClubs::rowCount(const QModelIndex &parent) const
{
    Container<Club> *m_data = m_resource->container<Club>();
    return m_data->count();
}

QVariant ListClubs::data(const QModelIndex &index, int role) const
{
    QVariant res;
    if (!index.isValid()) return res;

    Container<Club> *m_data = m_resource->container<Club>();
    const Club *card = m_data->item(index.row());

    switch (role) {
    case kId: return card->id;
    case kName: return card->name;
    case kLocation: return card->location;
    }
    return res;
}

QHash<int, QByteArray> ListClubs::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[kId] = "m_id";
    roles[kName] = "m_name";
    roles[kLocation] = "m_location";

    return roles;
}

void ListClubs::update()
{
    Container<Club> *m_data = m_resource->container<Club>();
    if (m_data->count() == 0) {
        beginResetModel();
        QList<QVariantMap> list_data;
        m_dw->get(&list_data, Playoff::Table::kClub, {}, Playoff::Selector::kAll);
        ClubMapper::list(list_data, m_data);
        endResetModel();
    }
}

void ListClubs::onAdded()
{
    Container<Club> *m_data = m_resource->container<Club>();
    int pos = m_data->count() - 1;
    beginInsertRows(QModelIndex(), pos, pos);
    endInsertRows();
}

void ListClubs::onUpdated(int pos)
{
    emit dataChanged(index(pos), index(pos));
}

void ListClubs::onDeleted(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    endRemoveRows();
}