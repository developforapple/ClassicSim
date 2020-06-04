#include "Frost.h"
#include <QObject>
#include "Mage.h"
#include "MageSpells.h"
#include "Talent.h"
#include "TalentStatIncrease.h"

Frost::Frost(Mage* mage) : TalentTree(QObject::tr("Frost"), "Assets/mage/mage_frost.jpg"), mage(mage), spells(static_cast<MageSpells*>(mage->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Frost Warding"), "1LL"},     {QObject::tr("Improved Frostbolt"), "1ML"}, {QObject::tr("Elemental Precision"), "1MR"},
        {QObject::tr("Ice Shards"), "2LL"},        {QObject::tr("Frostbite"), "2ML"},          {QObject::tr("Improved Frost Nova"), "2MR"},
        {QObject::tr("Permafrost"), "2RR"},        {QObject::tr("Piercing Ice"), "3LL"},       {QObject::tr("Cold Snap"), "3ML"},
        {QObject::tr("Improved Blizzard"), "3RR"}, {QObject::tr("Arctic Reach"), "4LL"},       {QObject::tr("Frost Channeling"), "4ML"},
        {QObject::tr("Shatter"), "4MR"},           {QObject::tr("Ice Block"), "5ML"},          {QObject::tr("Improved Cone of Cold"), "5MR"},
        {QObject::tr("Winter's Chill"), "6MR"},    {QObject::tr("Ice Barrier"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {{"1LL", new Talent(mage, this, QObject::tr("Frost Warding"), "1LL", "Assets/spell/Spell_frost_frostward.png", 2,
                                                     QObject::tr("Increases the armor and resistances given by your Frost Armor and Ice Armor spells by %1%. In "
                                                     "addition, gives your Frost Ward a %2% chance to reflect Frost spells and effects while active."),
                                                     QVector<QPair<unsigned, unsigned>> {{15, 15}, {10, 10}})}};
    add_improved_frostbolt(tier1);
    add_elemental_precision(tier1);
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2ML",
                new Talent(mage, this, QObject::tr("Frostbite"), "2ML", "Assets/spell/Spell_frost_frostarmor.png", 3,
                           QObject::tr("Gives your Chill effects a %1% chance to freeze the target for 5 sec."), QVector<QPair<unsigned, unsigned>> {{5, 5}})},
               {"2MR", new Talent(mage, this, QObject::tr("Improved Frost Nova"), "2MR", "Assets/spell/Spell_frost_freezingbreath.png", 2,
                                  QObject::tr("Reduces the cooldown of your Frost Nova spell by %1 sec."), QVector<QPair<unsigned, unsigned>> {{2, 2}})},
               {"2RR", new Talent(mage, this, QObject::tr("Permafrost"), "2RR", "Assets/spell/Spell_frost_wisp.png", 3,
                                  QObject::tr("Increases the duration of your Chill effects by %1 sec and reduces the target's speed by an additional %2%."),
                                  QVector<QPair<unsigned, unsigned>> {{1, 1}, {4, 3}})}};
    add_ice_shards(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3ML", new Talent(mage, this, QObject::tr("Cold Snap"), "3ML", "Assets/spell/Spell_frost_wizardmark.png", 1,
                          QObject::tr("When activated, this spell finishes the cooldown on all of your Frost spells."), QVector<QPair<unsigned, unsigned>> {})}};
    add_piercing_ice(tier3);
    add_improved_blizzard(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4LL",
         new Talent(mage, this, QObject::tr("Arctic Reach"), "4LL", "Assets/spell/Spell_shadow_darkritual.png", 2,
                    QObject::tr("Increases the range of your Frostbolt and Blizzard spells and the radius of your Frost Nova and Cone of Cold spells by %1%."),
                    QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"4MR", new Talent(mage, this, QObject::tr("Shatter"), "4MR", "Assets/spell/Spell_frost_frostshock.png", 5,
                           QObject::tr("Increases the critical strike chance of all your spells against frozen targets by %1%."),
                           QVector<QPair<unsigned, unsigned>> {{10, 10}})}};
    add_frost_channeling(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new Talent(mage, this, QObject::tr("Ice Block"), "5ML", "Assets/spell/Spell_frost_frost.png", 1,
                                                     QObject::tr("You become encased in a block of ice, protecting you from all physical attacks and spells for "
                                                     "10 sec, but during that time you cannot attack, move or cast spells."),
                                                     QVector<QPair<unsigned, unsigned>> {})},
                                  {"5MR", new Talent(mage, this, QObject::tr("Improved Cone of Cold"), "5MR", "Assets/spell/Spell_frost_glacier.png", 3,
                                                     QObject::tr("Increases the damage dealt by your Cone of Cold spell by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{15, 10}})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_winters_chill(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(mage, this, QObject::tr("Ice Barrier"), "7ML", "Assets/spell/Spell_ice_lament.png", 1,
                           QObject::tr("Instantly shields you, absorbing 438 damage. Lasts 1 min. While the shield holds, spells will not be interrupted."),
                           QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Frost::add_improved_frostbolt(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Improved Frostbolt"), "1ML", "Assets/spell/Spell_frost_frostbolt02.png", 5,
                                    QObject::tr("Reduces the casting time of your Frostbolt spell by %1 sec."), QVector<QPair<double, double>> {{0.1, 0.1}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Frostbolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_elemental_precision(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(mage, this, QObject::tr("Elemental Precision"), "1MR", "Assets/spell/Spell_ice_magicdamage.png", 3,
                                         QObject::tr("Reduces the chance that the opponent can resist your Frost and Fire spells by %1%."),
                                         QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {
                                             {TalentStat::FrostHit, 200},
                                             {TalentStat::FireHit, 200},
                                         });

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_ice_shards(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Ice Shards"), "2LL", "Assets/items/Spell_frost_iceshard.png", 5,
                                    QObject::tr("Increases the critical strike damage bonus of your Frost spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{20, 20}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Frostbolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_piercing_ice(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(mage, this, QObject::tr("Piercing Ice"), "3LL", "Assets/spell/Spell_frost_frostbolt.png", 3,
                                            QObject::tr("Increases the damage done by your Frost spells by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                            QVector<QPair<TalentStat, unsigned>> {{TalentStat::FrostDmgMod, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_improved_blizzard(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Adds a chill effect to your Blizzard spell. This effect lowers the target's movement speed by %1%. Lasts 1.50 sec.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(30)}, {1, base_str.arg(30)}, {2, base_str.arg(50)}, {3, base_str.arg(65)}};
    Talent* talent = new Talent(mage, this, QObject::tr("Improved Blizzard"), "3RR", "Assets/spell/Spell_frost_icestorm.png", 3, rank_descriptions);

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_frost_channeling(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Frost Channeling"), "4ML", "Assets/spell/Spell_frost_stun.png", 3,
                                    QObject::tr("Reduces the mana cost of your Frost spells by %1% and reduces the threat caused by your Frost spells by %2%."),
                                    QVector<QPair<unsigned, unsigned>> {{5, 5}, {10, 10}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Frostbolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Frost::add_winters_chill(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Winter's Chill"), "6MR", "Assets/spell/Spell_frost_chillingblast.png", 5,
                                    QObject::tr("Gives your Frost damage spells a %1% chance to apply the Winter's Chill effect, which increases the chance a "
                                    "Frost spell will critically hit the target by 2% for 15 sec. Stacks up to 5 times."),
                                    QVector<QPair<unsigned, unsigned>> {{20, 20}}, {}, {}, {spells->get_winters_chill_proc()});

    add_talent_to_tier(talent_tier, talent);
}
