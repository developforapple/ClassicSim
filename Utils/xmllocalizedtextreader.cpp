#include "xmllocalizedtextreader.h"
#include <qdebug.h>

QString localized_attribute_name(QString attribute_name, QString lang)
{
    if (lang == "en") {
        return attribute_name;
    }
    return attribute_name + "_" + lang;
}

QString read_localized_element_text(QXmlStreamReader& reader, QString lang)
{
    QString defaultText = "";
    QString localizedText = nullptr;
    while (reader.readNextStartElement()) {
        if (reader.name() == "en" || reader.name() == lang) {
            QString text = reader.readElementText().simplified();
            if (text != nullptr && text.length()) {
                if (reader.name() == "en") {
                    defaultText = text;
                } else if (reader.name() == lang) {
                    localizedText = text;
                }
            }
        }
    }
    if (localizedText == nullptr || localizedText.length() == 0) {
        qDebug() << QString("localized element text not found, Line: %1,Column: %2").arg(reader.lineNumber()).arg(reader.columnNumber());
        localizedText = defaultText;
    }
    return  localizedText;
}

QString read_localized_attribute_text(QXmlStreamReader& reader, QString attribute_name, QString lang)
{
    QString defaultText = "";
    QString localizedText = nullptr;

    if (reader.attributes().hasAttribute(attribute_name)) {
        defaultText = reader.attributes().value(attribute_name).toString();
    }

    if (lang != "en") {
        QString localized_name = localized_attribute_name(attribute_name, lang);
        if (reader.attributes().hasAttribute(localized_name)) {
            localizedText = reader.attributes().value(localized_name).toString();
        } else {
            qDebug() << QString("localized attribute text not found, line: %1, column: %2").arg(reader.lineNumber()).arg(reader.columnNumber());
        }
    }

    if (localizedText == nullptr || localizedText.length() == 0) {
        localizedText = defaultText;
    }
    return localizedText;
}
