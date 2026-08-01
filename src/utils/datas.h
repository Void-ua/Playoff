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

    Tournament() = default;
    Tournament(int id_, const QString& name_, const QString& place_,
               const QDate& tdate_, const QString& referre_,
               const QString& secretary_, const QDateTime& created_) :
        id(id_), name(name_), place(place_), tdate(tdate_), referre(referre_),
        secretary(secretary_) {};

};

struct Club {
    int id;
    QString name;
    QString location;

    Club() = default;
    Club(int id_, const QString& name_, const QString &location_):
        id(id_), name(name_), location(location_) {};
};

struct Sensei {
    int id;
    int club_id;
    QString name;

    Sensei() = default;
    Sensei(int id_, int club_id_, const QString& name_):
        id(id_), club_id(club_id_), name(name_) {};
};
