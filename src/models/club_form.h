#pragma once

#include <QObject>

#include "../db/databaseworker.h"
#include "../utils/resource.h"
#include "../utils/mapper.h"

class FormClub : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int idx READ idx WRITE setIdx NOTIFY idxChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(QString location READ location WRITE setLocation NOTIFY locationChanged FINAL);

    Q_PROPERTY(bool saveValid READ saveValid WRITE setSaveValid NOTIFY saveValidChanged FINAL);
    Q_PROPERTY(bool delValid READ delValid WRITE setDelValid NOTIFY delValidChanged FINAL);


public:
    explicit FormClub(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);

    Q_INVOKABLE void load(int id);
    Q_INVOKABLE bool post();
    Q_INVOKABLE bool reset();


    void validate();

    int idx() const;
    void setIdx(int newIdx);

    QString name() const;
    void setName(const QString &newName);

    QString location() const;
    void setLocation(const QString &newLocation);

    bool saveValid() const;
    void setSaveValid(bool newSaveValid);

    bool delValid() const;
    void setDelValid(bool newDelValid);

signals:

    void idxChanged();
    void nameChanged();
    void locationChanged();
    void saveValidChanged();
    void delValidChanged();

    void itemAdded();
    void itemUpdated(int index);
    void itemInactivated(int index);

private:
    DatabaseWorker *m_dw;
    Resources *m_resource;

    int m_idx;
    QString m_name;
    QString m_location;
    bool m_saveValid;
    bool m_delValid;
};
