#include "Execute.h"
#include <QObject>
#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Execute::Execute(Warrior* pchar, WarriorSpells* spells) :
    Spell(QObject::tr("Execute"), "Assets/items/Inv_sword_48.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 15),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Improved Execute"), 2, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    spell_ranks({QPair<int, int>(125, 3), QPair<int, int>(200, 6), QPair<int, int>(325, 9), QPair<int, int>(450, 12), QPair<int, int>(600, 15)}),
    talent_ranks({15, 13, 10}),
    execute_threshold(0.2) {
    initial_dmg = 600;
    dmg_per_rage_converted = 15;
}

Execute::~Execute() {
    delete cooldown;
}

SpellStatus Execute::is_ready_spell_specific() const {
    if (warr->in_defensive_stance())
        return SpellStatus::InDefensiveStance;

    if (warr->on_stance_cooldown())
        return SpellStatus::OnStanceCooldown;

    int combat_length = warr->get_sim_settings()->get_combat_length();
    double time_remaining = combat_length - warr->get_engine()->get_current_priority();
    return time_remaining / combat_length < execute_threshold ? SpellStatus::Available : SpellStatus::NotInExecuteRange;
}

void Execute::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(static_cast<unsigned>(round(warr->get_resource_level(resource_type) * 0.16)));
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        spells->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(warr->get_resource_level(resource_type) * 0.16)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(warr->get_resource_level(resource_type) * 0.16)));
        return;
    }

    const unsigned rage = warr->get_resource_level(resource_type);
    warr->lose_rage(rage);

    double damage_dealt = initial_dmg + (rage - resource_cost) * dmg_per_rage_converted;
    damage_dealt = damage_after_modifiers(damage_dealt);

    if (result == PhysicalAttackResult::CRITICAL) {
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt * warr->get_stats()->get_melee_ability_crit_dmg_mod())), rage, pchar->global_cooldown());
    } else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), rage, pchar->global_cooldown());
    }
}

void Execute::increase_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

void Execute::decrease_talent_rank_effect(const QString&, const int curr) {
    resource_cost = talent_ranks[curr];
}

void Execute::prepare_set_of_combat_iterations_spell_specific() {
    check((execute_threshold > -0.0001 && execute_threshold < 1.0001), "Invalid Execute range");
    this->execute_threshold = pchar->get_sim_settings()->get_execute_threshold();
}
