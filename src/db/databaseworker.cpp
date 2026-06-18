#include "databaseworker.h"

DatabaseWorker::DatabaseWorker(QSqlDatabase *db, QObject *parent)
    : m_db(db), QObject{parent}
{}

bool DatabaseWorker::post(int *id, const Playoff::Table &table, const Playoff::Query &query, const QVariantMap &card)
{
    QSqlQuery base_query(*m_db);
    QueryKey key = QueryKey(table, query, Playoff::Selector::kDefault);
    bool r = makeQuery(&base_query, key, card, {});
    if (!r) return false;

    *id = card.value("id", 0).toInt();
    if (query == Playoff::Query::kInsert) {
        *id = base_query.lastInsertId().toInt();
    }

    return true;
}

void DatabaseWorker::get(QList<QVariantMap> *result, const Playoff::Table &table, const QVariantMap &filter, const Playoff::Selector &selector)
{
    Playoff::Query query = Playoff::Query::kSelect;
    QueryKey key = QueryKey(table, query, selector);
    QSqlQuery base_query(*m_db);

    bool r = makeQuery(&base_query, key, {}, filter);

    if (!r) return;

    while (base_query.next()) {
        QVariantMap raw_data;
        for (int r = 0; r < base_query.record().count(); r++){
            QString col_name = base_query.record().fieldName(r);

            raw_data.insert(col_name, base_query.value(r));
        }
        result->append(raw_data);
    }
}

bool DatabaseWorker::del(int id, const Playoff::Table &table, const QVariantMap &filter)
{
    Playoff::Query query = Playoff::Query::kDelete;
    QueryKey key = QueryKey(table, query, Playoff::Selector::kDefault);
    QSqlQuery base_query(*m_db);
    bool r = makeQuery(&base_query, key, {{"id", id}}, filter);
    return r;
}

