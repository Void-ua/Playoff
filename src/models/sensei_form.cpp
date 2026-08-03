#include "sensei_form.h"

FormSensei::FormSensei(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QObject{parent}
{ }

void FormSensei::load(int id)
{
    if (id == 0) {
        reset();
        return;
    }

    Container<Sensei> *m_data = m_resource->container<Sensei>();
    const Sensei *card = m_data->itemById(id);

    setIdx(card->id);
    setClub(card->club_id);
    setName(card->name);
}

bool FormSensei::post()
{
    Sensei card;
    card.id = m_idx;
    card.club_id = m_club;
    card.name = m_name;

    Playoff::Query query = m_idx == 0 ? Playoff::Query::kInsert : Playoff::Query::kUpdate;
    Playoff::Table table = Playoff::Table::kSensei;

    QVariantMap save_card;
    SenseiMapper::toVariantMap(&card, &save_card);
    bool r = m_dw->post(&m_idx, table, query, save_card);

    if (!r) {
        qDebug() << "Error post";
        return false;
    }

    card.id = m_idx;

    Container<Sensei> *m_data = m_resource->container<Sensei>();
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

bool FormSensei::reset()
{
    setIdx(0);
    setClub(0);
    setName(QString());
    return true;
}

void FormSensei::validate()
{
    bool r = m_name.size() > 0 && m_club > 0;
    setSaveValid(r);

}

int FormSensei::idx() const
{
    return m_idx;
}

void FormSensei::setIdx(int newIdx)
{
    if (m_idx == newIdx)
        return;
    m_idx = newIdx;
    emit idxChanged();
}

QString FormSensei::name() const
{
    return m_name;
}

void FormSensei::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    validate();
    emit nameChanged();
}

bool FormSensei::saveValid() const
{
    return m_saveValid;
}

void FormSensei::setSaveValid(bool newSaveValid)
{
    if (m_saveValid == newSaveValid)
        return;
    m_saveValid = newSaveValid;
    emit saveValidChanged();
}

bool FormSensei::delValid() const
{
    return m_delValid;
}

void FormSensei::setDelValid(bool newDelValid)
{
    if (m_delValid == newDelValid)
        return;
    m_delValid = newDelValid;
    emit delValidChanged();
}

int FormSensei::club() const
{
    return m_club;
}

void FormSensei::setClub(int newClub)
{
    if (m_club == newClub)
        return;
    m_club = newClub;
    validate();
    emit clubChanged();
}
