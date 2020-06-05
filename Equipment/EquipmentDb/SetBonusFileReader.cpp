#include "SetBonusFileReader.h"

#include <QDebug>
#include <QDir>
#include <Utils/Check.h>
#include "ItemStatsEnum.h"

void SetBonusFileReader::read_set_bonuses(const QString& path,
                                          QMap<int, QString>& possible_set_items,
                                          QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips,
                                          QMap<QString, QMap<int, QPair<ItemStats, unsigned>>>& set_bonus_effects) {
    QFile file(path);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Cannot read file" << path << ":" << file.errorString();
        return;
    }

    QXmlStreamReader reader(&file);

    if (reader.readNextStartElement()) {
        if (reader.name() == "sets")
            set_bonus_file_handler(reader, possible_set_items, set_bonus_tooltips, set_bonus_effects);
        else
            qDebug() << "Did not find initial <sets> element in" << path;
    }

    file.close();
}

void SetBonusFileReader::set_bonus_file_handler(QXmlStreamReader& reader,
                                                QMap<int, QString>& possible_set_items,
                                                QMap<QString, QVector<QPair<int, QString>>>& set_bonus_tooltips,
                                                QMap<QString, QMap<int, QPair<ItemStats, unsigned>>>& set_bonus_effects) {
    QString lang = "zh";

    while (reader.readNextStartElement()) {
        if (!reader.attributes().hasAttribute("name")) {
            qDebug() << "Missing name attribute for <set> element";
            for (const auto& attr : reader.attributes())
                qDebug() << attr.name() << attr.value();
            reader.skipCurrentElement();
            continue;
        }

        QString set_name = nullptr;
        if (lang != "en") {
            set_name = reader.attributes().value("name_" + lang).toString();
        }
        if (set_name == nullptr || set_name.length() == 0) {
            set_name = reader.attributes().value("name").toString();
        }

        while (reader.readNextStartElement()) {
            if (reader.name() == "item_id") {
                if (!reader.attributes().hasAttribute("value")) {
                    qDebug() << QString("Missing 'value' attribute for <item_id> element in <set> '%1'").arg(set_name);
                    reader.skipCurrentElement();
                    continue;
                }
                int item_id = reader.attributes().value("value").toInt();

                if (possible_set_items.contains(item_id)) {
                    qDebug() << "item_id" << item_id << "part of two sets:" << possible_set_items[item_id] << "and" << set_name;
                    reader.skipCurrentElement();
                    continue;
                }

                possible_set_items[item_id] = set_name;
                reader.skipCurrentElement();
            } else if (reader.name() == "bonus") {
                if (!reader.attributes().hasAttribute("value")) {
                    qDebug() << QString("Missing 'value' attribute for <bonus> element in <set> '%1'").arg(set_name);
                    reader.skipCurrentElement();
                    continue;
                }

                const int num_items = reader.attributes().value("value").toInt();

                if (reader.attributes().hasAttribute("item_stat") && reader.attributes().hasAttribute("stat_value")) {
                    const ItemStats item_stats = get_item_stats_from_string(reader.attributes().value("item_stat").toString());
                    const unsigned stat_value = reader.attributes().value("stat_value").toUInt();
                    set_bonus_effects[set_name][num_items] = {item_stats, stat_value};
                }

                if (!set_bonus_tooltips.contains(set_name))
                    set_bonus_tooltips[set_name] = {};

                QString tooltip = read_bonus_tooltip(reader, set_name, lang);
                set_bonus_tooltips[set_name].append({num_items, tooltip});
            } else
                reader.skipCurrentElement();
        }
    }
}

QString SetBonusFileReader::read_bonus_tooltip(QXmlStreamReader& reader, QString set_name, QString lang){
    QString defaultTooltip = nullptr;
    QString localizedTooltip = nullptr;
    while (reader.readNextStartElement()) {
        if (reader.name() == "en" || reader.name() == lang) {
            QString tooltip = reader.readElementText().simplified();
            if (tooltip != nullptr && tooltip.length()) {
                if (reader.name() == "en") {
                    defaultTooltip = tooltip;
                } else if (reader.name() == lang) {
                    localizedTooltip = tooltip;
                }
            }
        }
    }
    if (localizedTooltip == nullptr || localizedTooltip.length() == 0) {
        qDebug() << QString("set_bonuses.xml localized bonus tooltip not found. Name: %1. Language: %2").arg(set_name).arg(lang);
        localizedTooltip = defaultTooltip;
    }
    return localizedTooltip;
}
