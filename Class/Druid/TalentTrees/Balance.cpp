#include "Balance.h"
#include <QObject>
#include "Druid.h"
#include "DruidSpells.h"
#include "Talent.h"
#include "TalentStatIncrease.h"

Balance::Balance(Druid* druid) :
    TalentTree(QObject::tr("Balance"), "Assets/druid/druid_balance.jpg"), druid(druid), spells(static_cast<DruidSpells*>(druid->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Improved Wrath"), "1LL"},
        {QObject::tr("Nature's Grasp"), "1ML"},
        {QObject::tr("Improved Nature's Grasp"), "1MR"},
        {QObject::tr("Improved Entangling Roots"), "2LL"},
        {QObject::tr("Improved Moonfire"), "2ML"},
        {QObject::tr("Natural Weapons"), "2MR"},
        {QObject::tr("Natural Shapeshifter"), "2RR"},
        {QObject::tr("Improved Thorns"), "3LL"},
        {QObject::tr("Omen of Clarity"), "3MR"},
        {QObject::tr("Nature's Reach"), "3RR"},
        {QObject::tr("Vengeance"), "4ML"},
        {QObject::tr("Improved Starfire"), "4MR"},
        {QObject::tr("Nature's Grace"), "5ML"},
        {QObject::tr("Moonglow"), "5MR"},
        {QObject::tr("Moonfury"), "6ML"},
        {QObject::tr("Moonkin Form"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(druid, this, QObject::tr("Nature's Grasp"), "1ML", "Assets/spell/Spell_nature_natureswrath.png", 1,
                           QObject::tr("While active, any time an enemy strikes the caster they have a 35% chance to become afflicted by Entangling Roots "
                           "(Rank 1). Only useable outdoors. 1 charge. Lasts 45 sec."),
                           QVector<QPair<unsigned, unsigned>>())},
    };
    add_improved_wrath(tier1);
    add_improved_natures_grasp(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2LL", new Talent(druid, this, QObject::tr("Improved Entangling Roots"), "2LL", "Assets/spell/Spell_nature_stranglevines.png", 3,
                           QObject::tr("Gives you a %1% chance to avoid interruption caused by damage while casting Entangling Roots."),
                           QVector<QPair<unsigned, unsigned>> {{40, 30}})},
    };
    add_improved_moonfire(tier2);
    add_natural_shapeshifter(tier2);
    add_natural_weapons(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL", new Talent(druid, this, QObject::tr("Improved Thorns"), "3LL", "Assets/spell/Spell_nature_thorns.png", 3,
                           QObject::tr("Increases damage caused by your Thorns spell by %1%."), QVector<QPair<unsigned, unsigned>> {{25, 25}})},
        {"3RR", new Talent(druid, this, QObject::tr("Nature's Reach"), "3RR", "Assets/items/Inv_misc_branch_01.png", 2,
                           QObject::tr("Increases the range of your Wrath, Entangling Roots, Faerie Fire, Moonfire, Starfire, and Hurricane spells by %1%."),
                           QVector<QPair<unsigned, unsigned>> {{10, 10}})},
    };
    add_omen_of_clarity(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {};
    add_vengeance(tier4);
    add_improved_starfire(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {};
    add_natures_grace(tier5);
    add_moonglow(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_moonfury(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_moonkin_form(tier7);
    add_talents(tier7);

    talents["1ML"]->talent->set_right_child(talents["1MR"]->talent);
    talents["1MR"]->talent->set_parent(talents["1ML"]->talent);

    talents["2ML"]->talent->set_bottom_child(talents["4ML"]->talent);
    talents["4ML"]->talent->set_parent(talents["2ML"]->talent);

    talents["2MR"]->talent->set_bottom_child(talents["3MR"]->talent);
    talents["3MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Balance::add_improved_wrath(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Improved Wrath"), "1LL", "Assets/items/Spell_nature_abolishmagic.png", 5,
                                    QObject::tr("Reduces the cast time of your Wrath spell by 0.%1 sec."), QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Wrath"))});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_natures_grasp(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Increases the chance for your Nature's Grasp to entangle an enemy by %1%.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(15)},
                                               {1, base_str.arg(15)},
                                               {2, base_str.arg(30)},
                                               {3, base_str.arg(45)},
                                               {4, base_str.arg(65)}};
    Talent* talent = new Talent(druid, this, QObject::tr("Improved Nature's Grasp"), "1MR", "Assets/spell/Spell_nature_natureswrath.png", 4, rank_descriptions);

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_moonfire(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Improved Moonfire"), "2ML", "Assets/spell/Spell_nature_starfall.png", 5,
                                    QObject::tr("Increases the damage and critical strike chance of your Moonfire spell by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Moonfire"))});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_natural_shapeshifter(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Natural Shapeshifter"), "2RR", "Assets/spell/Spell_nature_wispsplode.png", 3,
                                    QObject::tr("Reduces the mana cost of all shapeshifting by %1%."), QVector<QPair<unsigned, unsigned>> {{10, 10}},
                                    QVector<SpellRankGroup*> {
                                        spells->get_spell_rank_group_by_name(QObject::tr("Bear Form")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Cat Form")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Moonkin Form")),
                                    });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_natural_weapons(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(druid, this, QObject::tr("Natural Weapons"), "2MR", "Assets/items/Inv_staff_01.png", 5,
                                         QObject::tr("Increases the damage you deal with physical attacks in all forms by %1%."),
                                         QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::PhysicalDmgMod, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_omen_of_clarity(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Omen of Clarity"), "3MR", "Assets/items/Inv_misc_orb_01.png", 1,
                                    QObject::tr("Imbues the Druid with natural energy. Each of the Druid's melee attacks has a chance of causing the caster to "
                                    "enter a Clearcasting state. The Clearcasting state reduces the Mana, Rage or Energy cost of your next damage or "
                                    "healing spell or offensive ability by 100%. Lasts 10 min."),
                                    QVector<QPair<unsigned, unsigned>>(), {}, {}, QVector<Proc*> {spells->get_omen_of_clarity()});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_vengeance(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Vengeance"), "4ML", "Assets/spell/Spell_nature_purge.png", 5,
                                    QObject::tr("Increases the critical strike damage bonus of your Starfire, Moonfire, and Wrath spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{20, 20}},
                                    QVector<SpellRankGroup*> {
                                        spells->get_spell_rank_group_by_name(QObject::tr("Starfire")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Moonfire")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Wrath")),
                                    });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_improved_starfire(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Improved Starfire"), "4MR", "Assets/spell/Spell_arcane_starfire.png", 5,
                                    QObject::tr("Reduces the cast time of Starfire by 0.%1 sec and has a %2% chance to stun the target for 3 sec."),
                                    QVector<QPair<unsigned, unsigned>> {{1, 1}, {3, 3}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Starfire"))});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_natures_grace(QMap<QString, Talent*>& talent_tier) {
    Talent* talent
        = get_new_talent(druid, QObject::tr("Nature's Grace"), "5ML", "Assets/spell/Spell_nature_naturesblessing.png", 1,
                         QObject::tr("All spell criticals grace you with a blessing of nature, reducing the casting time of your next spell by 0.5 sec."),
                         QVector<QPair<unsigned, unsigned>>(), {}, QVector<Buff*> {spells->get_natures_grace()});

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_moonglow(QMap<QString, Talent*>& talent_tier) {
    Talent* talent
        = get_new_talent(druid, QObject::tr("Moonglow"), "5MR", "Assets/spell/Spell_nature_sentinal.png", 3,
                         QObject::tr("Reduces the Mana cost of your Moonfire, Starfire, Wrath, Healing Touch, Regrowth and Rejuvenation spells by %1%."),
                         QVector<QPair<unsigned, unsigned>> {{3, 3}},
                         QVector<SpellRankGroup*> {
                             spells->get_spell_rank_group_by_name(QObject::tr("Starfire")),
                             spells->get_spell_rank_group_by_name(QObject::tr("Moonfire")),
                             spells->get_spell_rank_group_by_name(QObject::tr("Wrath")),
                         });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_moonfury(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(druid, QObject::tr("Moonfury"), "6ML", "Assets/spell/Spell_nature_moonglow.png", 5,
                                    QObject::tr("Increases the damage done by your Starfire, Moonfire and Wrath spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                    QVector<SpellRankGroup*> {
                                        spells->get_spell_rank_group_by_name(QObject::tr("Starfire")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Moonfire")),
                                        spells->get_spell_rank_group_by_name(QObject::tr("Wrath")),
                                    });

    add_talent_to_tier(talent_tier, talent);
}

void Balance::add_moonkin_form(QMap<QString, Talent*>& talent_tier) {
    Talent* talent
        = get_new_talent(druid, QObject::tr("Moonkin Form"), "7ML", "Assets/spell/Spell_nature_forceofnature.png", 1,
                         QObject::tr("Transforms the Druid into Moonkin Form.  While in this form the armor contribution from items is increased by 360% and "
                         "all party members within 30 yards have their spell critical chance increased by 3%. The Moonkin can only cast Balance "
                         "spells while shapeshifted.\n\nThe act of shapeshifting frees the caster of Polymorph and Movement Impairing effects."),
                         QVector<QPair<unsigned, unsigned>>(), QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Moonkin Form"))});

    add_talent_to_tier(talent_tier, talent);
}
