#include "OffhandAttackWarrior.h"
#include <QObject>
#include "Buff.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Equipment.h"
#include "Flurry.h"
#include "RecklessnessBuff.h"
#include "StatisticsResource.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Weapon.h"

OffhandAttackWarrior::OffhandAttackWarrior(Warrior* pchar, WarriorSpells* spells) :
    OffhandAttack(pchar),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Dual Wield Specialization"), 5, DisabledAtZero::No)}),
    warr(pchar),
    spells(spells),
    talent_ranks({0.5, 0.525, 0.55, 0.575, 0.6, 0.625}) {
    offhand_penalty = talent_ranks[0];
}

void OffhandAttackWarrior::increase_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}

void OffhandAttackWarrior::decrease_talent_rank_effect(const QString&, const int curr) {
    offhand_penalty = talent_ranks[curr];
}

void OffhandAttackWarrior::calculate_damage() {
    const unsigned oh_wpn_skill = warr->get_oh_wpn_skill();
    const int result = roll->get_melee_hit_result(oh_wpn_skill, pchar->get_stats()->get_oh_crit_chance());

    spells->get_flurry()->use_charge();

    if (result == PhysicalAttackResult::MISS)
        return increment_miss();

    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        spells->get_overpower_buff()->apply_buff();
        gain_rage(damage_after_modifiers(warr->get_avg_oh_damage() * offhand_penalty));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        gain_rage(damage_after_modifiers(warr->get_avg_oh_damage() * offhand_penalty));
        return;
    }
    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL) {
        increment_full_block();
        gain_rage(damage_after_modifiers(warr->get_avg_oh_damage() * offhand_penalty));
        return;
    }

    double damage_dealt = damage_after_modifiers(warr->get_random_non_normalized_oh_dmg() * offhand_penalty);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
        add_crit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);

        warr->melee_oh_white_critical_effect();
        return;
    }

    warr->melee_oh_white_hit_effect();

    if (result == PhysicalAttackResult::GLANCING) {
        damage_dealt = round(damage_dealt * roll->get_glancing_blow_dmg_penalty(oh_wpn_skill));
        add_glancing_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
        gain_rage(damage_dealt);
        return;
    }

    damage_dealt = round(damage_dealt);
    add_hit_dmg(static_cast<int>(damage_dealt), resource_cost, 0);
    gain_rage(damage_dealt);
}

void OffhandAttackWarrior::prepare_set_of_combat_iterations_spell_specific() {
    if (pchar->get_equipment()->get_offhand() == nullptr)
        return;

    this->icon = "Assets/items/" + pchar->get_equipment()->get_offhand()->get_value("icon");
    this->cooldown->base = pchar->get_stats()->get_oh_wpn_speed();
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(name, icon);

    reset();
}

void OffhandAttackWarrior::gain_rage(const double damage_dealt) {
    const unsigned rage_gained = warr->rage_gained_from_dd(static_cast<unsigned>(damage_dealt));
    const unsigned before = warr->get_resource_level(ResourceType::Rage);

    warr->gain_rage(rage_gained);

    const unsigned gain_after_cap = warr->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}
