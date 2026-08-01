#include "sensei_list.h"

ListSensei::ListSensei(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QAbstractListModel{parent}
{ }


int ListSensei::rowCount(const QModelIndex &parent) const
{
    Container<Sensei> *m_data = m_resource->container<Sensei>();
    return m_data->count();
}

QVariant ListSensei::data(const QModelIndex &index, int role) const
{
    QVariant res;
    if (!index.isValid()) return res;

    Container<Sensei> *m_data = m_resource->container<Sensei>();
    const Sensei *card = m_data->item(index.row());

    Container<Club> *m_club = m_resource->container<Club>();
    const Club *card_club = m_club->itemById(card->club_id);

    switch (role) {
    case kId: return card->id;
    case kClubId: return card->club_id;
    case kClubName: return card_club->name;
    case kName: return card->name;
    }

    return res;
}

QHash<int, QByteArray> ListSensei::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[kId] = "m_id";
    roles[kClubId] = "m_club_id";
    roles[kClubName] = "m_club_name";
    roles[kName] = "m_name";
    return roles;
}

void ListSensei::update()
{
    Container<Sensei> *m_data = m_resource->container<Sensei>();
    if (m_data->count() == 0) {
        beginResetModel();
        QList<QVariantMap> list_data;
        m_dw->get(&list_data, Playoff::Table::kSensei, {}, Playoff::Selector::kAll);
        SenseiMapper::list(list_data, m_data);
        endResetModel();
    }
}

void ListSensei::onAdded()
{
    Container<Sensei> *m_data = m_resource->container<Sensei>();
    int pos = m_data->count() - 1;
    beginInsertRows(QModelIndex(), pos, pos);
    endInsertRows();
}

void ListSensei::onUpdated(int pos)
{
    emit dataChanged(index(pos), index(pos));
}

void ListSensei::onDeleted(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    endRemoveRows();
}