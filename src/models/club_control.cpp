#include "club_control.h"

ControlClub::ControlClub(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_list(new ListClubs(dw, rs)), m_form(new FormClub(dw, rs)), QObject{parent}
{
    connect(m_form, &FormClub::itemAdded, m_list, &ListClubs::onAdded);
    connect(m_form, &FormClub::itemUpdated, m_list, &ListClubs::onUpdated);
}

ListClubs *ControlClub::list() const
{
    return m_list;
}

FormClub *ControlClub::form() const
{
    return m_form;
}

void ControlClub::edit(int id)
{
    m_form->load(id);
}
