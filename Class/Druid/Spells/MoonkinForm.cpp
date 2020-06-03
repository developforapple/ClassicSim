#include "MoonkinForm.h"
#include <QObject>
#include <cmath>

#include "CooldownControl.h"
#include "Druid.h"
#include "MoonkinFormBuff.h"
#include "NoEffectSelfBuff.h"

MoonkinForm::MoonkinForm(Druid* druid, MoonkinFormBuff* buff) :
    Spell(QObject::tr("Moonkin Form"),
          "Assets/spell/Spell_nature_forceofnature.png",
          druid,
          new CooldownControl(druid, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          100),
    TalentRequirer(
        {new TalentRequirerInfo(QObject::tr("Moonkin Form"), 1, DisabledAtZero::Yes), new TalentRequirerInfo(QObject::tr("Natural Shapeshifter"), 3, DisabledAtZero::No)}),
    druid(druid),
    buff(buff),
    base_resource_cost(resource_cost) {
    enabled = false;
}

MoonkinForm::~MoonkinForm() {
    delete cooldown;
}

SpellStatus MoonkinForm::is_ready_spell_specific() const {
    if (druid->get_current_form() == DruidForm::Moonkin)
        return SpellStatus::InMoonkinForm;

    return SpellStatus::Available;
}

void MoonkinForm::spell_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(resource_cost)));
    druid->switch_to_form(DruidForm::Moonkin);
}

void MoonkinForm::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == QObject::tr("Natural Shapeshifter"))
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * natural_shapeshifter_ranks[curr]));
}

void MoonkinForm::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
