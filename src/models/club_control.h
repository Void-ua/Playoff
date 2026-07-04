#pragma once

#include <QObject>

#include "../utils/resource.h"
#include "../db/databaseworker.h"

#include "club_form.h"
#include "clubs_list.h"

class ControlClub : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ListClubs* list READ list CONSTANT);
    Q_PROPERTY(FormClub* form READ form CONSTANT);

public:
    explicit ControlClub(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);

    ListClubs *list() const;
    FormClub *form() const;

    Q_INVOKABLE void edit(int id);

signals:
private:
    ListClubs *m_list = nullptr;
    FormClub *m_form = nullptr;
};
