#pragma once

#include <QObject>

#include "../utils/resource.h"
#include "../db/databaseworker.h"

#include "sensei_form.h"
#include "sensei_list.h"

class ControlSensei : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ListSensei* list READ list CONSTANT);
    Q_PROPERTY(FormSensei* form READ form CONSTANT);

public:
    explicit ControlSensei(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);

    ListSensei *list() const;
    FormSensei *form() const;

    Q_INVOKABLE void edit(int id);

signals:
private:
    ListSensei *m_list = nullptr;
    FormSensei *m_form = nullptr;
};
