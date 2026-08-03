#include "sensei_control.h"

ControlSensei::ControlSensei(DatabaseWorker *dw, Resources *rs, QObject *parent)
    : m_list(new ListSensei(dw, rs)), m_form(new FormSensei(dw, rs)), QObject{parent}
{
    connect(m_form, &FormSensei::itemAdded, m_list, &ListSensei::onAdded);
    connect(m_form, &FormSensei::itemUpdated, m_list, &ListSensei::onUpdated);
}

ListSensei *ControlSensei::list() const
{
    return m_list;
}

FormSensei *ControlSensei::form() const
{
    return m_form;
}

void ControlSensei::edit(int id)
{
    m_form->load(id);
}
