#pragma once

#include <QObject>

#include "../db/databaseworker.h"
#include "../utils/resource.h"
#include "../utils/mapper.h"

class FormTournament : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int idx READ idx WRITE setIdx NOTIFY idxChanged FINAL);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL);
    Q_PROPERTY(QString place READ place WRITE setPlace NOTIFY placeChanged FINAL);
    Q_PROPERTY(QDate tdade READ tdade WRITE setTdade NOTIFY tdadeChanged FINAL);
    Q_PROPERTY(QString referre READ referre WRITE setReferre NOTIFY referreChanged FINAL);
    Q_PROPERTY(QString secretary READ secretary WRITE setSecretary NOTIFY secretaryChanged FINAL);

    Q_PROPERTY(QDateTime created READ created CONSTANT);

    Q_PROPERTY(bool saveValid READ saveValid WRITE setSaveValid NOTIFY saveValidChanged FINAL);
    Q_PROPERTY(bool delValid READ delValid WRITE setDelValid NOTIFY delValidChanged FINAL);


public:
    explicit FormTournament(DatabaseWorker *dw, Resources *rs, QObject *parent = nullptr);

    Q_INVOKABLE void load(int id);
    Q_INVOKABLE bool post();
    Q_INVOKABLE bool reset();

    int idx() const;
    void setIdx(int newIdx);

    QString name() const;
    void setName(const QString &newName);

    QString place() const;
    void setPlace(const QString &newPlace);

    QDate tdade() const;
    void setTdade(const QDate &newTdade);

    QString referre() const;
    void setReferre(const QString &newReferre);

    QString secretary() const;
    void setSecretary(const QString &newSecretary);

    QDateTime created() const;

    bool saveValid() const;
    void setSaveValid(bool newSaveValid);

    bool delValid() const;
    void setDelValid(bool newDelValid);

    void validate();

signals:
    void idxChanged();
    void nameChanged();
    void placeChanged();
    void tdadeChanged();
    void referreChanged();
    void secretaryChanged();
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
    QString m_place;
    QDate m_tdade;
    QString m_referre;
    QString m_secretary;
    QDateTime m_created;
    bool m_saveValid;
    bool m_delValid;
};
