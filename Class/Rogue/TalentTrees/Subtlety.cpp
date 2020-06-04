#include "Subtlety.h"
#include <QObject>
#include "Backstab.h"
#include "Deadliness.h"
#include "Hemorrhage.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SerratedBlades.h"
#include "Talent.h"

Subtlety::Subtlety(Rogue* pchar) :
    TalentTree(QObject::tr("Subtlety"), "Assets/rogue/rogue_subtlety.jpg"), rogue(pchar), spells(static_cast<RogueSpells*>(pchar->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Master of Deception"), "1ML"}, {QObject::tr("Opportunity"), "1MR"},       {QObject::tr("Sleight of Hand"), "2LL"}, {QObject::tr("Elusiveness"), "2ML"}, {QObject::tr("Camouflage"), "2MR"},
        {QObject::tr("Initiative"), "3LL"},          {QObject::tr("Ghostly Strike"), "3ML"},    {QObject::tr("Improved Ambush"), "3MR"}, {QObject::tr("Setup"), "4LL"},       {QObject::tr("Improved Sap"), "4ML"},
        {QObject::tr("Serrated Blades"), "4MR"},     {QObject::tr("Heightened Senses"), "5LL"}, {QObject::tr("Preparation"), "5ML"},     {QObject::tr("Dirty Deeds"), "5MR"}, {QObject::tr("Hemorrhage"), "5RR"},
        {QObject::tr("Deadliness"), "6MR"},          {QObject::tr("Premeditation"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1ML", new Talent(pchar, this, QObject::tr("Master of Deception"), "1ML", "Assets/spell/Spell_shadow_charm.png", 5,
                           QObject::tr("Reduces the chance enemies have to detect you while in Stealth mode."), QVector<QPair<unsigned, unsigned>> {})}};
    add_opportunity(tier1);
    add_talents(tier1);

    QMap<QString, Talent*>
        tier2 {{"2LL", new Talent(pchar, this, QObject::tr("Sleight of Hand"), "2LL", "Assets/ability/Ability_rogue_feint.png", 2,
                                  QObject::tr("Reduces the chance you are critically hit by melee and ranged attacks by %1% and increases the threat "
                                  "reduction of your Feint ability by %2%."),
                                  QVector<QPair<unsigned, unsigned>> {{1, 1}, {10, 10}})},
               {"2ML",
                new Talent(pchar, this, QObject::tr("Elusiveness"), "2ML", "Assets/spell/Spell_magic_lesserinvisibilty.png", 2,
                           QObject::tr("Reduces the cooldown of your Vanish and Blind abilities by %1 sec."), QVector<QPair<unsigned, unsigned>> {{45, 45}})},
               {"2MR", new Talent(pchar, this, QObject::tr("Camouflage"), "2MR", "Assets/ability/Ability_stealth.png", 5,
                                  QObject::tr("Increases your speed while stealthed by %1% and reduces the cooldown of your Stealth ability by %2 sec."),
                                  QVector<QPair<unsigned, unsigned>> {{3, 3}, {1, 1}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3LL",
         new Talent(pchar, this, QObject::tr("Initiative"), "3LL", "Assets/spell/Spell_shadow_fumble.png", 3,
                    QObject::tr("Gives you a %1% chance to add an additional combo point to your target when using your Ambush, Garrote, or Cheap Shot ability."),
                    QVector<QPair<unsigned, unsigned>> {{25, 25}})},
        {"3ML", new Talent(pchar, this, QObject::tr("Ghostly Strike"), "3ML", "Assets/spell/Spell_shadow_curse.png", 1,
                           QObject::tr("A strike that deals 125% weapon damage and increases your chance to dodge by 15% for 7 sec. Awards 1 combo point."),
                           QVector<QPair<unsigned, unsigned>> {})},
        {"3MR", new Talent(pchar, this, QObject::tr("Improved Ambush"), "3MR", "Assets/ability/Ability_rogue_ambush.png", 3,
                           QObject::tr("Increases the critical strike chance of your Ambush ability by %1%."), QVector<QPair<unsigned, unsigned>> {{15, 15}})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(pchar, this, QObject::tr("Setup"), "4LL", "Assets/spell/Spell_nature_mirrorimage.png", 3,
                                                     QObject::tr("Gives you a %1% chance to add a combo point to your target after dodging their attack or fully "
                                                     "resisting one of their spells."),
                                                     QVector<QPair<unsigned, unsigned>> {{15, 15}})},
                                  {"4ML", new Talent(pchar, this, QObject::tr("Improved Sap"), "4ML", "Assets/ability/Ability_sap.png", 3,
                                                     QObject::tr("Gives you a %1% chance to return to stealth mode after using your Sap ability."),
                                                     QVector<QPair<unsigned, unsigned>> {{30, 30}})},
                                  {"4MR", new SerratedBlades(pchar, this)}};
    add_talents(tier4);

    QMap<QString, Talent*>
        tier5 {{"5LL", new Talent(pchar, this, QObject::tr("Heightened Senses"), "5LL", "Assets/ability/Ability_ambush.png", 2,
                                  QObject::tr("Increases your Stealth detection and reduces the chance you are hit by spells and ranged attacks by %1%."),
                                  QVector<QPair<unsigned, unsigned>> {{2, 2}})},
               {"5ML", new Talent(pchar, this, QObject::tr("Preparation"), "5ML", "Assets/spell/Spell_shadow_antishadow.png", 1,
                                  QObject::tr("When activated, this ability immediately finishes the cooldown on your other Rogue abilities."),
                                  QVector<QPair<unsigned, unsigned>>())},
               {"5MR", new Talent(pchar, this, QObject::tr("Dirty Deeds"), "5MR", "Assets/spell/Spell_shadow_summonsuccubus.png", 2,
                                  QObject::tr("Reduces the Energy cost of your Cheap Shot and Garrote abilities by %1."),
                                  QVector<QPair<unsigned, unsigned>> {{10, 10}})}};
    add_hemorrhage(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6MR", new Deadliness(pchar, this)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(pchar, this, QObject::tr("Premeditation"), "7ML", "Assets/spell/Spell_shadow_possession.png", 1,
                                                     QObject::tr("When used, adds 2 combo points to your target. You must add to or use those combo points "
                                                     "within 10 sec or the combo points are lost."),
                                                     QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["4MR"]->talent->set_right_child(talents["5RR"]->talent);
    talents["5RR"]->talent->set_parent(talents["4MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Subtlety::add_opportunity(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases the damage dealt when striking from behind with your Backstab, Garrote, or Ambush abilities by %1%.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>> {{4, 4}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Opportunity"), "1MR", "Assets/ability/Ability_warrior_warcry.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Backstab"))});

    add_talent_to_tier(talent_tier, talent);
}

void Subtlety::add_hemorrhage(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("An instant strike that damages the opponent and causes the target to hemorrhage, increasing any Physical damage dealt to the "
                       "target by up to 3. Lasts 30 charges or 15 sec. Awards 1 combo point.");
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(rogue, this, QObject::tr("Hemorrhage"), "5RR", "Assets/spell/Spell_shadow_lifedrain.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Hemorrhage"))});

    add_talent_to_tier(talent_tier, talent);
}
