#include "Enhancement.h"
#include <QObject>
#include "Shaman.h"
#include "ShamanSpells.h"
#include "SpellRankGroup.h"
#include "TalentStatIncrease.h"

Enhancement::Enhancement(Shaman* shaman) :
    TalentTree(QObject::tr("Enhancement"), "Assets/shaman/shaman_enhancement.jpg"), shaman(shaman), spells(static_cast<ShamanSpells*>(shaman->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Ancestral Knowledge"), "1ML"}, {QObject::tr("Shield Specialization"), "1MR"},
        {QObject::tr("Guardian Totems"), "2LL"},     {QObject::tr("Thundering Strikes"), "2ML"},
        {QObject::tr("Improved Ghost Wolf"), "2MR"}, {QObject::tr("Improved Lightning Shield"), "2RR"},
        {QObject::tr("Enhancing Totems"), "3LL"},    {QObject::tr("Two-Handed Axes and Maces"), "3MR"},
        {QObject::tr("Anticipation"), "3RR"},        {QObject::tr("Flurry"), "4ML"},
        {QObject::tr("Toughness"), "4MR"},           {QObject::tr("Improved Weapon Totems"), "5LL"},
        {QObject::tr("Elemental Weapons"), "5ML"},   {QObject::tr("Parry"), "5MR"},
        {QObject::tr("Weapon Mastery"), "6MR"},      {QObject::tr("Stormstrike"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {{"1ML", new Talent(shaman, this, QObject::tr("Ancestral Knowledge"), "1ML", "Assets/spell/Spell_shadow_grimward.png", 5,
                                                     QObject::tr("Increases your maximum Mana by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})},
                                  {"1MR",
                                   new Talent(shaman, this, QObject::tr("Shield Specialization"), "1MR", "Assets/items/Inv_shield_06.png", 5,
                                              QObject::tr("Increases your chance to block attacks with a shield by %1% and increases the amount blocked by %2%."),
                                              QVector<QPair<unsigned, unsigned>> {{1, 1}, {5, 5}})}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new Talent(shaman, this, QObject::tr("Guardian Totems"), "2LL", "Assets/spell/Spell_nature_stoneskintotem.png", 2,
                                                     QObject::tr("Increases the amount of damage reduced by your Stoneskin Totem and Windwall Totem by %1% and "
                                                     "reduces the cooldown of your Grounding Totem by %2 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {{10, 10}, {1, 1}})},
                                  {"2MR",
                                   new Talent(shaman, this, QObject::tr("Improved Ghost Wolf"), "2MR", "Assets/spell/Spell_nature_spiritwolf.png", 2,
                                              QObject::tr("Reduces cast time of your Ghost Wolf spell by %1 sec."), QVector<QPair<unsigned, unsigned>> {{1, 1}})},
                                  {"2RR", new Talent(shaman, this, QObject::tr("Improved Lightning Shield"), "2RR", "Assets/spell/Spell_nature_lightningshield.png",
                                                     3, QObject::tr("Increases the damage done by your Lightning Shield orbs by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{5, 5}})}};
    add_thundering_strikes(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(shaman, this, QObject::tr("Enhancing Totems"), "3LL", "Assets/spell/Spell_nature_earthbindtotem.png", 2,
                                                     QObject::tr("Increases the effect of your Strength of Earth and Grace of Air Totems by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{8, 7}})},
                                  {"3MR",
                                   new Talent(shaman, this, QObject::tr("Two-Handed Axes and Maces"), "3MR", "Assets/items/Inv_axe_10.png", 1,
                                              QObject::tr("Allows you to use Two-Handed Axes and Two-Handed Maces."), QVector<QPair<unsigned, unsigned>> {})},
                                  {"3RR",
                                   new Talent(shaman, this, QObject::tr("Anticipation"), "3RR", "Assets/spell/Spell_nature_mirrorimage.png", 5,
                                              QObject::tr("Increases your chance to dodge by an additional %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4MR", new Talent(shaman, this, QObject::tr("Toughness"), "4MR", "Assets/spell/Spell_holy_devotion.png", 5,
                                                     QObject::tr("Increases your armor value from items by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_flurry(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(shaman, this, QObject::tr("Improved Weapon Totems"), "5LL", "Assets/spell/Spell_fire_enchantweapon.png", 2,
                                                     QObject::tr("Increases the melee attack power bonus of your Windfury Totem by %1% and increases the damage "
                                                     "caused by your Flametongue Totem by %2%."),
                                                     QVector<QPair<unsigned, unsigned>> {{15, 15}, {6, 6}})},
                                  {"5MR", new Talent(shaman, this, QObject::tr("Parry"), "5MR", "Assets/ability/Ability_parry.png", 1,
                                                     QObject::tr("Gives a chance to parry enemy melee attacks."), QVector<QPair<unsigned, unsigned>> {})}};
    add_elemental_weapons(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_weapon_mastery(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_stormstrike(tier7);
    add_talents(tier7);

    talents["2ML"]->talent->set_bottom_child(talents["4ML"]->talent);
    talents["4ML"]->talent->set_parent(talents["2ML"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Enhancement::add_thundering_strikes(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(shaman, this, QObject::tr("Thundering Strikes"), "2ML", "Assets/ability/Ability_thunderbolt.png", 5,
                                         QObject::tr("Improves your chance to get a critical strike with your weapon attacks by %1%."),
                                         QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::MeleeCrit, 100}});

    add_talent_to_tier(talent_tier, talent);
}

void Enhancement::add_flurry(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(shaman, QObject::tr("Flurry"), "4ML", "Assets/ability/Ability_ghoulfrenzy.png", 5,
                                    QObject::tr("Increases your attack speed by %1% for your next 3 swings after dealing a critical strike."),
                                    QVector<QPair<unsigned, unsigned>> {{10, 5}}, {}, QVector<Buff*> {spells->get_flurry()});

    add_talent_to_tier(talent_tier, talent);
}

void Enhancement::add_elemental_weapons(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Increases the melee attack power bonus of your Rockbiter Weapon by %1%, your Windfury Weapon effect by %2% and increases the "
                       "damage caused by your Flametongue Weapon and Frostbrand Weapon by %3%.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(7).arg(13).arg(5)},
                                               {1, base_str.arg(7).arg(13).arg(5)},
                                               {2, base_str.arg(14).arg(27).arg(10)},
                                               {3, base_str.arg(20).arg(40).arg(15)}};
    Talent* talent = new Talent(shaman, this, QObject::tr("Elemental Weapons"), "5ML", "Assets/spell/Spell_fire_flametounge.png", 3, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Windfury Weapon"))});

    add_talent_to_tier(talent_tier, talent);
}

void Enhancement::add_weapon_mastery(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(shaman, this, QObject::tr("Weapon Mastery"), "6MR", "Assets/ability/Ability_hunter_swiftstrike.png", 5,
                                         QObject::tr("Increases the damage you deal with all weapons by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::OneHandMeleeDmg, 2}, {TalentStat::TwoHandMeleeDmg, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void Enhancement::add_stormstrike(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str
        = QObject::tr("Gives you an extra attack. In addition, the next 2 sources of Nature damage dealt to the target are increased by 20%. Lasts 12 sec.");
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(shaman, this, QObject::tr("Stormstrike"), "7ML", "Assets/spell/Spell_holy_sealofmight.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Stormstrike"))});

    add_talent_to_tier(talent_tier, talent);
}
