#include "yandextranslator.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QJsonArray>

YandexTranslator::YandexTranslator(QObject *parent) : QObject(parent), m_networkManager(new QNetworkAccessManager(this))
{
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &YandexTranslator::onTranslationFinished);
}

YandexTranslator::~YandexTranslator()
{
    delete m_networkManager;
    delete m_dbManager;
}

void YandexTranslator::translate(const QString &text, const QString &targetLanguage, const QString &folderId, const QString &apiKey)
{
    m_currentText = text;
    m_currentTargetLang = targetLanguage;

    QUrl url("https://translate.api.cloud.yandex.net/translate/v2/translate");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Api-Key %1").arg(apiKey).toUtf8());

    QJsonObject requestBody;
    requestBody["folderId"] = folderId;
    requestBody["texts"] = QJsonArray{text};
    requestBody["targetLanguageCode"] = targetLanguage;

    QJsonDocument doc(requestBody);
    m_networkManager->post(request, doc.toJson());
}

void YandexTranslator::onTranslationFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        m_errorMessage = reply->errorString();
        emit errorOccurred(m_errorMessage);
        reply->deleteLater();
        return;
    }

    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObject = jsonResponse.object();

    if (jsonObject.contains("translations")) {
        QJsonArray translations = jsonObject["translations"].toArray();
        if (!translations.isEmpty())
        {
            m_translatedText = translations[0].toObject()["text"].toString();
            emit translationFinished(m_translatedText);
        }
    } else {
        m_errorMessage = "Invalid API response";
        emit errorOccurred(m_errorMessage);
    }

    reply->deleteLater();
}
