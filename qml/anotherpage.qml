import QtQuick 2.0
import Sailfish.Silica 1.0
import YandexTranslator 1.0
import DatabaseManager 1.0

Page {
    id: page

    DatabaseManager
    {
        id: db

    }

    YandexTranslator
    {
        id: translator
        onTranslationFinished:
        {
            outputField.text = translatedText
        }
    }

    // Фон страницы
    Rectangle {
        anchors.fill: parent
        color: Theme.colorScheme === Theme.LightOnDark ? "#000000" : "#ffffff"
    }

    // Заголовок страницы
    PageHeader {
        id: header
        title: qsTr("Переводчик")
    }

    // Основное содержимое
    Column {
        anchors {
            top: header.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: Theme.paddingLarge
        }
        spacing: Theme.paddingLarge

        // Поле ввода текста для перевода
        TextArea {
            id: inputField
            width: parent.width
            height: Math.max(implicitHeight, page.height / 3)
            placeholderText: qsTr("Введите текст для перевода...")
            label: qsTr("Исходный текст")
            color: Theme.primaryColor
            textMargin: Theme.paddingMedium
            wrapMode: Text.Wrap
            font.pixelSize: Theme.fontSizeMedium

            background: Rectangle {
                color: Theme.rgba(Theme.highlightBackgroundColor, 0.1)
                radius: Theme.paddingSmall
            }
        }

        // Кнопка перевода
        Button {
            id: translateButton
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Перевести")
            onClicked:
            {
                db.init("translations.db")
                translator.translate(inputField.text, "zh", "b1gd81gnqcd39fkdftq0", "AQVNzslKURu19r77Ma6rD4G2vL9T6szGQgN4t1Uu")
                db.saveTranslation(inputField.text, translator.translatedText, "zh")
                db.test();
                console.log("Перевод текста: " + inputField.text)
            }
        }

        // Разделитель
        Separator {
            width: parent.width
            color: Theme.secondaryColor
            horizontalAlignment: Qt.AlignHCenter
        }

        // Поле результата перевода
        TextArea {
            id: outputField
            width: parent.width
            height: Math.max(implicitHeight, page.height / 3)
            placeholderText: qsTr("Результат перевода...")
            label: qsTr("Перевод")
            readOnly: true
            color: Theme.primaryColor
            textMargin: Theme.paddingMedium
            wrapMode: Text.Wrap
            font.pixelSize: Theme.fontSizeMedium

            background: Rectangle {
                color: Theme.rgba(Theme.highlightBackgroundColor, 0.05)
                radius: Theme.paddingSmall
            }
        }
    }
}
