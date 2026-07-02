#include "formclub.h"

FormClub::FormClub(QObject *parent)
    : QObject{parent}
{ }

void FormClub::load(int id)
{

}

bool FormClub::post()
{

}

bool FormClub::reset()
{

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
