#include "ContentPhase.h"
#include <QObject>
#include "Utils/Check.h"

QString Content::get_description_for_phase(const Content::Phase phase) {
    switch (phase) {
    case Content::Phase::MoltenCore:
        return QObject::tr("(1) Molten Core, Onyxia, Maraudon");
    case Content::Phase::DireMaul:
        return QObject::tr("(2) Dire Maul, Azuregos, Kazzak, Honor rewards");
    case Content::Phase::BlackwingLair:
        return QObject::tr("(3) Blackwing Lair, Darkmoon Faire, AV/WSG");
    case Content::Phase::ZulGurub:
        return QObject::tr("(4) Zul'Gurub, Green Dragons, Arathi Basin");
    case Content::Phase::AhnQiraj:
        return QObject::tr("(5) Ahn'Qiraj, improved dungeon loot");
    case Content::Phase::Naxxramas:
        return QObject::tr("(6) Naxxramas");
    }

    return "<missing phase>";
}

QString Content::get_shortname_for_phase(const Content::Phase phase) {
    switch (phase) {
    case Content::Phase::MoltenCore:
        return QObject::tr("(1) MC/Ony");
    case Content::Phase::DireMaul:
        return QObject::tr("(2) DM");
    case Content::Phase::BlackwingLair:
        return QObject::tr("(3) BWL");
    case Content::Phase::ZulGurub:
        return QObject::tr("(4) ZG/AB");
    case Content::Phase::AhnQiraj:
        return QObject::tr("(5) AQ");
    case Content::Phase::Naxxramas:
        return QObject::tr("(6) Naxx");
    }

    return "<missing phase>";
}

Content::Phase Content::get_phase(const int phase) {
    check((phase >= static_cast<int>(Content::Phase::MoltenCore) && phase <= static_cast<int>(Content::Phase::Naxxramas)),
          QString("Phase %1 out of enum range").arg(phase).toStdString());

    return static_cast<Content::Phase>(phase);
}
