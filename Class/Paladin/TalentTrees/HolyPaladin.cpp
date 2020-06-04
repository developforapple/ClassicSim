#include "HolyPaladin.h"
#include <QObject>
#include "Consecration.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "TalentStatIncrease.h"

HolyPaladin::HolyPaladin(Paladin* paladin) :
    TalentTree(QObject::tr("Holy"), "Assets/paladin/paladin_holy.jpg"), paladin(paladin), spells(static_cast<PaladinSpells*>(paladin->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Divine Strength"), "1ML"},
        {QObject::tr("Divine Intellect"), "1MR"},
        {QObject::tr("Spiritual Focus"), "2ML"},
        {QObject::tr("Improved Seal of Righteousness"), "2MR"},
        {QObject::tr("Healing Light"), "3LL"},
        {QObject::tr("Consecration"), "3ML"},
        {QObject::tr("Improved Lay on Hands"), "3MR"},
        {QObject::tr("Unyielding Faith"), "3RR"},
        {QObject::tr("Illumination"), "4ML"},
        {QObject::tr("Improved Blessing of Wisdom"), "4MR"},
        {QObject::tr("Divine Favor"), "5ML"},
        {QObject::tr("Lasting Judgement"), "5MR"},
        {QObject::tr("Holy Power"), "6MR"},
        {QObject::tr("Holy Shock"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {};
    add_divine_strength(tier1);
    add_divine_intellect(tier1);
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2ML", new Talent(paladin, this, QObject::tr("Spiritual Focus"), "2ML", "Assets/spell/Spell_arcane_blink.png", 5,
                                  QObject::tr("Gives your Flash of Light and Holy Light spells a %1% chance to not lose casting time when you take damage."),
                                  QVector<QPair<unsigned, unsigned>> {{14, 14}})},
               {"2MR", new Talent(paladin, this, QObject::tr("Improved Seal of Righteousness"), "2MR", "Assets/ability/Ability_thunderbolt.png", 5,
                                  QObject::tr("Increases the damage done by your Seal of Righteousness and Judgement of Righteousness by %1%."),
                                  QVector<QPair<unsigned, unsigned>> {{3, 3}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(paladin, this, QObject::tr("Healing Light"), "3LL", "Assets/spell/Spell_holy_holybolt.png", 3,
                                                     QObject::tr("Increases the amount of healed by your Holy Light and Flash of Light spells by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{4, 4}})},
                                  {"3MR", new Talent(paladin, this, QObject::tr("Improved Lay on Hands"), "3MR", "Assets/spell/Spell_holy_layonhands.png", 2,
                                                     QObject::tr("Gives the target of your Lay on Hands spell a %1% bonus to their armor value from items for 2 "
                                                     "min. In addition, the cooldown for your Lay on Hands spell is reduced by %2 min."),
                                                     QVector<QPair<unsigned, unsigned>> {{15, 15}, {10, 10}})},
                                  {"3RR", new Talent(paladin, this, QObject::tr("Unyielding Faith"), "3RR", "Assets/spell/Spell_holy_unyieldingfaith.png", 2,
                                                     QObject::tr("Increases your chance to resist Fear and Disorient effects by an additional %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{5, 5}})}};
    add_consecration(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new Talent(paladin, this, QObject::tr("Illumination"), "4ML", "Assets/spell/Spell_holy_greaterheal.png", 5,
                                                     QObject::tr("After getting a critical effect from your Flash of Light, Holy Light, or Holy Shock heal "
                                                     "spell, gives you a %1% chance to gain Mana equal to the base cost of the spell."),
                                                     QVector<QPair<unsigned, unsigned>> {{20, 20}})},
                                  {"4MR", new Talent(paladin, this, QObject::tr("Improved Blessing of Wisdom"), "4MR", "Assets/spell/Spell_holy_sealofwisdom.png",
                                                     2, QObject::tr("Increases the effect of your Blessing of Wisdom spell by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{10, 10}})}};
    add_talents(tier4);

    QMap<QString, Talent*>
        tier5 {{"5ML", new Talent(paladin, this, QObject::tr("Divine Favor"), "5ML", "Assets/spell/Spell_holy_heal.png", 1,
                                  QObject::tr("When activated, gives your next Flash of Light, Holy Light, or Holy Shock spell a 100% critical effect chance."),
                                  QVector<QPair<unsigned, unsigned>>())},
               {"5MR", new Talent(paladin, this, QObject::tr("Lasting Judgement"), "5MR", "Assets/spell/Spell_holy_healingaura.png", 3,
                                  QObject::tr("Increases the duration of your Judgement of Light and Judgement of Wisdom by %1 sec."),
                                  QVector<QPair<unsigned, unsigned>> {{10, 10}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {
        {"6MR", new Talent(paladin, this, QObject::tr("Holy Power"), "6MR", "Assets/spell/Spell_holy_power.png", 5,
                           QObject::tr("Increases the critical effect chance of your Holy spells by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(paladin, this, QObject::tr("Holy Shock"), "7ML", "Assets/spell/Spell_holy_searinglight.png", 1,
                           QObject::tr("Blast the target with Holy energy, causing 204 to 221 Holy damage to an enemy, or 204 to 221 healing to an ally."),
                           QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["4ML"]->talent->set_bottom_child(talents["5ML"]->talent);
    talents["5ML"]->talent->set_parent(talents["4ML"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void HolyPaladin::add_divine_strength(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(paladin, this, QObject::tr("Divine Strength"), "1ML", "Assets/ability/Ability_golemthunderclap.png", 5,
                                         QObject::tr("Increases your Strength by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::StrengthMod, 2}});
    add_talent_to_tier(talent_tier, talent);
}

void HolyPaladin::add_divine_intellect(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(paladin, this, QObject::tr("Divine Intellect"), "1MR", "Assets/spell/Spell_nature_sleep.png", 5,
                                         QObject::tr("Increases your total Intellect by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::IntellectMod, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void HolyPaladin::add_consecration(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(paladin, QObject::tr("Consecration"), "3ML", "Assets/spell/Spell_holy_innerfire.png", 1,
                                 QObject::tr("Consecrates the land beneath Paladin, doing 64 Holy damage over 8 sec to enemies who enter the area."),
                                 QVector<QPair<unsigned, unsigned>>(),
                                 QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Consecration"))});

    add_talent_to_tier(talent_tier, talent);
}
