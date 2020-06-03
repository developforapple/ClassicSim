#include "HolyStrength.h"
#include <QObject>
#include "Character.h"
#include "CharacterStats.h"

HolyStrength::HolyStrength(Character* pchar, const QString& weapon_side) :
    SelfBuff(pchar, QObject::tr("Holy Strength ") + weapon_side, "Assets/spell/Spell_holy_blessingofstrength.png", 15, 0) {}

void HolyStrength::buff_effect_when_applied() {
    pchar->get_stats()->increase_strength(100);
}

void HolyStrength::buff_effect_when_removed() {
    pchar->get_stats()->decrease_strength(100);
}
