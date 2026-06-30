#pragma once

#include <QObject>

#include "../utils/resource.h"
#include "../db/databaseworker.h"

#include "tournament_form.h"
#include "tournament_list.h"

class ControlTournament : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ListTournament* list READ list CONSTANT);
    Q_PROPERTY(FormTournament* form READ form CONSTANT);

public:
    explicit ControlTournament(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);


    ListTournament *list() const;
    FormTournament *form() const;

    Q_INVOKABLE void edit(int id);

signals:
private:
    ListTournament *m_list = nullptr;
    FormTournament *m_form = nullptr;
};
