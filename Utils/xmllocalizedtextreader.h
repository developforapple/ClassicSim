#ifndef XMLLOCALIZEDTEXTREADER_H
#define XMLLOCALIZEDTEXTREADER_H

#include <QObject>
#include <QXmlStreamReader>

QString localized_attribute_name(QString attribute_name, QString lang);
QString read_localized_element_text(QXmlStreamReader& reader, QString lang);
QString read_localized_attribute_text(QXmlStreamReader& reader, QString attribute_name, QString lang);

#endif // XMLLOCALIZEDTEXTREADER_H
