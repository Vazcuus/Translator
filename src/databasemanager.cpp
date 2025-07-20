#include "databasemanager.h"
#include <QDebug>
#include <QStandardPaths>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

void DatabaseManager::init(const QString &databasePath) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");  // Используем SQLite вместо QPSQL
    QString path = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QDir().mkpath(path); // Создаём директорию, если её нет
    m_db.setDatabaseName(path + "/" + databasePath);
    qDebug() << "Database path:" << m_db.databaseName(); // Для отладки в консоль
    m_db.setConnectOptions("QSQLITE_OPEN_READWRITE | QSQLITE_OPEN_CREATE");


    if (!m_db.open())
    {
        qDebug() << "SQLite error:" << m_db.lastError().text();
        return;
    }
    else
    {
        qDebug() << "Connection YES!!!";
    }

   createTables();
}

bool DatabaseManager::createTables()
{
    if (!m_db.open()) {
        qDebug() << "SQLite error:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;

    bool success = query.exec(
                "CREATE TABLE IF NOT EXISTS translations ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                "source_text TEXT NOT NULL,"
                "translated_text TEXT NOT NULL,"
                "target_language TEXT NOT NULL,"
                "UNIQUE(source_text, target_language)"
                ");"
            );
     if (success)
     {
         m_db.commit();
     }
     else
     {
         m_db.rollback();
     }
      return success;

}

QString DatabaseManager::getTranslation(const QString &text, const QString &targetLanguage) {
    QSqlQuery query;
    QString result;
    query.prepare("SELECT translated_text FROM translations WHERE source_text = ? AND target_language = ?;");
    query.addBindValue(text.trimmed().toLower());
    query.addBindValue(targetLanguage.trimmed().toLower());

    if (query.exec() && query.next())
    {
        result = query.value(0).toString();
        return result;
    }
    return NULL;
}

bool DatabaseManager::saveTranslation(const QString &text, const QString &translatedText, const QString &targetLanguage) {
    QSqlQuery query;
    query.prepare(
        "INSERT OR REPLACE INTO translations (source_text, translated_text, target_language) "
        "VALUES (?, ?, ?);"
    );
    query.addBindValue(text.trimmed().toLower());
    query.addBindValue(translatedText.trimmed().toLower());
    query.addBindValue(targetLanguage);

    bool success = query.exec();
    if (success)
    {
        m_db.commit();
    } else
    {
       m_db.rollback();
    }
    return success;
}



void DatabaseManager::bd_output()
{
    if (!m_db.isOpen())
    {
            qDebug() << "Database is not open!";
            return;
        }

        QSqlQuery query;
        query.exec("SELECT id, source_text, translated_text FROM translations");

        while (query.next())
        {
            int id = query.value(0).toInt();
            QString source = query.value(1).toString();
            QString translated = query.value(2).toString();
            qDebug() << id << " " << source << " " << translated;
        }
}
