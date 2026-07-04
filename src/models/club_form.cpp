#include "club_form.h"

FormClub::FormClub(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QObject{parent}
{ }

void FormClub::load(int id)
{
    if (id == 0) {
        reset();
        return;
    }

    Container<Club> *m_data = m_resource->container<Club>();
    const Club* card = m_data->itemById(id);

    setIdx(card->id);
    setName(card->name);
    setLocation(card->location);
}

bool FormClub::post()
{
    Club card;
    card.id = m_idx;
    card.name = m_name;
    card.location = m_location;

    Playoff::Query query = m_idx == 0 ? Playoff::Query::kInsert : Playoff::Query::kUpdate;
    Playoff::Table table = Playoff::Table::kClub;

    QVariantMap save_card;
    ClubMapper::toVarianMap(&card, &save_card);
    bool r = m_dw->post(&m_idx, table, query, save_card);
    if (!r) {
        qDebug() << "Error post";
        return false;
    }

    card.id = m_idx;

    Container<Club> *m_data = m_resource->container<Club>();
    if (query == Playoff::Query::kInsert) {
        m_data->add(card);
        emit itemAdded();
    } else {
        m_data->update(card);
        int pos = m_data->pos(card.id);
        emit itemUpdated(pos);
    }
    return true;

}

bool FormClub::reset()
{
    setIdx(0);
    setName(QString());
    setLocation(QString());
    return true;
}

void FormClub::validate()
{
    bool r = m_name.size() > 0;
    setSaveValid(r);
}

int FormClub::idx() const
{
    return m_idx;
}

void FormClub::setIdx(int newIdx)
{
    if (m_idx == newIdx)
        return;
    m_idx = newIdx;
    emit idxChanged();
}

QString FormClub::name() const
{
    return m_name;
}

void FormClub::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    validate();
    emit nameChanged();
}

QString FormClub::location() const
{
    return m_location;
}

void FormClub::setLocation(const QString &newLocation)
{
    if (m_location == newLocation)
        return;
    m_location = newLocation;
    emit locationChanged();
}

bool FormClub::saveValid() const
{
    return m_saveValid;
}

void FormClub::setSaveValid(bool newSaveValid)
{
    if (m_saveValid == newSaveValid)
        return;
    m_saveValid = newSaveValid;
    emit saveValidChanged();
}

bool FormClub::delValid() const
{
    return m_delValid;
}

void FormClub::setDelValid(bool newDelValid)
{
    if (m_delValid == newDelValid)
        return;
    m_delValid = newDelValid;
    emit delValidChanged();
}
