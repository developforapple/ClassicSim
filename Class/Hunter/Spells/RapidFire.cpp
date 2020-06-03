#include "RapidFire.h"
#include <QObject>
#include "Character.h"
#include "CooldownControl.h"
#include "RapidFireBuff.h"
#include "Utils/Check.h"

RapidFire::RapidFire(Character* pchar) :
    Spell(QObject::tr("Rapid Fire"),
          "Assets/ability/Ability_hunter_runningshot.png",
          pchar,
          new CooldownControl(pchar, 300.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          100),
    SetBonusRequirer({QObject::tr("Striker's Garb")}),
    rapid_fire(new RapidFireBuff(pchar)) {
    rapid_fire->enable_buff();
}

RapidFire::~RapidFire() {
    if (rapid_fire->is_enabled())
        rapid_fire->disable_buff();

    delete rapid_fire;
    delete cooldown;
}

RapidFireBuff* RapidFire::get_rapid_fire_buff() const {
    return this->rapid_fire;
}

void RapidFire::spell_effect() {
    cooldown->add_gcd_event();
    pchar->lose_mana(get_resource_cost());
    rapid_fire->apply_buff();
}

void RapidFire::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Striker's Garb")) {
        switch (set_bonus) {
        case 5:
            cooldown->base -= 120.0;
            break;
        default:
            check(false, "RapidFire:activate_set_bonus_effect reached end of switch");
        }
    }
}

void RapidFire::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name ==QObject::tr("Striker's Garb")) {
        switch (set_bonus) {
        case 5:
            cooldown->base -= 120.0;
            break;
        default:
            check(false, "RapidFire::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
