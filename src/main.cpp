#include <auroraapp.h>
#include <QtQuick>
#include "yandextranslator.h"
#include "databasemanager.h"

int main(int argc, char *argv[])
{

    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));


    application->setOrganizationName(QStringLiteral("ru.template"));
    application->setApplicationName(QStringLiteral("test2"));

    qmlRegisterType<YandexTranslator>("YandexTranslator", 1, 0, "YandexTranslator");
    qmlRegisterType<DatabaseManager>("DatabaseManager", 1, 0, "DatabaseManager");

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/test2.qml")));
    view->show();

    return application->exec();
}
