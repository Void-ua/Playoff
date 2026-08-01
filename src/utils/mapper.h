#pragma once

#include "datas.h"
#include "resource.h"
#include <QObject>
#include <QLocale>
#include <QVariantMap>

class TournamentMapper {
public:
    static void toVariantMap(const Tournament *doc, QVariantMap *map) {
        map->clear();
        map->insert("id", doc->id);
        map->insert("name", doc->name);
        map->insert("place", doc->place);
        map->insert("tdate", doc->tdate.toJulianDay());
        map->insert("referre", doc->referre);
        map->insert("secretary", doc->secretary);
    }
    static void fromVariantMap(const QVariantMap& map, Tournament *doc){
        doc->id = map.value("id", 0).toInt();
        doc->name = map.value("name", QString()).toString();
        doc->place = map.value("place", QString()).toString();
        doc->tdate = QDate::fromJulianDay(map.value("tdate", QDate::currentDate().toJulianDay()).toInt());
        doc->referre = map.value("referre", QString()).toString();
        doc->secretary = map.value("secretary", QString()).toString();
    };
    static void list(const QList<QVariantMap> &vData, Container<Tournament> *rData) {
        rData->clear();
        for (const QVariantMap &m : vData) {
            Tournament doc;
            fromVariantMap(m, &doc);
            rData->add(doc);
        }
    }
};

class ClubMapper {
public:
    static void toVarianMap(const Club *doc, QVariantMap *map) {
        map->clear();
        map->insert("id", doc->id);
        map->insert("name", doc->name);
        map->insert("location", doc->location);
    };
    static void fromVariantMap(const QVariantMap& map, Club *doc) {
        doc->id = map.value("id", 0).toInt();
        doc->name = map.value("name", QString()).toString();
        doc->location = map.value("location", QString()).toString();
    };
    static void list(const QList<QVariantMap> &vData, Container<Club> *rData) {
        rData->clear();
        for (const QVariantMap &m : vData) {
            Club doc;
            fromVariantMap(m, &doc);
            rData->add(doc);
        }
    };
};

class SenseiMapper {
public:
    static void toVariantMap(const Sensei *doc, QVariantMap *map){
        map->clear();
        map->insert("id", doc->id);
        map->insert("club_id", doc->club_id);
        map->insert("name", doc->name);
    };
    static void fromVariantMap(const QVariantMap& map, Sensei *doc) {
        doc->id = map.value("id").toInt();
        doc->club_id = map.value("club_id").toInt();
        doc->name = map.value("name").toString();
    };
    static void list(const QList<QVariantMap> &vData, Container<Sensei> *rData) {
        rData->clear();
        for (const QVariantMap &m : vData) {
            Sensei doc;
            fromVariantMap(m, &doc);
            rData->add(doc);
        }
    };
};
