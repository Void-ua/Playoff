#pragma once

#include <QObject>
#include <QHash>
#include <QList>
#include <typeinfo>

#include "datas.h"

template<typename DataType>
class Container {
public:

    Container() = default;
    ~Container() = default;

    int count() const { return m_data.size(); }
    int pos(int id) const { return m_index.value(id, -1); }

    const DataType* item(int position) const {
        if (position >= 0 && position < m_data.size()) {
            return &m_data.at(position);
        }
        return nullptr;
    }

    DataType* item(int position) {
        if (position >= 0 && position < m_data.size()) {
            return &m_data[position];
        }
        return nullptr;
    }

    const DataType* itemById(int id) const {
        int position = pos(id);
        return item(position);
    }

    DataType* itemById(int id) {
        int position = pos(id);
        return item(position);
    }

    int add(const DataType& item) {
        int position = m_data.size();
        m_data.append(item);
        m_index.insert(item.id, position);
        return position;
    }

    int update(const DataType& item) {
        int position = pos(item.id);
        if (position >= 0) m_data[position] = item;
        return position;
    }

    bool remove(int id) {
        int position = pos(id);
        if (position < 0) return false;
        m_data.removeAt(position);
        m_index.remove(id);
        rebuildIndex(position);
        return true;
    }

    void clear(){
        m_data.clear();
        m_index.clear();
    }

    const QList<DataType>& data() const { return m_data; }



private:
    QList<DataType> m_data;
    QHash<int, int> m_index;

    void rebuildIndex(int startPos) {
        for (int i = startPos; i < m_data.size(); i++) {
            m_index[m_data[i].id] = i;
        }
    }
};

class Resources : public QObject
{
    Q_OBJECT

public:


    explicit Resources(QObject *parent = nullptr): QObject(parent){
        registerContainer<Tournament>(&c_tournament);
        registerContainer<Club>(&c_club);
        registerContainer<Sensei>(&c_sensei);

    };

    template<typename DataType>
    Container<DataType>* container() {
        size_t typeId = typeid(DataType).hash_code();
        auto it = m_containers.find(typeId);
        if (it != m_containers.end()) {
            return static_cast<Container<DataType>*>(it.value());
        }
        return nullptr;
    };

    template<typename DataType>
    void emitChanged() {
        size_t typeId = typeid(DataType).hash_code();
        emit dataChanged(typeId);
    }

signals:
    void dataChanged(size_t typeId);

    void currentUserChanged();
    void currentRoleChanged();

private:
    QHash<size_t, void*> m_containers;
    Container<Tournament> c_tournament;
    Container<Club> c_club;
    Container<Sensei> c_sensei;



    template<typename DataType>
    void registerContainer(Container<DataType>* container) {
        size_t typeId = typeid(DataType).hash_code();
        m_containers[typeId] = container;
    }

};