TARGET = ru.template.test2

CONFIG += auroraapp

# Пути к заголовкам
INCLUDEPATH += "../curl/include"
DEPENDPATH += "../curl/include"

# Библиотеки
LIBS += -L"../curl/lib" -lcurl

CONFIG(release, debug|release): LIBS += -lcurl


SOURCES += src/main.cpp

HEADERS +=

DISTFILES += rpm/ru.template.test2.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.test2.ts \
    translations/ru.template.test2-ru.ts
