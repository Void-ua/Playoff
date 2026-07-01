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

        qDebug() << "TV:" << doc->tdate;
    }
    static void fromVariantMap(const QVariantMap& map, Tournament *doc){
        doc->id = map.value("id", 0).toInt();
        doc->name = map.value("name", QString()).toString();
        doc->place = map.value("place", QString()).toString();
        doc->tdate = QDate::fromJulianDay(map.value("tdate", QDate::currentDate().toJulianDay()).toInt());
        doc->referre = map.value("referre", QString()).toString();
        doc->secretary = map.value("secretary", QString()).toString();

        qDebug() << "FV tdate:" << map.value("tdate");
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
