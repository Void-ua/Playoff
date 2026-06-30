#include "tournament_list.h"

ListTournament::ListTournament(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QAbstractListModel{parent}
{}


int ListTournament::rowCount(const QModelIndex &parent) const
{
    Container<Tournament> *m_data = m_resource->container<Tournament>();
    return m_data->count();
}

QVariant ListTournament::data(const QModelIndex &index, int role) const
{
    QVariant res;
    QLocale locale;
    if (!index.isValid()) return res;

    Container<Tournament>* m_data = m_resource->container<Tournament>();

    const Tournament *card = m_data->item(index.row());
    switch (role) {
    case kId: return card->id;
    case kName: return card->name;
    case kPlace: return card->place;
    case kDate: return card->tdate.toString("dd.MM.yyyy");//toString(locale.dateFormat(QLocale::ShortFormat));
    case kReferre: return card->referre;
    case kSecretary: return card->secretary;
    }
    return res;
}

QHash<int, QByteArray> ListTournament::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[kId] = "m_id";
    roles[kName] = "m_name";
    roles[kPlace] = "m_place";
    roles[kDate] = "m_date";
    roles[kReferre] = "m_referre";
    roles[kSecretary] = "m_secretary";
    return roles;
}

void ListTournament::update()
{
    Container<Tournament> *m_data = m_resource->container<Tournament>();
    if (m_data->count() == 0) {
        beginResetModel();
        QList<QVariantMap> list_data;
        m_dw->get(&list_data, Playoff::Table::kTournament, {}, Playoff::Selector::kAll);
        TournamentMapper::list(list_data, m_data);
        endResetModel();
    }
}

void ListTournament::onAdded()
{
    Container<Tournament> *m_data = m_resource->container<Tournament>();
    int pos = m_data->count() - 1;
    beginInsertRows(QModelIndex(), pos, pos);
    endInsertRows();
}

void ListTournament::onUpdated(int pos)
{
    emit dataChanged(index(pos), index(pos));
}

void ListTournament::onDeleted(int pos)
{
    beginRemoveRows(QModelIndex(), pos, pos);
    endRemoveRows();
}