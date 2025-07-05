TARGET = ru.template.test2

CONFIG += auroraapp

# Пути к заголовкам


# Библиотеки



SOURCES += src/main.cpp \
    src/yandextranslator.cpp

HEADERS += \
    src/yandextranslator.h

DISTFILES += rpm/ru.template.test2.spec \
    qml/anotherpage.qml

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.test2.ts \
    translations/ru.template.test2-ru.ts
