#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QDir>
#include <QSqlError>
#include <QSqlRecord>
class DatabaseManager : public QObject {
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    Q_INVOKABLE void init(const QString &databasePath = "translations.db");  // SQLite использует файл вместо сервера
    Q_INVOKABLE QString getTranslation(const QString &text, const QString &targetLanguage);
    Q_INVOKABLE bool saveTranslation(const QString &text, const QString &translatedText, const QString &targetLanguage);
    Q_INVOKABLE void bd_output();
    bool openDatabase();

    QString translatedText() const { return mget; }
private:
    QSqlDatabase m_db;
    QString mget;
    bool createTables();
};

#endif // DATABASEMANAGER_H
