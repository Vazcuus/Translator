TARGET = ru.template.test2

CONFIG += auroraapp

# Пути к заголовкам


# Библиотеки

QT += sql core

SOURCES += src/main.cpp \
    src/databasemanager.cpp \
    src/yandextranslator.cpp

HEADERS += \
    src/databasemanager.h \
    src/yandextranslator.h

DISTFILES += rpm/ru.template.test2.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.test2.ts \
    translations/ru.template.test2-ru.ts
