/*
 *
 *
 */

#pragma once

#include <QObject>
#include <QHash>

namespace Playoff {

Q_NAMESPACE

enum class Query {
    kSelect,
    kInsert,
    kUpdate,
    kDelete
};
Q_ENUM_NS(Query);

enum class Table {
    kClub,
    kCategory,
    kCompetition,
    kParticipants,
    kTournament,
    kCompetitionParticipants
};
Q_ENUM_NS(Table);


enum class Selector {
    kDefault,
    kAll,
    kID
};
Q_ENUM_NS(Selector);
}


struct QueryKey {
    Playoff::Table table;
    Playoff::Query query;
    Playoff::Selector selector;

    QueryKey() = default;
    QueryKey(const Playoff::Table &table_, const Playoff::Query &query_, const Playoff::Selector &selector_)
        : table(table_), query(query_), selector(selector_) {};

    bool operator == (const QueryKey &b) const noexcept {
        return table == b.table && query == b.query && selector == b.selector;
    }
};

inline size_t qHash(const QueryKey &key, int seed = 0) {
    return qHashMulti(seed, static_cast<int>(key.table), static_cast<int>(key.query), static_cast<int>(key.selector));
}
