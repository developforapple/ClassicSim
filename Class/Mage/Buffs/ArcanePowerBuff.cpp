#include "ArcanePowerBuff.h"
#include <QObject>
#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Spell.h"
#include "SpellRankGroup.h"

ArcanePowerBuff::ArcanePowerBuff(Character* pchar) :
    SelfBuff(pchar, QObject::tr("Arcane Power"), "Assets/spell/Spell_nature_lightning.png", 15, 0),
    affected_spells({
        QObject::tr("Blizzard"),
        QObject::tr("Frostbolt"),
        QObject::tr("Arcane Explosion"),
        QObject::tr("Fire Blast"),
        QObject::tr("Scorch"),
        QObject::tr("Fireball"),
        QObject::tr("Pyroblast"),
        QObject::tr("Blast Wave"),
        QObject::tr("Frost Nova"),
        QObject::tr("Flamestrike"),
        QObject::tr("Cone of Cold"),
        QObject::tr("Arcane Missiles"),
    }) {}

void ArcanePowerBuff::buff_effect_when_applied() {
    pchar->get_stats()->increase_magic_school_damage_mod(30);

    for (const auto& spell_name : affected_spells) {
        SpellRankGroup* group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
        if (group == nullptr)
            continue;

        for (const auto& spell : group->spell_group)
            spell->increase_resource_cost_modifier(30);
    }
}

void ArcanePowerBuff::buff_effect_when_removed() {
    pchar->get_stats()->decrease_magic_school_damage_mod(30);

    for (const auto& spell_name : affected_spells) {
        SpellRankGroup* group = pchar->get_spells()->get_spell_rank_group_by_name(spell_name);
        if (group == nullptr)
            continue;

        for (const auto& spell : group->spell_group)
            spell->decrease_resource_cost_modifier(30);
    }
}
