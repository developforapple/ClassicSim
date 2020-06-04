#include "SinisterStrike.h"
#include <QObject>
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Equipment.h"
#include "Rogue.h"
#include "SealFate.h"
#include "Utils/Check.h"
#include "Weapon.h"

SinisterStrike::SinisterStrike(Rogue* rogue) :
    Spell(QObject::tr("Sinister Strike"),
          "Assets/spell/Spell_shadow_ritualofsacrifice.png",
          rogue,
          new CooldownControl(rogue, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Energy,
          45),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Aggression"), 3, DisabledAtZero::No),
                                                 new TalentRequirerInfo(QObject::tr("Improved Sinister Strike"), 2, DisabledAtZero::No),
                                                 new TalentRequirerInfo(QObject::tr("Lethality"), 5, DisabledAtZero::No)}),
    SetBonusRequirer({QObject::tr("Bonescythe Armor")}),
    rogue(rogue),
    imp_ss_ranks({45, 42, 40}),
    aggression_ranks({1.0, 1.02, 1.04, 1.06}),
    lethality_ranks({0.0, 0.06, 0.12, 0.18, 0.24, 0.30}) {}

SinisterStrike::~SinisterStrike() {
    delete cooldown;
}

void SinisterStrike::spell_effect() {
    rogue->exit_stealth();

    const int result = roll->get_melee_ability_result(rogue->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        rogue->lose_energy(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        rogue->lose_energy(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    rogue->lose_energy(resource_cost);
    rogue->gain_combo_points(1);

    double base_dmg = rogue->get_random_normalized_mh_dmg() + 68.0;
    double damage_dealt = damage_after_modifiers(base_dmg * aggression);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * (rogue->get_stats()->get_melee_ability_crit_dmg_mod() + lethality));
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());

        rogue->gain_energy(bonescythe_energy);
        statistics_resource->add_resource_gain(ResourceType::Energy, bonescythe_energy);

        if (rogue->get_seal_fate()->is_enabled() && rogue->get_seal_fate()->check_proc_success()) {
            rogue->get_seal_fate()->set_current_proc_source(ProcInfo::Source::MainhandSpell);
            rogue->get_seal_fate()->perform();
        }
    } else if (result == PhysicalAttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
}

void SinisterStrike::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Improved Sinister Strike"))
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == QObject::tr("Aggression"))
        aggression = aggression_ranks[curr];
    else if (talent_name == QObject::tr("Lethality"))
        lethality = lethality_ranks[curr];
}

void SinisterStrike::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Improved Sinister Strike"))
        resource_cost = imp_ss_ranks[curr];
    else if (talent_name == QObject::tr("Aggression"))
        aggression = aggression_ranks[curr];
    else if (talent_name == QObject::tr("Lethality"))
        lethality = lethality_ranks[curr];
}

void SinisterStrike::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Bonescythe Armor")) {
        switch (set_bonus) {
        case 4:
            bonescythe_energy = 5;
            break;
        default:
            check(false, "SinisterStrike::activate_set_bonus_effect reached end of switch");
        }
    }
}

void SinisterStrike::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Bonescythe Armor")) {
        switch (set_bonus) {
        case 4:
            bonescythe_energy = 0;
            break;
        default:
            check(false, "SinisterStrike::deactivate_set_bonus_effect reached end of switch");
        }
    }
}

void SinisterStrike::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QObject::tr("%1 Bonescythe 4P").arg(name), icon);
}
