import QtQuick 2.0
import Sailfish.Silica 1.0
import YandexTranslator 1.0
import DatabaseManager 1.0


Page {
    id: page
    property string userText: ""

    DatabaseManager
    {
        id: db
        Component.onCompleted: db.init("translations.db")
    }

    YandexTranslator
    {
        id: translator
        onTranslationFinished:
        {
            outputField.text = translator.translatedText
            db.saveTranslation(inputField.text, translator.translatedText, "zh")
            db.bd_output();
        }
    }

    Timer {
            id: translateTimer
            interval: 800
            onTriggered:
            {
                const result = db.getTranslation(inputField.text, "zh");
                console.log("TranslationFromDatabase: " + result)
                if (result)
                {
                    outputField.text = result;
                }
                else
                {
                    translator.translate(inputField.text, "b1gd81gnqcd39fkdftq0", "AQVNzslKURu19r77Ma6rD4G2vL9T6szGQgN4t1Uu")
                    console.log("Перевод текста: " + inputField.text)
                }
            }
        }


    // Заголовок страницы
    PageHeader {
        id: header
        title: qsTr("Переводчик")
        titleColor: Theme.primaryColor
        rightMargin: parent.width
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
            placeholderColor: Theme.highlightColor
            label: qsTr("Исходный текст")
            color: Theme.primaryColor
            textMargin: Theme.paddingMedium
            wrapMode: Text.Wrap
            font.pixelSize: Theme.fontSizeMedium
            text: userText
            onTextChanged:
            {
                if (activeFocus)
                {
                    translateTimer.restart()
                }
            }

            background: Rectangle {
                anchors.fill: parent
                color: Theme.primaryColor
                opacity: Theme.opacityLow
                radius: Theme.paddingMedium
            }
        }

//        // Кнопка перевода пока оставлю мало ли
//        Button {
//            id: translateButton
//            anchors.horizontalCenter: parent.horizontalCenter
//            text: qsTr("Перевести")
//            onClicked:
//            {
//                const result = db.getTranslation(inputField.text, "zh");
//                console.log("TranslationFromDatabase: " + result)
//                if (result)
//                {  // Если метод возвращает строку
//                    outputField.text = result;
//                }
//                else
//                {
//                    translator.translate(inputField.text, "zh", "b1gd81gnqcd39fkdftq0", "AQVNzslKURu19r77Ma6rD4G2vL9T6szGQgN4t1Uu")
//                    console.log("Перевод текста: " + inputField.text)
//                }
//            }
//        }

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

            background: Rectangle
            {
                color: Theme.rgba(Theme.highlightBackgroundColor, 0.05)
                radius: Theme.paddingSmall
            }
        }
    }
}
