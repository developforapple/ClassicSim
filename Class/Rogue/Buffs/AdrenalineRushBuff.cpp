#include "AdrenalineRushBuff.h"
#include <QObject>
#include "Energy.h"
#include "Rogue.h"

AdrenalineRushBuff::AdrenalineRushBuff(Rogue* rogue) :
    SelfBuff(rogue, QObject::tr("Adrenaline Rush"), "Assets/spell/Spell_shadow_shadowworddominate.png", 15, 0), rogue(rogue) {}

AdrenalineRushBuff::~AdrenalineRushBuff() {
    if (is_enabled())
        disable_buff();
}

void AdrenalineRushBuff::buff_effect_when_applied() {
    rogue->get_energy()->increase_energy_per_tick();
}

void AdrenalineRushBuff::buff_effect_when_removed() {
    rogue->get_energy()->decrease_energy_per_tick();
}
