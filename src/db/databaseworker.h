#pragma once

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QSettings>

#include "../utils/utils.h"

class DatabaseWorker : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWorker(QSqlDatabase *db, QObject *parent = nullptr);

    bool post(int *id, const Playoff::Table& table, const Playoff::Query& query, const QVariantMap& card);
    void get(QList<QVariantMap> *result,
             const Playoff::Table& table,
             const QVariantMap& filter = QVariantMap(),
             const Playoff::Selector& selector = Playoff::Selector::kDefault);
    bool del(int id, const Playoff::Table& table, const QVariantMap& filter = QVariantMap());



private:
    QSqlDatabase *m_db;
    QHash<QueryKey, QString> m_register;

    void registerQueries();

    bool makeQuery(QSqlQuery *db_query, const QueryKey &key, const QVariantMap& card, const QVariantMap& filter);
    void regQuery(const QueryKey &key, const QString &str);
    void getQuqery(QString *str, const QueryKey &key);

    void binding(QSqlQuery *db_query, const QueryKey &key, const QVariantMap& card, const QVariantMap& filter);






signals:
};
