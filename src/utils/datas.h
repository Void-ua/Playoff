#pragma once

#include <QObject>
#include <QDateTime>

struct Tournament {
    int id;
    QString name;
    QString place;
    QDate tdate;
    QString referre;
    QString secretary;
    QDateTime created;

    Tournament() = default;
    Tournament(int id_, const QString& name_, const QString& place_,
               const QDate& tdate_, const QString& referre_,
               const QString& secretary_, const QDateTime& created_) :
        id(id_), name(name_), place(place_), tdate(tdate_), referre(referre_),
        secretary(secretary_), created(created_) {};

};
