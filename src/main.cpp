/*
 * Playoff
 * by Void
 *
 * 2026.06
 * Ukraine
 */

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QDate>
#include <QtSql/QSqlDatabase>

#include "db/databaseservice.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Void");
    app.setApplicationName("Playoff");

    //setting
    QSettings settings("Void", "Playoff");


    //database
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE", "base");
    database.setDatabaseName("base.sqlite3");
    database.open();

    if (!database.isOpen()) {
        qCritical() << "Database is closed";
        return -1;
    }

    DatabaseService *db_service = new DatabaseService(&database);
    qDebug() << "Database opened";

    if (!settings.contains("app/last_session")){
        bool r = db_service->init();
        if (!r) {
            qCritical() << "Database not initialized";
            return -1;
        }
        qDebug() << "Database inited success";
    }

    //migrations
    db_service->makeMigration();


    // qml engine
    qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("UiPlayoff", "Main");

    settings.setValue("app/last_session", QDate::currentDate().toString("dd.MM.yyyy"));

    return QGuiApplication::exec();
}
