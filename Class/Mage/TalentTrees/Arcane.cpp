#include "Arcane.h"
#include <QObject>
#include "Mage.h"
#include "MageSpells.h"
#include "Talent.h"
#include "TalentStatIncrease.h"

Arcane::Arcane(Mage* mage) : TalentTree(QObject::tr("Arcane"), "Assets/mage/mage_arcane.jpg"), mage(mage), spells(static_cast<MageSpells*>(mage->get_spells())) {
    talent_names_to_locations = {
        {QObject::tr("Arcane Subtlety"), "1LL"},   {QObject::tr("Arcane Focus"), "1ML"},         {QObject::tr("Improved Arcane Missiles"), "1MR"}, {QObject::tr("Wand Specialization"), "2LL"},
        {QObject::tr("Magic Absorption"), "2ML"},  {QObject::tr("Arcane Concentration"), "2MR"}, {QObject::tr("Magic Attunement"), "3LL"},         {QObject::tr("Improved Arcane Explosion"), "3ML"},
        {QObject::tr("Arcane Resilience"), "3MR"}, {QObject::tr("Improved Mana Shield"), "4LL"}, {QObject::tr("Improved Counterspell"), "4ML"},    {QObject::tr("Arcane Meditation"), "4RR"},
        {QObject::tr("Presence of Mind"), "5ML"},  {QObject::tr("Arcane Mind"), "5MR"},          {QObject::tr("Arcane Instability"), "6ML"},       {QObject::tr("Arcane Power"), "7ML"},
    };

    QMap<QString, Talent*> tier1 {
        {"1MR", new Talent(mage, this, QObject::tr("Improved Arcane Missiles"), "1MR", "Assets/spell/Spell_nature_starfall.png", 5,
                           QObject::tr("Gives you a %1% chance to avoid interruption caused by damage while channeling Arcane Missiles."),
                           QVector<QPair<unsigned, unsigned>> {{20, 20}})}};
    add_arcane_subtlety(tier1);
    add_arcane_focus(tier1);
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {
        {"2LL", new Talent(mage, this, QObject::tr("Wand Specialization"), "2LL", "Assets/items/Inv_wand_01.png", 2, QObject::tr("Increases your damage with Wands by %1%."),
                           QVector<QPair<unsigned, unsigned>> {{13, 12}})},
        {"2ML",
         new Talent(mage, this, QObject::tr("Magic Absorption"), "2ML", "Assets/spell/Spell_nature_astralrecalgroup.png", 5,
                    QObject::tr("Increases all resistances by %1 and causes all spells you fully resist to restore %2% of your total mana. 1 sec. cooldown."),
                    QVector<QPair<unsigned, unsigned>> {{2, 2}, {1, 1}})}};
    add_arcane_concentration(tier2);
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new Talent(mage, this, QObject::tr("Magic Attunement"), "3LL", "Assets/items/Spell_nature_abolishmagic.png", 2,
                                                     QObject::tr("Increases the effect of your Amplify Magic and Dampen Magic spells by %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{25, 25}})},
                                  {"3ML", new Talent(mage, this, QObject::tr("Improved Arcane Explosion"), "3ML", "Assets/spell/Spell_nature_wispsplode.png", 3,
                                                     QObject::tr("Increases the critical strike chance of your Arcane Explosion spell by an additional %1%."),
                                                     QVector<QPair<unsigned, unsigned>> {{2, 2}})},
                                  {"3MR", new Talent(mage, this, QObject::tr("Arcane Resilience"), "3MR", "Assets/spell/Spell_arcane_arcaneresilience.png", 1,
                                                     QObject::tr("Increases your armor by an amount equal to 50% of your Intellect."),
                                                     QVector<QPair<unsigned, unsigned>> {})}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4LL",
                                   new Talent(mage, this, QObject::tr("Improved Mana Shield"), "4LL", "Assets/spell/Spell_shadow_detectlesserinvisibility.png", 2,
                                              QObject::tr("Decreases the mana lost per point of damage taken when Mana Shield is active by %1%."),
                                              QVector<QPair<unsigned, unsigned>> {{10, 10}})},
                                  {"4ML", new Talent(mage, this, QObject::tr("Improved Counterspell"), "4ML", "Assets/spell/Spell_frost_iceshock.png", 2,
                                                     QObject::tr("Gives your Counterspell a %1% chance to silence the target for 4 sec."),
                                                     QVector<QPair<unsigned, unsigned>> {{50, 50}})}};
    add_arcane_meditation(tier4);
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {
        {"5ML", new Talent(mage, this, QObject::tr("Presence of Mind"), "5ML", "Assets/spell/Spell_nature_enchantarmor.png", 1,
                           QObject::tr("When activated, your next Mage spell with a casting time less than 10 sec becomes an instant cast spell."),
                           QVector<QPair<unsigned, unsigned>> {})}};
    add_arcane_mind(tier5);
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {};
    add_arcane_instability(tier6);
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {};
    add_arcane_power(tier7);
    add_talents(tier7);

    talents["3MR"]->talent->set_bottom_child(talents["5MR"]->talent);
    talents["5MR"]->talent->set_parent(talents["3MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);

    talents["6ML"]->talent->set_bottom_child(talents["7ML"]->talent);
    talents["7ML"]->talent->set_parent(talents["6ML"]->talent);
}

void Arcane::add_arcane_subtlety(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(
        mage, this, QObject::tr("Arcane Subtlety"), "1LL", "Assets/spell/Spell_holy_dispelmagic.png", 2,
        QObject::tr("Reduces your target's resistance to all your spells by %1 and reduces the threat caused by your Arcane spells by %2%."),
        QVector<QPair<unsigned, unsigned>> {{5, 5}, {20, 20}}, QVector<QPair<TalentStat, unsigned>> {{TalentStat::TargetResistanceReduction, 5}});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_focus(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(mage, this, QObject::tr("Arcane Focus"), "1ML", "Assets/spell/Spell_holy_devotion.png", 5,
                                            QObject::tr("Reduces the chance that the opponent can resist your Arcane spells by %1%."),
                                            QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                            QVector<QPair<TalentStat, unsigned>> {{TalentStat::ArcaneHit, 200}});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_concentration(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Arcane Concentration"), "2MR", "Assets/spell/Spell_shadow_manaburn.png", 5,
                                    QObject::tr("Gives you a %1% chance of entering a Clearcasting state after any damage spell hits a target. The Clearcasting "
                                    "state reduces the mana cost of your next damage spell by 100%."),
                                    QVector<QPair<unsigned, unsigned>> {{2, 2}}, {}, {}, QVector<Proc*> {spells->get_clearcasting()});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_meditation(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(mage, this, QObject::tr("Arcane Meditation"), "4RR", "Assets/spell/Spell_shadow_siphonmana.png", 3,
                                            QObject::tr("Allows %1% of your Mana regeneration to continue while casting."),
                                            QVector<QPair<unsigned, unsigned>> {{5, 5}},
                                            QVector<QPair<TalentStat, unsigned>> {{TalentStat::BaseManaRegenWhileCasting, 5}});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_mind(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(mage, this, QObject::tr("Arcane Mind"), "5MR", "Assets/spell/Spell_shadow_charm.png", 5,
                                            QObject::tr("Increases your maximum Mana by %1%."), QVector<QPair<unsigned, unsigned>> {{2, 2}},
                                            QVector<QPair<TalentStat, unsigned>> {{TalentStat::MaxManaMod, 2}});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_instability(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = new TalentStatIncrease(mage, this, QObject::tr("Arcane Instability"), "6ML", "Assets/spell/Spell_shadow_teleport.png", 3,
                                            QObject::tr("Increases your spell damage and critical strike chance by %1%."),
                                            QVector<QPair<unsigned, unsigned>> {{1, 1}},
                                            QVector<QPair<TalentStat, unsigned>> {{TalentStat::SpellDmgMod, 1}, {TalentStat::SpellCrit, 100}});

    add_talent_to_tier(talent_tier, talent);
}

void Arcane::add_arcane_power(QMap<QString, Talent*>& talent_tier) {
    Talent* talent = get_new_talent(mage, QObject::tr("Arcane Power"), "7ML", "Assets/spell/Spell_nature_lightning.png", 1,
                                    QObject::tr("When activated, your spells deal 30% more damage while costing 30% more mana to cast. This effect lasts 15 sec."),
                                    QVector<QPair<unsigned, unsigned>>(),
                                    QVector<SpellRankGroup*> {spells->get_spell_rank_group_by_name(QObject::tr("Arcane Power"))});

    add_talent_to_tier(talent_tier, talent);
}
