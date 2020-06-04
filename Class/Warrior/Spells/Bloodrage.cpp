#include "Bloodrage.h"
#include <QObject>
#include "Buff.h"
#include "ClassStatistics.h"
#include "CooldownControl.h"
#include "Engine.h"
#include "StatisticsResource.h"
#include "Warrior.h"

Bloodrage::Bloodrage(Warrior* warrior) :
    PeriodicResourceGainSpell(QObject::tr("Bloodrage"),
                              "Assets/ability/Ability_racial_bloodrage.png",
                              warrior,
                              RestrictedByGcd::No,
                              1.0,
                              10,
                              {{ResourceType::Rage, 1}}),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Improved Bloodrage"), 2, DisabledAtZero::No)}),
    warrior(warrior) {
    delete cooldown;
    cooldown = new CooldownControl(warrior, 60.0);
    enabled = true;
    marker_buff->enable_buff();
}

void Bloodrage::new_application_effect() {
    cooldown->add_spell_cd_event();

    gain_rage(immediate_rage_gain);
}

SpellStatus Bloodrage::is_ready_spell_specific() const {
    return warrior->in_defensive_stance() ? SpellStatus::InDefensiveStance : SpellStatus::Available;
}

void Bloodrage::increase_talent_rank_effect(const QString&, const int curr) {
    this->immediate_rage_gain = talent_ranks[curr];
}

void Bloodrage::decrease_talent_rank_effect(const QString&, const int curr) {
    this->immediate_rage_gain = talent_ranks[curr];
}

void Bloodrage::gain_rage(const unsigned rage_gain) {
    const unsigned before = warrior->get_resource_level(ResourceType::Rage);

    warrior->gain_rage(rage_gain);

    const unsigned gain_after_cap = warrior->get_resource_level(ResourceType::Rage) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Rage, gain_after_cap);
}
