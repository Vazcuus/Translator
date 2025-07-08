#ifndef YANDEXTRANSLATOR_H
#define YANDEXTRANSLATOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "databasemanager.h"
class YandexTranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString translatedText READ translatedText NOTIFY translationFinished)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorOccurred)

public:
    explicit YandexTranslator(QObject *parent = nullptr);
    ~YandexTranslator();

    QString translatedText() const { return m_translatedText; }
    QString errorMessage() const { return m_errorMessage; }

    Q_INVOKABLE void translate(const QString &text, const QString &targetLanguage, const QString &folderId, const QString &apiKey);

signals:
    void translationFinished(const QString &result);
    void errorOccurred(const QString &errorMessage);

private slots:
    void onTranslationFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *m_networkManager;
    QString m_translatedText;
    QString m_currentText;
    QString m_currentTargetLang;
    QString m_errorMessage;
    DatabaseManager *m_dbManager;
};

#endif // YANDEXTRANSLATOR_H
