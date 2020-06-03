#include "BeastMastery.h"
#include <QObject>
#include "AspectOfTheHawk.h"
#include "BestialWrath.h"
#include "FrenzyProc.h"
#include "Hunter.h"
#include "HunterPet.h"
#include "HunterSpells.h"
#include "ImprovedAspectOfTheHawkProc.h"
#include "TalentStatIncrease.h"

BeastMastery::BeastMastery(Hunter* hunter) :
    TalentTree(QObject::tr("Beast Mastery"), "Assets/hunter/hunter_beastmastery.jpg"), hunter(hunter), spells(static_cast<HunterSpells*>(hunter->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Improved Aspect of the Hawk"), "1ML"},
        {QObject::tr("Endurance Training"), "1MR"},
        {QObject::tr("Improved Eyes of the Beast"), "2LL"},
        {QObject::tr("Improved Aspect of the Monkey"), "2ML"},
        {QObject::tr("Thick Hide"), "2MR"},
        {QObject::tr("Improved Revive Pet"), "2RR"},
        {QObject::tr("Pathfinding"), "3LL"},
        {QObject::tr("Bestial Swiftness"), "3ML"},
        {QObject::tr("Unleashed Fury"), "3MR"},
        {QObject::tr("Improved Mend Pet"), "4ML"},
        {QObject::tr("Ferocity"), "4MR"},
        {QObject::tr("Spirit Bond"), "5LL"},
        {QObject::tr("Intimidation"), "5ML"},
        {QObject::tr("Bestial Discipline"), "5RR"},
        {QObject::tr("Frenzy"), "6MR"},
        {QObject::tr("Bestial Wrath"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {{"1MR", new Talent(hunter, this, QObject::tr("Endurance Training"), "1MR", "Assets/spell/Spell_nature_reincarnation.png", 5,
                                                     QObject::tr("Increases the Health of your pets by %1%."), QVector<QPair<unsigned, unsigned>> {{3, 3}})}};
    add_improved_aspect_of_the_hawk(tier1);
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2LL", new Talent(hunter, this, QObject::tr("Improved Eyes of the Beast"), "2LL", "Assets/ability/Ability_eyeoftheowl", 2,
                                 QObject::tr("Increases the duration of your Eyes of the Beast by %1 sec."), QVector<QPair<unsigned, unsigned>> {{30, 30}})},
               {"2ML", new Talent(hunter, this, QObject::tr("Improved Aspect of the Monkey"), "2ML", "Assets/ability/Ability_hunter_aspectofthemonkey.png", 5,
                                  QObject::tr("Increases the Dodge bonus of your Aspect of the Monkey by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})},
               {"2MR", new Talent(hunter, this, QObject::tr("Thick Hide"), "2MR", "Assets/items/Inv_misc_pelt_bear_03.png", 3,
                                  QObject::tr("Increases the Armor rating of your pets by %1%."), QVector<QPair<unsigned, unsigned>> {{10, 10}})},
               {"2RR", new Talent(hunter, this, QObject::tr("Improved Revive Pet"), "2RR", "Assets/ability/Ability_hunter_beastsoothe.png", 2,
                                  QObject::tr("Revive Pet's casting time is reduced by %1 sec, mana cost is reduced by %2%, and increases the health your "
                                  "pet auto talent =s with by an additional %3%"),
                                  QVector<QPair<unsigned, unsigned>> {{3, 3}, {20, 20}, {15, 15}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(hunter, this, QObject::tr("Pathfinding"), "3LL", "Assets/ability/Ability_mount_jungletiger.png", 2,
                                                     QObject::tr("Increases the speed bonus of your Aspect of the Cheetah and Aspect of the Pack by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{3, 3}})},
                                  {"3ML",
                                   new Talent(hunter, this, QObject::tr("Bestial Swiftness"), "3ML", "Assets/ability/Ability_druid_dash.png", 1,
                                              QObject::tr("Increases the outdoor movement speed of your pets by 30%."), QVector<QPair<unsigned, unsigned>>())}};
    add_unleashed_fury(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4ML", new Talent(hunter, this, QObject::tr("Improved Mend Pet"), "4ML", "Assets/ability/Ability_hunter_mendpet.png", 2,
                           QObject::tr("Gives the Mend Pet spell a %1% chance of cleansing 1 Curse, Disease, Magic or Poison effect from the pet each tick."),
                           QVector<QPair<unsigned, unsigned>> {{15, 35}})}};
    add_ferocity(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(hunter, this, QObject::tr("Spirit Bond"), "5LL", "Assets/ability/Ability_druid_demoralizingroar.png", 2,
                                                     QObject::tr("While your pet is active, you and your pet will regenerate %1% of total health every 10 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {{1, 1}})},
                                  {"5ML", new Talent(hunter, this, QObject::tr("Intimidation"), "5ML", "Assets/ability/Ability_devour.png", 1,
                                                     QObject::tr("Command your pet to intimidate the target on the next successful melee attack, causing a high "
                                                     "amount of threat and stunning the target for 3 sec."),
                                                     QVector<QPair<unsigned, unsigned>>())}};
    add_bestial_discipline(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_frenzy(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_bestial_wrath(tier7);
    add_talents(tier7);

    talents["4MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["4MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void BeastMastery::add_improved_aspect_of_the_hawk(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(
        hunter, QObject::tr("Improved Aspect of the Hawk"), "1ML", "Assets/spell/Spell_nature_ravenform.png", 5,
        QObject::tr("While Aspect of the Hawk is active, all normal ranged attacks have a %1% chance of increasing ranged attack speed by 30% for 12 sec."),
        QVector<QPair<unsigned, unsigned>> {{1, 1}}, {}, {},
        QVector<Proc*> {spells->get_aspect_of_the_hawk()->get_improved_aspect_of_the_hawk_proc()});

    add_talent_to_tier(talent_tier, talent);
}

void BeastMastery::add_unleashed_fury(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, QObject::tr("Unleashed Fury"), "3MR", "Assets/ability/Ability_bullrush.png", 5,
                                         QObject::tr("Increases the damage done by your pets by %1%."), QVector<QPair<unsigned, unsigned>> {{4, 4}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::PetDmgMod, 4}});

    add_talent_to_tier(talent_tier, talent);
}

void BeastMastery::add_ferocity(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, QObject::tr("Ferocity"), "4MR", "Assets/items/Inv_misc_monsterclaw_04.png", 5,
                                         QObject::tr("Increases the critical strike chance of your pets by %1%."), QVector<QPair<unsigned, unsigned>> {{3, 3}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::PetCritChance, 300}});

    add_talent_to_tier(talent_tier, talent);
}

void BeastMastery::add_bestial_discipline(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(hunter, this, QObject::tr("Bestial Discipline"), "5RR", "Assets/items/Spell_nature_abolishmagic.png", 2,
                                         QObject::tr("Increases the Focus regeneration of your pets by %1%."), QVector<QPair<unsigned, unsigned>> {{10, 10}},
                                         QVector<QPair<TalentStat, unsigned>> {{TalentStat::PetFocusGain, 0}});

    add_talent_to_tier(talent_tier, talent);
}

void BeastMastery::add_frenzy(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, QObject::tr("Frenzy"), "6MR", "Assets/items/Inv_misc_monsterclaw_03.png", 5,
                                 QObject::tr("Gives your pet a %1% chance to gain a 30% attack speed increase for 8 sec after dealing a critical strike."),
                                 QVector<QPair<unsigned, unsigned>> {{20, 20}}, {}, {},
                                 QVector<Proc*> {static_cast<HunterPet*>(hunter->get_pet())->get_frenzy_proc()});

    add_talent_to_tier(talent_tier, talent);
}

void BeastMastery::add_bestial_wrath(QMap<QString, Talent*>& talent_tier) {
    auto talent = get_new_talent(hunter, QObject::tr("Bestial Wrath"), "7ML", "Assets/ability/Ability_druid_ferociousbite.png", 1,
                                 QObject::tr("Send your pet into a rage causing 50% additional damage for 18 sec. While enraged, the beast does not feel pity or "
                                 "remorse or fear and it cannot be stopped unless killed."),
                                 QVector<QPair<unsigned, unsigned>>(),
                                 QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Bestial Wrath"))});

    add_talent_to_tier(talent_tier, talent);
}
