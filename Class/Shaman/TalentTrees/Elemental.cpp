#include "Elemental.h"
#include <QObject>
#include "Shaman.h"
#include "ShamanSpells.h"
#include "SpellRankGroup.h"
#include "TalentStatIncrease.h"

Elemental::Elemental(Shaman* shaman) :
    TalentTree(QObject::tr("Elemental"), "Assets/shaman/shaman_elemental.jpg"), shaman(shaman), spells(static_cast<ShamanSpells*>(shaman->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Convection"), "1ML"},           {QObject::tr("Concussion"), "1MR"},        {QObject::tr("Earth's Grasp"), "2LL"},         {QObject::tr("Elemental Warding"), "2ML"},
        {QObject::tr("Call of Flame"), "2MR"},        {QObject::tr("Elemental Focus"), "3LL"},   {QObject::tr("Reverberation"), "3ML"},         {QObject::tr("Call of Thunder"), "3MR"},
        {QObject::tr("Improved Fire Totems"), "4LL"}, {QObject::tr("Eye of the Storm"), "4ML"},  {QObject::tr("Elemental Devastation"), "4RR"}, {QObject::tr("Storm Reach"), "5LL"},
        {QObject::tr("Elemental Fury"), "5ML"},       {QObject::tr("Lightning Mastery"), "6MR"}, {QObject::tr("Elemental Mastery"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {};
    add_convection(tier1);
    add_concussion(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL",
                                   new Talent(shaman, this, QObject::tr("Earth's Grasp"), "2LL", "Assets/spell/Spell_nature_stoneclawtotem.png", 2,
                                              QObject::tr("Increases the health of your Stoneclaw Totem by %1% and the radius of your Earthbind Totem by %2%."),
                                              QVector<QPair<unsigned, unsigned>> {{25, 25}, {10, 10}})},
                                  {"2ML", new Talent(shaman, this, QObject::tr("Elemental Warding"), "2ML", "Assets/spell/Spell_nature_spiritarmor.png", 3,
                                                     QObject::tr("Reduces damage taken  from Fire, Frost and Nature effects by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{4, 3}})},
                                  {"2MR",
                                   new Talent(shaman, this, QObject::tr("Call of Flame"), "2MR", "Assets/spell/Spell_fire_immolation.png", 3,
                                              QObject::tr("Increases the damage done by your Fire Totems by %1%."), QVector<QPair<unsigned, unsigned>> {{5, 5}})}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {
        {"3ML", new Talent(shaman, this, QObject::tr("Reverberation"), "3ML", "Assets/spell/Spell_frost_frostward.png", 5,
                           QObject::tr("Reduces the cooldown of your Shock spells by %1 sec."), QVector<QPair<double, double>> {{0.2, 0.2}})}};
    add_elemental_focus(tier3);
    add_call_of_thunder(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL", new Talent(shaman, this, QObject::tr("Improved Fire Totems"), "4LL", "Assets/spell/Spell_fire_sealoffire.png", 2,
                                                     QObject::tr("Reduces the delay before your Fire Nova Totem activates by %1 sec. and decreases the threat "
                                                     "generated by your Magma Totem by %2%."),
                                                     QVector<QPair<unsigned, unsigned>> {{1, 1}, {25, 25}})}};
    add_eye_of_storm(tier4);
    add_elemental_devastation(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL", new Talent(shaman, this, QObject::tr("Storm Reach"), "5LL", "Assets/spell/Spell_nature_stormreach.png", 2,
                                                     QObject::tr("Increases the range of your Lightning Bolt and Chain Lightning spells by %1 yards."),
                                                     QVector<QPair<unsigned, unsigned>> {{3, 3}})},
                                  {"5ML", new Talent(shaman, this, QObject::tr("Elemental Fury"), "5ML", "Assets/spell/Spell_fire_volcano.png", 1,
                                                     QObject::tr("Increases the critical strike damage bonus of your Searing, Magma, and Fire Nova Totems and "
                                                     "your Fire, Frost, and Nature spells by 100%."),
                                                     QVector<QPair<unsigned, unsigned>> {})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_lightning_mastery(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Talent(shaman, this, QObject::tr("Elemental Mastery"), "7ML", "Assets/spell/Spell_nature_wispheal.png", 1,
                                                     QObject::tr("When activated, this spell gives your next Fire, Frost, or Nature damage spell a 100% critical "
                                                     "strike chance and reduces the mana cost by 100%."),
                                                     QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["6MR"]->talent);
    talents["6MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Elemental::add_convection(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(shaman, QObject::tr("Convection"), "1ML", "Assets/spell/Spell_nature_wispsplode.png", 5,
                                    QObject::tr("Reduces the mana cost of your Shock, Lightning Bolt, and Chain Lightning spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name("Lightning Bolt")});

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_concussion(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(shaman, QObject::tr("Concussion"), "1MR", "Assets/spell/Spell_fire_fireball.png", 5,
                                    QObject::tr("Increases the damage done by your Lightning Bolt, Chain Lightning and Shock spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name("Lightning Bolt")});

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_elemental_focus(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(shaman, QObject::tr("Elemental Focus"), "3LL", "Assets/spell/Spell_shadow_manaburn.png", 1,
                                    QObject::tr("Gives you a 10% chance to enter a Clearcasting state after casting any Fire, Frost, or Nature damage spell. The "
                                    "Clearcasting state reduces the mana cost of your next damage spell by 100%."),
                                    QVector<QPair<unsigned, unsigned>> {}, {}, {}, QVector<Proc*> {spells->get_clearcasting()});

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_call_of_thunder(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Increases the critical strike chance of your Lightning Bolt and Chain Lightning spells by an additional %1%.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(1)}, {1, base_str.arg(1)}, {2, base_str.arg(2)},
                                               {3, base_str.arg(3)}, {4, base_str.arg(4)}, {5, base_str.arg(6)}};
    Talent* talent = new Talent(shaman, this, QObject::tr("Call of Thunder"), "3MR", "Assets/spell/Spell_nature_callstorm.png", 5, rank_descriptions,
                                QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Lightning Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_eye_of_storm(QMap<QString, Talent*>& talent_tier) {
    QString base_str = QObject::tr("Gives you a %1% chance to gain the Focused Casting effect that lasts for 6 sec after being the victim of a melee or ranged "
                       "critical strike. The Focused Casting effect prevents you from losing casting time when taking damage.");
    QMap<unsigned, QString> rank_descriptions {{0, base_str.arg(33)}, {1, base_str.arg(33)}, {2, base_str.arg(66)}, {3, base_str.arg(100)}};
    Talent* talent = new Talent(shaman, this, QObject::tr("Eye of the Storm"), "4ML", "Assets/spell/Spell_nature_eyeofthestorm.png", 3, rank_descriptions);

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_elemental_devastation(QMap<QString, Talent*>& talent_tier) {
    Talent* talent
        = get_new_talent(shaman, QObject::tr("Elemental Devastation"), "4RR", "Assets/spell/Spell_fire_elementaldevastation.png", 3,
                         QObject::tr("Your offensive spell crits will increase your chance to get a critical strike with melee attacks by %1% for 10 sec."),
                         QVector<QPair<unsigned, unsigned>> {{3, 3}}, {}, {spells->get_elemental_devastation()});

    add_talent_to_tier(talent_tier, talent);
}

void Elemental::add_lightning_mastery(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(shaman, QObject::tr("Lightning Mastery"), "6MR", "Assets/spell/Spell_lightning_lightningbolt01.png", 5,
                                   QObject::tr("Reduces the cast time of your Lightning Bolt and Chain Lightning spells by %1 sec."),
                                    QVector<QPair<double, double>> {{0.2, 0.2}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Lightning Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}
