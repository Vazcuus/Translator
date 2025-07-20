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
}
QString YandexTranslator::detectLanguage(const QString &text, const QString &apiKey, const QString &folderId)
{
    QNetworkAccessManager manager;

        // 2. Формируем URL и JSON-тело запроса
        QUrl url("https://translate.api.cloud.yandex.net/translate/v2/detect");
        QJsonObject json_body;
        json_body["folderId"] = folderId;
        json_body["text"] = text;

        // 3. Настраиваем HTTP-запрос
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
        request.setRawHeader("Authorization", ("Api-Key " + apiKey).toUtf8());

        // 4. Отправляем POST-запрос и ждём ответа (ПЛОХАЯ РЕАЛИЗАЦИЯ, лучше асинхронно, однако пока так оставлю, с кэллбэком не разобрался пока что, можно еще попробовать через сигналы оформить, thinking)
        QNetworkReply *reply = manager.post(request, QJsonDocument(json_body).toJson());
        QEventLoop loop;
        QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
        loop.exec();

        // 6. Парсим JSON и извлекаем languageCode
        QJsonDocument response = QJsonDocument::fromJson(reply->readAll());
        QJsonObject root = response.object();
        QString detected_lang = root["languageCode"].toString();
        qDebug() << "Перевод с: " << detected_lang;
        reply->deleteLater();
        return detected_lang;
}

void YandexTranslator::translate(const QString &text, const QString &folderId, const QString &apiKey)
{
    m_currentText = text;

    QUrl url("https://translate.api.cloud.yandex.net/translate/v2/translate");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Api-Key %1").arg(apiKey).toUtf8());

    QJsonObject requestBody;
    requestBody["folderId"] = folderId;
    requestBody["texts"] = QJsonArray{text};
    if (detectLanguage(text, apiKey, folderId) == "zh")
    {
        m_currentTargetLang = "ru";
        requestBody["targetLanguageCode"] = "ru";
    }
    else
    {
        requestBody["targetLanguageCode"] = "zh";
        m_currentTargetLang = "zh";
    }

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
