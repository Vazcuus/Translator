#include <auroraapp.h>
#include <QtQuick>
#include "curl/curl.h"
#include "yandextranslator.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    qmlRegisterType<YandexTranslator>("YandexTranslator", 1, 0, "YandexTranslator");
    application->setOrganizationName(QStringLiteral("ru.template"));
    application->setApplicationName(QStringLiteral("test2"));

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/test2.qml")));
    view->show();

    return application->exec();
}
