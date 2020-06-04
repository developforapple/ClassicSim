#include "Eviscerate.h"
#include <QObject>
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Equipment.h"
#include "Random.h"
#include "RelentlessStrikes.h"
#include "Rogue.h"
#include "Ruthlessness.h"
#include "Utils/Check.h"
#include "Weapon.h"

Eviscerate::Eviscerate(Rogue* rogue) :
    Spell(QObject::tr("Eviscerate"),
          "Assets/ability/Ability_rogue_eviscerate.png",
          rogue,
          new CooldownControl(rogue, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Energy,
          35),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Aggression"), 3, DisabledAtZero::No),
                                                 new TalentRequirerInfo(QObject::tr("Improved Eviscerate"), 3, DisabledAtZero::No)}),
    SetBonusRequirer({QObject::tr("Deathdealer's Embrace")}),
    rogue(rogue),
    evisc_range(new Random(904, 1012)),
    damage_ranges_per_combo_point({
        QPair<unsigned, unsigned>(224, 332),
        QPair<unsigned, unsigned>(394, 502),
        QPair<unsigned, unsigned>(564, 672),
        QPair<unsigned, unsigned>(734, 842),
        QPair<unsigned, unsigned>(904, 1012),
    }),
    aggression_modifiers({1.0, 1.02, 1.04, 1.06}),
    imp_evisc_modifiers({1.0, 1.05, 1.10, 1.15}) {}

Eviscerate::~Eviscerate() {
    delete evisc_range;
    delete cooldown;
}

SpellStatus Eviscerate::is_ready_spell_specific() const {
    return rogue->get_combo_points() > 0 ? SpellStatus::Available : SpellStatus::InsufficientComboPoints;
}

void Eviscerate::spell_effect() {
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

    set_evisc_range();
    double ap_modifier = rogue->get_stats()->get_melee_ap() * (rogue->get_combo_points() * 0.03);
    double damage_dealt = damage_after_modifiers((evisc_range->get_roll() + ap_modifier) * total_dmg_modifier);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * rogue->get_stats()->get_melee_ability_crit_dmg_mod());
        rogue->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    } else if (result == PhysicalAttackResult::HIT) {
        rogue->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    rogue->lose_energy(resource_cost);

    if (rogue->get_relentless_strikes()->is_enabled()) {
        rogue->get_relentless_strikes()->set_current_combo_points(rogue->get_combo_points());
        if (rogue->get_relentless_strikes()->check_proc_success())
            rogue->get_relentless_strikes()->perform();
    }

    rogue->spend_combo_points();

    if (rogue->get_ruthlessness()->is_enabled() && rogue->get_ruthlessness()->check_proc_success())
        rogue->get_ruthlessness()->perform();
}

void Eviscerate::set_evisc_range() {
    int index = static_cast<int>(rogue->get_combo_points()) - 1;
    check((index >= 0 && index <= damage_ranges_per_combo_point.size() - 1), "Index out of range");

    unsigned min = damage_ranges_per_combo_point[index].first;
    unsigned max = damage_ranges_per_combo_point[index].second;

    evisc_range->set_new_range(min, max);
}

void Eviscerate::update_dmg_modifier() {
    this->total_dmg_modifier = 1 * imp_evisc_modifier * aggression_modifier * deathdealer_modifier;
}

void Eviscerate::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Improved Eviscerate"))
        imp_evisc_modifier = imp_evisc_modifiers[curr];
    else if (talent_name == QObject::tr("Aggression"))
        aggression_modifier = aggression_modifiers[curr];

    update_dmg_modifier();
}

void Eviscerate::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Improved Eviscerate"))
        imp_evisc_modifier = imp_evisc_modifiers[curr];
    else if (talent_name == QObject::tr("Aggression"))
        aggression_modifier = aggression_modifiers[curr];

    update_dmg_modifier();
}

void Eviscerate::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Deathdealer's Embrace")) {
        switch (set_bonus) {
        case 5:
            deathdealer_modifier = 1.15;
            break;
        default:
            check(false, "Eviscerate::activate_set_bonus_effect reached end of switch");
        }
    }
}

void Eviscerate::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Deathdealer's Embrace")) {
        switch (set_bonus) {
        case 5:
            deathdealer_modifier = 1.0;
            break;
        default:
            check(false, "Eviscerate::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
