#include "RapidFireBuff.h"
#include <QObject>
#include "CharacterStats.h"
#include "Hunter.h"
#include "Utils/Check.h"

RapidFireBuff::RapidFireBuff(Character* pchar) :
    SelfBuff(pchar, QObject::tr("Rapid Fire"), "Assets/ability/Ability_hunter_runningshot.png", 15, 0), SetBonusRequirer({QObject::tr("Cryptstalker Armor")}) {}

void RapidFireBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_ranged_attack_speed(40);
}

void RapidFireBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_ranged_attack_speed(40);
}

void RapidFireBuff::activate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Cryptstalker Armor")) {
        switch (set_bonus) {
        case 2:
            duration += 4;
            break;
        default:
            check(false, "RapidFireBuff::activate_set_bonus_effect reached end of switch");
        }
    }
}

void RapidFireBuff::deactivate_set_bonus_effect(const QString& set_name, const int set_bonus) {
    if (set_name == QObject::tr("Cryptstalker Armor")) {
        switch (set_bonus) {
        case 2:
            duration -= 4;
            break;
        default:
            check(false, "RapidFireBuff::deactivate_set_bonus_effect reached end of switch");
        }
    }
}
