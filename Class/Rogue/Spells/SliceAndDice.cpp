#include "SliceAndDice.h"
#include <QObject>
#include "CharacterStats.h"
#include "CooldownControl.h"
#include "Equipment.h"
#include "Random.h"
#include "RelentlessStrikes.h"
#include "Rogue.h"
#include "Ruthlessness.h"
#include "SliceAndDiceBuff.h"
#include "Utils/Check.h"
#include "Weapon.h"

SliceAndDice::SliceAndDice(Rogue* rogue) :
    Spell(QObject::tr("Slice and Dice"),
          "Assets/ability/Ability_rogue_slicedice.png",
          rogue,
          new CooldownControl(rogue, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Energy,
          25),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Improved Slice And Dice"), 3, DisabledAtZero::No)}),
    SetBonusRequirer({QObject::tr("Emblems of Veiled Shadows")}),
    rogue(rogue),
    buff(new SliceAndDiceBuff(rogue)) {
    buff->enable_buff();
}

SliceAndDice::~SliceAndDice() {
    if (buff->is_enabled())
        buff->disable_buff();

    delete buff;
    delete cooldown;
}

SpellStatus SliceAndDice::is_ready_spell_specific() const {
    return rogue->get_combo_points() > 0 ? SpellStatus::Available : SpellStatus::InsufficientComboPoints;
}

void SliceAndDice::spell_effect() {
    rogue->exit_stealth();

    cooldown->add_gcd_event();

    buff->update_duration(rogue->get_combo_points());
    buff->apply_buff();

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

void SliceAndDice::increase_talent_rank_effect(const QString&, const int curr) {
    buff->change_duration_modifier(curr);
}

void SliceAndDice::decrease_talent_rank_effect(const QString&, const int curr) {
    buff->change_duration_modifier(curr);
}

void SliceAndDice::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Emblems of Veiled Shadows")) {
        switch (set_bonus) {
        case 3:
            resource_cost -= 10;
            break;
        default:
            check(false, "SliceAndDice::activate_set_bonus_effect reached end of switch");
        }
    }
}

void SliceAndDice::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Emblems of Veiled Shadows")) {
        switch (set_bonus) {
        case 3:
            resource_cost += 10;
            break;
        default:
            check(false, "SliceAndDice::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
