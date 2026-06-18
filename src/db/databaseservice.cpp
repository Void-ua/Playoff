#include "databaseservice.h"

DatabaseService::DatabaseService(QSqlDatabase *db, QObject *parent)
    : m_db(db), QObject{parent}
{}

bool DatabaseService::init()
{
    QFile file(":/sql/001_init.sql");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString context = file.readAll();

        QSqlQuery query(*m_db);
        bool r = query.exec(context);
        if (r) writeMigraion(file.fileName());
        qDebug() << "Init migration: " << r;
        return r;
    } else {
        qDebug() << "Migration file not found";
    }
    return false;
}

void DatabaseService::makeMigration()
{
    QSqlQuery query(*m_db);
    query.exec("SELECT t.name FROM migrations as t ");
    QStringList migrated;
    while (query.next()) {
        migrated.append(query.value("name").toString());
    }
    qDebug() << "Migrated list: " << migrated;

    QDir migrationDir(":/sql");
    QStringList file_list = migrationDir.entryList(QStringList() << "*.sql", QDir::Files, QDir::Name);
    QStringList migration_list;
    for (const QString &fname : file_list) {
        if (!migrated.contains(":/sql/" + fname)) {
            migration_list.append(":/sql/" + fname);
        }
    }

    if (migration_list.isEmpty()) return;

    for (const QString &file_name : migration_list) {
        QStringList query_list;
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly |QIODevice::Text)) {
            QString context = file.readAll();
            makeMigrationQuery(context, &query_list);
        }

        qDebug() << "mgr: " << file_name;

        m_db->transaction();
        for (const QString & q_str : query_list) {
            bool x = query.exec(q_str);
            if (!x) {
                qDebug() << "q: " <<query.lastQuery() << " err: " << query.lastError();
            }
        }
        bool r = m_db->commit();

        if (r) {
            writeMigraion(file_name);
        } else {
            m_db->rollback();
        }
    }
}

void DatabaseService::makeMigrationQuery(const QString &context, QStringList *queryList)
{
    queryList->clear();
    for (const QString &line : context.split(";")){
        queryList->append(line.simplified());
    }
}

void DatabaseService::writeMigraion(const QString &name)
{
    QSqlQuery query(*m_db);
    query.prepare("INSERT INTO migrations (name) VALUES (?);");
    query.bindValue(0, name);
    bool i = query.exec();
    if (!i) {
        qDebug() << "Err write migration: " << m_db->lastError().text();
    }
}
