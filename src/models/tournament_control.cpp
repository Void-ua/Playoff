#include "tournament_control.h"

ControlTournament::ControlTournament(DatabaseWorker *dw, Resources *rs, QObject *parent)
    :  m_list(new ListTournament(dw, rs)), m_form(new FormTournament(dw, rs)), QObject{parent}
{

    connect(m_form, &FormTournament::itemAdded, m_list, &ListTournament::onAdded);
    connect(m_form, &FormTournament::itemUpdated, m_list, &ListTournament::onUpdated);


}

ListTournament *ControlTournament::list() const
{
    return m_list;
}

FormTournament *ControlTournament::form() const
{
    return m_form;
}

void ControlTournament::edit(int id)
{
    m_form->load(id);
}