void DatabaseWorker::registerQueries()
{
    // club
    regQuery(QueryKey(Playoff::Table::kClub, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO club (name, place) VALUES (?, ?);");
    regQuery(QueryKey(Playoff::Table::kClub, Playoff::Query::kUpdate, Playoff::Selector::kDefault), "UPDATE club SET name = ?, place = ? WHERE club.id = ?;");
    regQuery(QueryKey(Playoff::Table::kClub, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM club WHERE club.id = ?;");
    regQuery(QueryKey(Playoff::Table::kClub, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM club ORDER BY club.name ASC;");

    // category
    regQuery(QueryKey(Playoff::Table::kCategory, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO category (name) VALUES (?);");
    regQuery(QueryKey(Playoff::Table::kCategory, Playoff::Query::kInsert, Playoff::Selector::kDefault),"UPDATE category SET name = ? WHERE category.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCategory, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM category WHERE category.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCategory, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM category ORDER BY category.name ASC;");

    // participants
    regQuery(QueryKey(Playoff::Table::kParticipants, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO participants (name, club_id, level, born) VALUES (?, ?, ?, ?);");
    regQuery(QueryKey(Playoff::Table::kParticipants, Playoff::Query::kInsert, Playoff::Selector::kDefault),"UPDATE participants SET name = ?, club_id = ?, level = ?, born = ? WHERE participants.id = ?;");
    regQuery(QueryKey(Playoff::Table::kParticipants, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM participants WHERE participants.id = ?;");
    regQuery(QueryKey(Playoff::Table::kParticipants, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM participants ORDER BY participants.name ASC;");

    // participants
    regQuery(QueryKey(Playoff::Table::kTournament, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO tournament (name, place, tdate, referre, secretary) VALUES (?, ?, ?, ?, ?);");
    regQuery(QueryKey(Playoff::Table::kTournament, Playoff::Query::kInsert, Playoff::Selector::kDefault),"UPDATE tournament SET name = ?, place = ?, tdate = ?, referre = ?, secretary = ? WHERE tournament.id = ?;");
    regQuery(QueryKey(Playoff::Table::kTournament, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM tournament WHERE tournament.id = ?;");
    regQuery(QueryKey(Playoff::Table::kTournament, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM tournament ORDER BY tournament.tdate DESC;");

    // competition
    regQuery(QueryKey(Playoff::Table::kCompetition, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO competition (gender, age, level, category_id, tournament_id) VALUES (?, ?, ?, ?, ?);");
    regQuery(QueryKey(Playoff::Table::kCompetition, Playoff::Query::kInsert, Playoff::Selector::kDefault),"UPDATE competition SET gender = ?, age = ?, level = ?, category_id = ?, tournament_id = ? WHERE competition.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCompetition, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM competition WHERE competition.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCompetition, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM competition ORDER BY competition.tournament_id ASC;");

    // competition_participants
    regQuery(QueryKey(Playoff::Table::kCompetitionParticipants, Playoff::Query::kInsert, Playoff::Selector::kDefault),"INSERT INTO competition_participants (pos, competition_id, participants_id) VALUES (?, ?, ?);");
    regQuery(QueryKey(Playoff::Table::kCompetitionParticipants, Playoff::Query::kInsert, Playoff::Selector::kDefault),"UPDATE competition_participants SET pos = ?, competition_id = ?, participants_id = ? WHERE competition_participants.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCompetitionParticipants, Playoff::Query::kDelete, Playoff::Selector::kDefault), "DELETE FROM competition_participants WHERE competition_participants.id = ?;");
    regQuery(QueryKey(Playoff::Table::kCompetitionParticipants, Playoff::Query::kSelect, Playoff::Selector::kAll), "SELECT * FROM competition_participants ORDER BY competition.tournament_id ASC;");
}

bool DatabaseWorker::makeQuery(QSqlQuery *db_query, const QueryKey &key, const QVariantMap &card, const QVariantMap &filter)
{
    QString str_query;
    getQuqery(&str_query, key);
    db_query->prepare(str_query);

    binding(db_query, key, card, filter);

    bool r = db_query->exec();
    if (!r) {
        qDebug() << "DB ERR: " << db_query->lastError().text();
        qDebug() << "DB QUERY: " << db_query->lastQuery();
    }
    return r;

}

void DatabaseWorker::regQuery(const QueryKey &key, const QString &str)
{
    m_register.insert(key, str);
}

void DatabaseWorker::getQuqery(QString *str, const QueryKey &key)
{
    str->append(m_register.value(key));
}

void DatabaseWorker::binding(QSqlQuery *db_query, const QueryKey &key, const QVariantMap &card, const QVariantMap &filter)
{
    if (key.table == Playoff::Table::kClub) {
        if (key.query == Playoff::Query::kInsert || key.query == Playoff::Query::kUpdate) {
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("place"));
        }
        if (key.query == Playoff::Query::kUpdate) {
            db_query->bindValue(0, card.value("id"));
        }
        if (key.query == Playoff::Query::kDelete) {
            db_query->bindValue(0, card.value("id"));
        }
    }
    if (key.table == Playoff::Table::kCategory) {
        switch (key.query) {
        case Playoff::Query::kInsert:
            db_query->bindValue(0, card.value("name"));
            break;
        case Playoff::Query::kUpdate:
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("id"));
            break;
        case Playoff::Query::kDelete:
            db_query->bindValue(0, card.value("id"));
            break;
        case Playoff::Query::kSelect:
            break;
        }
    }
    if (key.table == Playoff::Table::kParticipants) {
        switch (key.query) {
        case Playoff::Query::kInsert:
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("club_id"));
            db_query->bindValue(2, card.value("level"));
            db_query->bindValue(3, card.value("born"));
            break;

        case Playoff::Query::kUpdate:
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("club_id"));
            db_query->bindValue(2, card.value("level"));
            db_query->bindValue(3, card.value("born"));
            db_query->bindValue(4, card.value("id"));
            break;
        case Playoff::Query::kDelete:
            db_query->bindValue(0, card.value("id"));
            break;
        case Playoff::Query::kSelect:
            break;
        }
    }
    if (key.table == Playoff::Table::kTournament) {
        switch (key.query) {
        case Playoff::Query::kInsert:
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("place"));
            db_query->bindValue(2, card.value("tdate"));
            db_query->bindValue(3, card.value("referre"));
            db_query->bindValue(4, card.value("secretary"));
            break;

        case Playoff::Query::kUpdate:
            db_query->bindValue(0, card.value("name"));
            db_query->bindValue(1, card.value("place"));
            db_query->bindValue(2, card.value("tdate"));
            db_query->bindValue(3, card.value("referre"));
            db_query->bindValue(4, card.value("secretary"));
            db_query->bindValue(5, card.value("id"));
            break;
        case Playoff::Query::kDelete:
            db_query->bindValue(0, card.value("id"));
            break;
        case Playoff::Query::kSelect:
            break;
        }
    }
    if (key.table == Playoff::Table::kCompetition) {
        switch (key.query) {
        case Playoff::Query::kInsert:
            db_query->bindValue(0, card.value("gender"));
            db_query->bindValue(1, card.value("age"));
            db_query->bindValue(2, card.value("level"));
            db_query->bindValue(3, card.value("category_id"));
            db_query->bindValue(4, card.value("tournament_id"));
            break;

        case Playoff::Query::kUpdate:
            db_query->bindValue(0, card.value("gender"));
            db_query->bindValue(1, card.value("age"));
            db_query->bindValue(2, card.value("level"));
            db_query->bindValue(3, card.value("category_id"));
            db_query->bindValue(4, card.value("tournament_id"));
            db_query->bindValue(5, card.value("id"));
            break;
        case Playoff::Query::kDelete:
            db_query->bindValue(0, card.value("id"));
            break;
        case Playoff::Query::kSelect:
            break;
        }
    }
    if (key.table == Playoff::Table::kCompetitionParticipants) {
        switch (key.query) {
        case Playoff::Query::kInsert:
            db_query->bindValue(0, card.value("pos"));
            db_query->bindValue(1, card.value("competition_id"));
            db_query->bindValue(2, card.value("participant_id"));
            break;

        case Playoff::Query::kUpdate:
            db_query->bindValue(0, card.value("pos"));
            db_query->bindValue(1, card.value("competition_id"));
            db_query->bindValue(2, card.value("participant_id"));
            db_query->bindValue(5, card.value("id"));
            break;
        case Playoff::Query::kDelete:
            db_query->bindValue(0, card.value("id"));
            break;
        case Playoff::Query::kSelect:
            break;
        }
    }

}

