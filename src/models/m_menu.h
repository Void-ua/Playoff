#pragma once

#include <QAbstractListModel>
#include <QObject>

#include "../utils/utils.h"


class ModelMenu : public QAbstractListModel {
    Q_OBJECT
public:
    explicit ModelMenu(QObject *parent = nullptr);

    enum Role {
        kID,
        kType
    };
};
