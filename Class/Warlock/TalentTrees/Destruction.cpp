#include "Destruction.h"
#include <QObject>
#include "Talent.h"
#include "TalentStatIncrease.h"
#include "Warlock.h"
#include "WarlockSpells.h"

Destruction::Destruction(Warlock* warlock) :
    TalentTree(QObject::tr("Destruction"), "Assets/warlock/warlock_destruction.jpg"),
    warlock(warlock),
    spells(static_cast<WarlockSpells*>(warlock->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Improved Shadow Bolt"), "1ML"},
        {QObject::tr("Cataclysm"), "1MR"},
        {QObject::tr("Bane"), "2ML"},
        {QObject::tr("Aftermath"), "2MR"},
        {QObject::tr("Improved Firebolt"), "3LL"},
        {QObject::tr("Improved Lash of Pain"), "3ML"},
        {QObject::tr("Devastation"), "3MR"},
        {QObject::tr("Shadowburn"), "3RR"},
        {QObject::tr("Intensity"), "4LL"},
        {QObject::tr("Destructive Reach"), "4ML"},
        {QObject::tr("Improved Searing Pain"), "4RR"},
        {QObject::tr("Pyroclasm"), "5LL"},
        {QObject::tr("Improved Immolate"), "5ML"},
        {QObject::tr("Ruin"), "5MR"},
        {QObject::tr("Emberstorm"), "6MR"},
        {QObject::tr("Conflagrate"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {};
    add_cataclysm(tier1);
    add_improved_shadow_bolt(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2MR", new Talent(warlock, this, QObject::tr("Aftermath"), "2MR", "Assets/spell/Spell_fire_fire.png", 5,
                           QObject::tr("Gives your Destruction spells a %1% chance to daze the target for 5 sec."), QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_bane(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(warlock, this, QObject::tr("Improved Firebolt"), "3LL", "Assets/spell/Spell_fire_firebolt.png", 2,
                                                     QObject::tr("Reduces the casting time of your Imp's Firebolt spell by %1 sec."),
                                                     QVector<QPair<double, double>> {{0.5, 0.5}})},
                                  {"3ML", new Talent(warlock, this, QObject::tr("Improved Lash of Pain"), "3ML", "Assets/spell/Spell_shadow_curse.png", 2,
                                                     QObject::tr("Reduces the cooldown of your Succubus' Lash of Pain spell by %1 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {{3, 3}})},
                                  {
                                      "3RR",
                                      new Talent(warlock, this, QObject::tr("Shadowburn"), "3RR", "Assets/spell/Spell_shadow_scourgebuild.png", 1,
                                                 QObject::tr("Instantly blasts the target for 91 to 104 Shadow damage.  If the target dies within 5 sec of "
                                                 "Shadowburn, and yields experience or honor, the caster gains a Soul Shard."),
                                                 QVector<QPair<unsigned, unsigned>> {}),
                                  }};
    add_devastation(tier3);
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {
        {"4LL",
         new Talent(warlock, this, QObject::tr("Intensity"), "4LL", "Assets/spell/Spell_fire_lavaspawn.png", 2,
                    QObject::tr("Gives you a %1% chance to resist interruption caused by damage while channeling the Rain of Fire, Hellfire or Soul Fire spell."),
                    QVector<QPair<unsigned, unsigned>> {{35, 35}})},
        {"4ML", new Talent(warlock, this, QObject::tr("Destructive Reach"), "4ML", "Assets/spell/Spell_shadow_corpseexplode.png", 2,
                           QObject::tr("Increases the range of your Destruction spells by %1%."), QVector<QPair<unsigned, unsigned>> {{10, 10}})},
        {"4RR", new Talent(warlock, this, QObject::tr("Improved Searing Pain"), "4RR", "Assets/spell/Spell_fire_soulburn.png", 5,
                           QObject::tr("Increases the critical strike chance of your Searing Pain spell by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5LL",
                                   new Talent(warlock, this, QObject::tr("Pyroclasm"), "5LL", "Assets/spell/Spell_fire_volcano.png", 2,
                                              QObject::tr("Gives your Rain of Fire, Hellfire, and Soul Fire spells a %1% chance to stun the target for 3 sec."),
                                              QVector<QPair<unsigned, unsigned>> {{13, 13}})},
                                  {"5ML", new Talent(warlock, this, QObject::tr("Improved Immolate"), "5ML", "Assets/spell/Spell_fire_immolation.png", 5,
                                                     QObject::tr("Increases the initial damage of your Immolate spell by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{5, 5}})}};
    add_ruin(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_emberstorm(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {
        {"7ML", new Talent(warlock, this, QObject::tr("Conflagrate"), "7ML", "Assets/spell/Spell_fire_fireball.png", 1,
                           QObject::tr("Ignites a target that is already afflicted by Immolate, dealing 249 to 316 Fire damage and consuming the Immolate spell."),
                           QVector<QPair<unsigned, unsigned>>())}};
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["4LL"]->talent->set_bottom_child(talents["5LL"]->talent);
    talents["5LL"]->talent->set_parent(talents["4LL"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["5ML"]->talent);
}

void Destruction::add_improved_shadow_bolt(QMap<QString, Talent*>& talent_tier) {
    Talent* talent
        = get_new_talent(warlock, QObject::tr("Improved Shadow Bolt"), "1ML", "Assets/spell/Spell_shadow_shadowbolt.png", 5,
                         QObject::tr("Your Shadow Bolt critical strikes increase Shadow damage dealt to the target by %1% until 4 non-periodic damage sources "
                         "are applied.  Effect lasts a maximum of 12 sec."),
                         QVector<QPair<unsigned, unsigned>> {{4, 4}}, QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Shadow Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Destruction::add_cataclysm(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(warlock, QObject::tr("Cataclysm"), "1MR", "Assets/spell/Spell_fire_windsofwoe.png", 5,
                                    QObject::tr("Reduces the Mana cost of your Destruction spells by %1%."), QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Shadow Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Destruction::add_bane(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(warlock, QObject::tr("Bane"), "2ML", "Assets/spell/Spell_shadow_deathpact.png", 5,
                                    QObject::tr("Reduces the casting time of your Shadow Bolt and Immolate spells by %1 sec and your Soul Fire spell by %2 sec."),
                                    QVector<QPair<double, double>> {{0.1, 0.1}, {0.4, 0.4}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Shadow Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Destruction::add_devastation(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(warlock, QObject::tr("Devastation"), "3MR", "Assets/spell/Spell_fire_flameshock.png", 5,
                                    QObject::tr("Increases the critical strike chance of your Destruction spells by %1%."),
                                    QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Shadow Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Destruction::add_ruin(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(warlock, QObject::tr("Ruin"), "5MR", "Assets/spell/Spell_shadow_shadowwordpain.png", 1,
                                    QObject::tr("Increases the critical strike damage bonus of your Destruction spells by 100%."),
                                    QVector<QPair<unsigned, unsigned>> {},
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Shadow Bolt"))});

    add_talent_to_tier(talent_tier, talent);
}

void Destruction::add_emberstorm(QMap<QString, Talent*>& talent_tier) {
    auto talent = new TalentStatIncrease(warlock, this, QObject::tr("Emberstorm"), "6MR", "Assets/spell/Spell_fire_selfdestruct.png", 5,
                                         QObject::tr("Increases the damage done by your Fire spells by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                         QVector<QPair<TalentStat, unsigned>> {
                                             {TalentStat::FireDmgMod, 2},
                                         });

    add_talent_to_tier(talent_tier, talent);
}
