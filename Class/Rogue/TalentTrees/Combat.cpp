#include "Combat.h"
#include <QObject>
#include "AdrenalineRush.h"
#include "Backstab.h"
#include "BladeFlurry.h"
#include "DaggerSpecialization.h"
#include "Eviscerate.h"
#include "FistWeaponSpecialization.h"
#include "MaceSpecialization.h"
#include "OffhandAttackRogue.h"
#include "Precision.h"
#include "Rogue.h"
#include "RogueSpells.h"
#include "SinisterStrike.h"
#include "SwordSpecialization.h"
#include "Talent.h"
#include "WeaponExpertise.h"

Combat::Combat(Rogue* pchar) :
    TalentTree(QObject::tr("Combat"), "Assets/rogue/rogue_combat.jpg"), rogue(pchar), spells(static_cast<RogueSpells*>(pchar->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Improved Gouge"), "1LL"},
        {QObject::tr("Improved Sinister Strike"), "1ML"},
        {QObject::tr("Lightning Reflexes"), "1MR"},
        {QObject::tr("Improved Backstab"), "2LL"},
        {QObject::tr("Deflection"), "2ML"},
        {QObject::tr("Precision"), "2MR"},
        {QObject::tr("Endurance"), "3LL"},
        {QObject::tr("Riposte"), "3ML"},
        {QObject::tr("Improved Sprint"), "3RR"},
        {QObject::tr("Improved Kick"), "4LL"},
        {QObject::tr("Dagger Specialization"), "4ML"},
        {QObject::tr("Dual Wield Specialization"), "4MR"},
        {QObject::tr("Mace Specialization"), "5LL"},
        {QObject::tr("Blade Flurry"), "5ML"},
        {QObject::tr("Sword Specialization"), "5MR"},
        {QObject::tr("Fist Weapon Specialization"), "5RR"},
        {QObject::tr("Weapon Expertise"), "6ML"},
        {QObject::tr("Aggression"), "6MR"},
        {QObject::tr("Adrenaline Rush"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {{"1LL", new Talent(pchar, this, QObject::tr("Improved Gouge"), "1LL", "Assets/ability/Ability_gouge.png", 3,
                                                     QObject::tr("Increases the effect duration of your Gouge ability by %1 sec."),
                                                     QVector<QPair<double, double>> {{0.5, 0.5}})},
                                  {"1MR", new Talent(pchar, this, QObject::tr("Lightning Reflexes"), "1MR", "Assets/spell/Spell_nature_invisibility.png", 5,
                                                     QObject::tr("Increases your Dodge chance by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})}};
    add_improved_sinister_strike(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2ML", new Talent(pchar, this, QObject::tr("Deflection"), "2ML", "Assets/ability/Ability_parry.png", 5,
                                                     QObject::tr("Increases your Parry chance by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}})},
                                  {"2MR", new Precision(pchar, this)}};
    add_improved_backstab(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3ML", new Talent(pchar, this, QObject::tr("Riposte"), "3ML", "Assets/ability/Ability_warrior_challange.png", 1,
                                                     QObject::tr("A strike that becomes active after parrying an opponent's attack. This deals 150% weapon "
                                                     "damage and disarms the target for 6 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {})},
                                  {"3RR",
                                   new Talent(pchar, this, QObject::tr("Improved Sprint"), "3RR", "Assets/ability/Ability_rogue_sprint.png", 2,
                                              QObject::tr("Gives a %1% chance to remove all movement impairing effects when you activate your Sprint ability."),
                                              QVector<QPair<unsigned, unsigned>> {{50, 50}})}};
    add_endurance(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(pchar, this, QObject::tr("Improved Kick"), "4LL", "Assets/ability/Ability_kick.png", 2,
                                                     QObject::tr("Gives your Kick ability a %1% chance to silence the target for 2 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {{50, 50}})},
                                  {"4ML", new DaggerSpecialization(pchar, this)}};
    add_dual_wield_spec(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new MaceSpecialization(pchar, this)}, {"5RR", new FistWeaponSpecialization(pchar, this)}};
    add_blade_flurry(tier5);
    add_sword_spec(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6ML", new WeaponExpertise(pchar, this)}};
    add_aggression(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_adrenaline_rush(tier7);
    add_talents(tier7);

    talents["2ML"]->talent->set_bottom_child(talents["3ML"]->talent);
    talents["3ML"]->talent->set_parent(talents["2ML"]->talent);

    talents["2MR"]->talent->set_bottom_child(talents["4MR"]->talent);
    talents["4MR"]->talent->set_parent(talents["2MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Combat::add_improved_sinister_strike(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Reduces the Energy cost of your Sinister Strike ability by %1.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 2, QVector<QPair<unsigned, unsigned>> {{3, 2}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Improved Sinister Strike"), "1ML", "Assets/spell/Spell_shadow_ritualofsacrifice.png", 2,
                                rank_descriptions, QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Sinister Strike"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_improved_backstab(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases the critical strike chance of your Backstab ability by %1%.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 3, QVector<QPair<unsigned, unsigned>> {{10, 10}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Improved Backstab"), "2LL", "Assets/ability/Ability_backstab.png", 3, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Backstab"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_dual_wield_spec(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases the damage done by your offhand weapon by %1%.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>> {{10, 10}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Dual Wield Specialization"), "4MR", "Assets/ability/Ability_dualwield.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Offhand Attack"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_blade_flurry(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases your attack speed by 20%. In addition, attacks strike an additional nearby opponent. Lasts 15 sec.");
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(rogue, this, QObject::tr("Blade Flurry"), "5ML", "Assets/ability/Ability_warrior_punishingblow.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Blade Flurry"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_sword_spec(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Gives you a %1% chance to get an extra attack on the same target after dealing damage with your Sword.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 5, QVector<QPair<unsigned, unsigned>> {{1, 1}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Sword Specialization"), "5MR", "Assets/items/Inv_sword_27.png", 5, rank_descriptions, {}, {},
                                QVector<Proc*> {rogue->get_sword_spec()});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_aggression(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases the damage of your Sinister Strike and Eviscerate abilities by %1%.");
    Talent::initialize_rank_descriptions(rank_descriptions, base_str, 3, QVector<QPair<unsigned, unsigned>> {{2, 2}});
    Talent* talent = new Talent(rogue, this, QObject::tr("Aggression"), "6MR", "Assets/ability/Ability_racial_avatar.png", 3, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Eviscerate")),
                                                          spells->get_spell_rank_group_by_name(QObject::tr("Sinister Strike"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_adrenaline_rush(QMap<QString, Talent*>& talent_tier) {
    QMap<unsigned, QString> rank_descriptions;
    QString base_str = QObject::tr("Increases your Energy regeneration rate by 100% for 15 sec.");
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
    Talent* talent = new Talent(rogue, this, QObject::tr("Adrenaline Rush"), "7ML", "Assets/spell/Spell_shadow_shadowworddominate.png", 1, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Adrenaline Rush"))});

    add_talent_to_tier(talent_tier, talent);
}

void Combat::add_endurance(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Reduces the cooldown of your Sprint and Evasion abilities by %1.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(QObject::tr("45 sec"))}, {1, base_str.arg(QObject::tr("45 sec"))}, {2, base_str.arg(QObject::tr("1.5 min"))}};
    Talent* talent = new Talent(rogue, this, QObject::tr("Endurance"), "3LL", "Assets/spell/Spell_shadow_shadowward.png", 2, rank_descriptions);

    add_talent_to_tier(talent_tier, talent);
}
