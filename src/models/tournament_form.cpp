#include "tournament_form.h"

FormTournament::FormTournament(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_dw(dw), m_resource(rs), QObject{parent}
{}

void FormTournament::load(int id)
{
    if (id == 0) {
        reset();
        return;
    }

    Container<Tournament> *m_data = m_resource->container<Tournament>();
    const Tournament* card = m_data->itemById(id);

    setIdx(card->id);
    setName(card->name);
    setPlace(card->place);
    setTdate(card->tdate);
    setReferre(card->referre);
    setSecretary(card->secretary);

}

bool FormTournament::post()
{
    Tournament card;
    card.id = m_idx;
    card.name = m_name;
    card.place = m_place;
    card.tdate = m_tdate;
    card.referre = m_referre;
    card.secretary = m_secretary;

    Playoff::Query query = m_idx == 0 ? Playoff::Query::kInsert : Playoff::Query::kUpdate;
    Playoff::Table table = Playoff::Table::kTournament;

    QVariantMap save_card;
    TournamentMapper::toVariantMap(&card, &save_card);
    bool r = m_dw->post(&m_idx, table, query, save_card);

    if (!r) {
        qDebug() << "Error post";
        return false;
    }

    Container<Tournament> *m_data = m_resource->container<Tournament>();
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

bool FormTournament::reset()
{
    setIdx(0);
    setName(QString());
    setPlace(QString());
    setTdate(QDate::currentDate());
    setReferre(QString());
    setSecretary(QString());

    return true;
}

int FormTournament::idx() const
{
    return m_idx;
}

void FormTournament::setIdx(int newIdx)
{
    if (m_idx == newIdx)
        return;
    m_idx = newIdx;
    emit idxChanged();
}

QString FormTournament::name() const
{
    return m_name;
}

void FormTournament::setName(const QString &newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    validate();
    emit nameChanged();
}

QString FormTournament::place() const
{
    return m_place;
}

void FormTournament::setPlace(const QString &newPlace)
{
    if (m_place == newPlace)
        return;
    m_place = newPlace;
    validate();
    emit placeChanged();
}

QDate FormTournament::tdate() const
{
    return m_tdate;
}

void FormTournament::setTdate(const QDate &newTdate)
{
    if (m_tdate == newTdate)
        return;
    m_tdate = newTdate;
    emit tdateChanged();
}

QString FormTournament::referre() const
{
    return m_referre;
}

void FormTournament::setReferre(const QString &newReferre)
{
    if (m_referre == newReferre)
        return;
    m_referre = newReferre;
    emit referreChanged();
}

QString FormTournament::secretary() const
{
    return m_secretary;
}

void FormTournament::setSecretary(const QString &newSecretary)
{
    if (m_secretary == newSecretary)
        return;
    m_secretary = newSecretary;
    emit secretaryChanged();
}


bool FormTournament::saveValid() const
{
    return m_saveValid;
}

void FormTournament::setSaveValid(bool newSaveValid)
{
    if (m_saveValid == newSaveValid)
        return;
    m_saveValid = newSaveValid;
    emit saveValidChanged();
}

bool FormTournament::delValid() const
{
    return m_delValid;
}

void FormTournament::setDelValid(bool newDelValid)
{
    if (m_delValid == newDelValid)
        return;
    m_delValid = newDelValid;
    emit delValidChanged();
}

void FormTournament::validate()
{
    bool v = m_name.size() > 0 && m_place.size() > 0;
    setSaveValid(v);
}
