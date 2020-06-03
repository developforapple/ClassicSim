#include "MultiShot.h"
#include <QObject>
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Hunter.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

MultiShot::MultiShot(Hunter* pchar, CooldownControl* cooldown_control) :
    Spell(QObject::tr("Multi-Shot"), "Assets/ability/Ability_upgrademoonglaive.png", pchar, cooldown_control, RestrictedByGcd::Yes, ResourceType::Mana, 230),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Efficiency"), 5, DisabledAtZero::No),
                                                 new TalentRequirerInfo(QObject::tr("Mortal Shots"), 5, DisabledAtZero::No),
                                                 new TalentRequirerInfo(QObject::tr("Barrage"), 3, DisabledAtZero::No)}),
    SetBonusRequirer({QObject::tr("Giantstalker Armor"), QObject::tr("Cryptstalker Armor")}),
    ItemModificationRequirer({16463, 16571, 22862, 23279}),
    hunter(pchar),
    efficiency_ranks({1.0, 0.98, 0.96, 0.94, 0.92, 0.90}),
    mortal_shots_ranks({0.0, 0.06, 0.12, 0.18, 0.24, 0.30}),
    barrage_ranks({1.0, 1.05, 1.10, 1.15}) {
    resource_base = resource_cost;
}

void MultiShot::spell_effect() {
    const unsigned wpn_skill = pchar->get_ranged_wpn_skill();
    const int result = roll->get_ranged_ability_result(wpn_skill, pchar->get_stats()->get_ranged_crit_chance());

    cooldown->add_gcd_event();
    cooldown->add_spell_cd_event();
    pchar->lose_mana(get_resource_cost());

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        return;
    }

    double damage_dealt = damage_after_modifiers(pchar->get_random_normalized_ranged_dmg() + 150 + hunter->get_normalized_projectile_dmg_bonus())
                          * barrage_mod * giantstalker_bonus * pvp_gloves_bonus;

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= pchar->get_stats()->get_ranged_ability_crit_dmg_mod() + mortal_shots_bonus;
        add_crit_dmg(static_cast<int>(round(damage_dealt)), get_resource_cost(), 0);
        pchar->ranged_yellow_hit_effect();
        add_adrenaline_rush_statistics();
        return;
    }

    pchar->ranged_yellow_hit_effect();
    add_hit_dmg(static_cast<int>(round(damage_dealt)), get_resource_cost(), 0);
}

void MultiShot::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QObject::tr("Multi-Shot"), icon);
}

void MultiShot::add_adrenaline_rush_statistics() {
    const unsigned before_gain = hunter->get_resource_level(ResourceType::Mana);
    hunter->gain_mana(adrenaline_rush);

    const unsigned delta = hunter->get_resource_level(ResourceType::Mana) - before_gain;

    if (delta > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, delta);
}

void MultiShot::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Efficiency"))
        resource_cost = static_cast<unsigned>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == QObject::tr("Mortal Shots"))
        mortal_shots_bonus = mortal_shots_ranks[curr];
    if (talent_name == QObject::tr("Barrage"))
        barrage_mod = barrage_ranks[curr];
}

void MultiShot::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Efficiency"))
        resource_cost = static_cast<unsigned>(round(resource_base * efficiency_ranks[curr]));
    if (talent_name == QObject::tr("Mortal Shots"))
        mortal_shots_bonus = mortal_shots_ranks[curr];
    if (talent_name == QObject::tr("Barrage"))
        barrage_mod = barrage_ranks[curr];
}

void MultiShot::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Giantstalker Armor")) {
        switch (set_bonus) {
        case 8:
            giantstalker_bonus = 1.15;
            break;
        default:
            check(false, "MultiShot::activate_set_bonus_effect reached end of switch");
        }
    } else if (set_name == QObject::tr("Cryptstalker Armor")) {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 50;
            break;
        case 8:
            resource_cost -= 20;
            break;
        default:
            check(false, "MultiShot::activate_set_bonus_effect reached end of switch");
        }
    }
}

void MultiShot::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Giantstalker Armor")) {
        switch (set_bonus) {
        case 8:
            giantstalker_bonus = 1.0;
            break;
        default:
            check(false, "MultiShot::deactivate_set_bonus_effect reached end of switch");
        }
    } else if (set_name == QObject::tr("Cryptstalker Armor")) {
        switch (set_bonus) {
        case 6:
            adrenaline_rush = 0;
            break;
        case 8:
            resource_cost += 20;
            break;
        default:
            check(false, "MultiShot::deactivate_set_bonus_effect reached end of switch");
        }
    }
}

void MultiShot::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 16463:
    case 16571:
    case 22862:
    case 23279:
        pvp_gloves_bonus = 1.03;
        break;
    default:
        check(false, "MultiShot::activate_item_effect reached end of switch");
    }
}

void MultiShot::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 16463:
    case 16571:
    case 22862:
    case 23279:
        pvp_gloves_bonus = 1.0;
        break;
    default:
        check(false, "MultiShot::deactivate_item_effect reached end of switch");
    }
}
