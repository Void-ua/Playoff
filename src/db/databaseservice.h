/*
 * Playoff
 * by Void
 *
 * 2026.06
 * Ukraine
 */

#pragma once

#include <QObject>
#include <QFile>
#include <QDir>
#include <QIODevice>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>


class DatabaseService : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseService(QSqlDatabase *db, QObject *parent = nullptr);

    bool init();
    void makeMigration();
    void makeMigrationQuery(const QString& context, QStringList *queryList);



signals:

private:
    QSqlDatabase *m_db;

    void writeMigraion(const QString& name);

};
