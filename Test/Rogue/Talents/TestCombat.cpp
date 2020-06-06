#include "TestCombat.h"

#include <cassert>

#include "Combat.h"
#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"

TestCombat::TestCombat(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestCombat::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestCombat::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestCombat::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Lightning Reflexes")));

    assert(increment(QObject::tr("Lightning Reflexes"), 5));
    // 5 points
    assert(!increment(QObject::tr("Lightning Reflexes")));
    assert(decrement(QObject::tr("Lightning Reflexes")));
    assert(increment(QObject::tr("Lightning Reflexes")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Lightning Reflexes")));
    assert(increment(QObject::tr("Improved Gouge")));
    assert(decrement(QObject::tr("Lightning Reflexes")));
    assert(!decrement(QObject::tr("Lightning Reflexes")));
    assert(!decrement(QObject::tr("Improved Gouge")));

    assert(increment(QObject::tr("Lightning Reflexes")));
    assert(decrement(QObject::tr("Improved Gouge")));
    assert(decrement(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Lightning Reflexes"), 5));

    // 0 points spent, make Dual-Wield Specialization "available" via other talents
    assert(increment(QObject::tr("Improved Gouge"), 3));
    assert(increment(QObject::tr("Improved Sinister Strike"), 2));
    assert(increment(QObject::tr("Improved Backstab"), 3));
    assert(increment(QObject::tr("Deflection"), 5));
    assert(increment(QObject::tr("Improved Sprint"), 2));

    // Assert cannot spend points into Dual-Wield Specialization if 5/5 Precision is missing
    assert(!increment(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Precision")));
    assert(!increment(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Precision")));
    assert(!increment(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Precision")));
    assert(!increment(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Precision")));
    assert(!increment(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Precision")));

    // Assert cannot remove points from Precision once points are spent in Dual-Wield Specialization
    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Precision")));
    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Precision")));
    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Precision")));
    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Precision")));
    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Precision")));

    // 20 points spent
    assert(decrement(QObject::tr("Dual Wield Specialization"), 4));
    assert(decrement(QObject::tr("Improved Backstab"), 1));
    assert(tree_has_points(20));

    assert(increment(QObject::tr("Blade Flurry")));

    // Cannot decrement lower tiers
    assert(!decrement(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Improved Sprint")));
    assert(!decrement(QObject::tr("Improved Backstab")));
    assert(!decrement(QObject::tr("Lightning Reflexes")));

    // Try shifting points in T1
    assert(increment(QObject::tr("Lightning Reflexes")));
    assert(decrement(QObject::tr("Improved Sinister Strike")));
    assert(!decrement(QObject::tr("Improved Sinister Strike")));
    assert(!decrement(QObject::tr("Improved Gouge")));

    assert(increment(QObject::tr("Improved Sinister Strike")));
    assert(decrement(QObject::tr("Improved Gouge")));

    // Try shifting points in T3
    assert(increment(QObject::tr("Riposte")));
    assert(decrement(QObject::tr("Improved Sprint")));
    assert(!decrement(QObject::tr("Riposte")));
    assert(!decrement(QObject::tr("Improved Sprint")));

    assert(increment(QObject::tr("Improved Sprint")));
    assert(decrement(QObject::tr("Riposte")));

    // Try shifting points in T4
    assert(!decrement(QObject::tr("Dual Wield Specialization")));
    assert(increment(QObject::tr("Dagger Specialization")));
    assert(decrement(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Dagger Specialization")));

    assert(increment(QObject::tr("Dual Wield Specialization")));
    assert(decrement(QObject::tr("Dagger Specialization")));

    // Assert cannot remove parent (Blade Flurry) when child (Weapon Expertise) is active although points allow
    assert(tree_has_points(21));
    assert(increment(QObject::tr("Dagger Specialization"), 4));
    assert(increment(QObject::tr("Weapon Expertise")));
    assert(!decrement(QObject::tr("Blade Flurry")));
    assert(increment(QObject::tr("Weapon Expertise")));

    // Assert lower tiers cannot be decremented with Adrenaline Rush enabled (31 pts)
    assert(increment(QObject::tr("Aggression"), 3));
    assert(tree_has_points(30));
    assert(increment(QObject::tr("Adrenaline Rush")));
    assert(!decrement(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Improved Sprint")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Improved Sinister Strike")));

    assert(decrement(QObject::tr("Adrenaline Rush")));
}

void TestCombat::test_clearing_tree_after_filling() {
    assert(increment(QObject::tr("Improved Gouge"), 3));
    assert(increment(QObject::tr("Lightning Reflexes"), 5));
    assert(increment(QObject::tr("Improved Backstab"), 3));
    assert(increment(QObject::tr("Deflection"), 5));
    assert(increment(QObject::tr("Precision"), 5));
    assert(increment(QObject::tr("Endurance"), 2));
    assert(increment(QObject::tr("Improved Sprint"), 2));
    assert(increment(QObject::tr("Dual Wield Specialization"), 5));
    assert(increment(QObject::tr("Dagger Specialization"), 5));
    assert(increment(QObject::tr("Blade Flurry")));
    assert(increment(QObject::tr("Weapon Expertise"), 2));
    assert(increment(QObject::tr("Adrenaline Rush")));

    assert(!decrement(QObject::tr("Blade Flurry")));

    clear_tree();
}

void TestCombat::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_combat();
    assert(tree_has_points(37));
}

void TestCombat::spec_combat() {
    assert(increment(QObject::tr("Improved Sinister Strike"), 2));
    assert(increment(QObject::tr("Improved Gouge"), 3));
    assert(increment(QObject::tr("Improved Backstab"), 3));
    assert(increment(QObject::tr("Precision"), 5));
    assert(increment(QObject::tr("Improved Sprint"), 2));
    assert(increment(QObject::tr("Dagger Specialization"), 5));
    assert(increment(QObject::tr("Dual Wield Specialization"), 5));
    assert(increment(QObject::tr("Sword Specialization"), 5));
    assert(increment(QObject::tr("Blade Flurry"), 1));
    assert(increment(QObject::tr("Weapon Expertise"), 2));
    assert(increment(QObject::tr("Aggression"), 3));
    assert(increment(QObject::tr("Adrenaline Rush"), 1));
}
