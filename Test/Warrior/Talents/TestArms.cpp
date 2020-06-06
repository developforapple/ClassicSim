#include "TestArms.h"

#include <cassert>

#include "Arms.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warrior.h"

TestArms::TestArms(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "LEFT") {}

void TestArms::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestArms::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestArms::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Deflection")));

    assert(increment(QObject::tr("Deflection"), 5));
    // 5 points
    assert(!increment(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Deflection")));
    assert(increment(QObject::tr("Deflection")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Tactical Mastery")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(increment(QObject::tr("Improved Rend")));
    assert(decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Improved Rend")));

    assert(increment(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Improved Rend")));
    // 5 Deflection 1 Imp TC.

    assert(increment(QObject::tr("Tactical Mastery"), 4));

    // Assert cannot spend points into Deep Wounds if 3/3 Imp Rend is missing
    assert(!increment(QObject::tr("Deep Wounds")));
    assert(increment(QObject::tr("Improved Rend")));
    assert(!increment(QObject::tr("Deep Wounds")));
    assert(increment(QObject::tr("Improved Rend")));
    assert(!increment(QObject::tr("Deep Wounds")));
    assert(increment(QObject::tr("Improved Rend")));

    // Assert cannot remove points from Improved Rend once points are spent in Deep Wounds
    assert(increment(QObject::tr("Deep Wounds")));
    assert(!decrement(QObject::tr("Improved Rend")));
    assert(increment(QObject::tr("Deep Wounds")));
    assert(!decrement(QObject::tr("Improved Rend")));
    assert(increment(QObject::tr("Deep Wounds")));
    assert(!decrement(QObject::tr("Improved Rend")));

    assert(increment(QObject::tr("Improved Overpower"), 2));
    assert(increment(QObject::tr("Impale"), 2));
    assert(!decrement(QObject::tr("Deep Wounds")));

    assert(increment(QObject::tr("Sweeping Strikes")));

    // Cannot decrement lower tiers
    assert(!decrement(QObject::tr("Impale")));
    assert(!decrement(QObject::tr("Deep Wounds")));
    assert(!decrement(QObject::tr("Tactical Mastery")));
    assert(!decrement(QObject::tr("Deflection")));

    // Try shifting points in T1
    assert(increment(QObject::tr("Improved Heroic Strike")));
    assert(decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Improved Heroic Strike")));

    assert(increment(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Improved Heroic Strike")));

    // Try shifting points in T2
    assert(increment(QObject::tr("Improved Charge")));
    assert(decrement(QObject::tr("Tactical Mastery")));
    assert(!decrement(QObject::tr("Improved Charge")));
    assert(!decrement(QObject::tr("Tactical Mastery")));

    assert(increment(QObject::tr("Tactical Mastery")));
    assert(decrement(QObject::tr("Improved Charge")));

    // Try shifting points in T3
    assert(increment(QObject::tr("Anger Management")));
    assert(decrement(QObject::tr("Improved Overpower")));
    assert(!decrement(QObject::tr("Anger Management")));
    assert(!decrement(QObject::tr("Improved Overpower")));

    assert(increment(QObject::tr("Improved Overpower")));
    assert(decrement(QObject::tr("Anger Management")));

    // Try shifting points in T4
    assert(increment(QObject::tr("Two-Handed Weapon Specialization")));
    assert(decrement(QObject::tr("Impale")));
    assert(!decrement(QObject::tr("Two-Handed Weapon Specialization")));
    assert(!decrement(QObject::tr("Two-Handed Weapon Specialization")));

    assert(increment(QObject::tr("Impale")));
    assert(decrement(QObject::tr("Two-Handed Weapon Specialization")));

    assert(increment(QObject::tr("Axe Specialization"), 5));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization")));
    assert(!increment(QObject::tr("Mortal Strike")));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization")));
    assert(!increment(QObject::tr("Mortal Strike")));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization")));
    assert(!increment(QObject::tr("Mortal Strike")));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization")));
    assert(tree_has_points(30));
    assert(increment(QObject::tr("Mortal Strike")));

    // Assert cannot remove parent (Sweeping Strikes) when child (MS) is active although points allow
    assert(!decrement(QObject::tr("Sweeping Strikes")));

    // Assert lower tiers cannot be decremented
    assert(!decrement(QObject::tr("Axe Specialization")));
    assert(!decrement(QObject::tr("Impale")));
    assert(!decrement(QObject::tr("Deep Wounds")));
    assert(!decrement(QObject::tr("Tactical Mastery")));
    assert(!decrement(QObject::tr("Deflection")));

    assert(decrement(QObject::tr("Mortal Strike")));
}

void TestArms::test_clearing_tree_after_filling() {
    assert(increment(QObject::tr("Deflection"), 5));
    assert(increment(QObject::tr("Improved Rend"), 3));
    assert(increment(QObject::tr("Tactical Mastery"), 5));
    assert(increment(QObject::tr("Deep Wounds"), 3));
    assert(increment(QObject::tr("Anger Management")));
    assert(increment(QObject::tr("Impale"), 2));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization"), 5));
    assert(increment(QObject::tr("Axe Specialization"), 5));
    assert(increment(QObject::tr("Sweeping Strikes")));
    assert(increment(QObject::tr("Mortal Strike")));

    assert(!decrement(QObject::tr("Two-Handed Weapon Specialization")));

    clear_tree();
}

void TestArms::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_ms();
    assert(tree_has_points(31));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_ms();
    assert(tree_has_points(31));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_ms();
    assert(tree_has_points(31));
}

void TestArms::spec_ms() {
    assert(increment(QObject::tr("Improved Rend"), 3));
    assert(increment(QObject::tr("Deflection"), 3));
    assert(increment(QObject::tr("Tactical Mastery"), 5));
    assert(increment(QObject::tr("Improved Overpower"), 2));
    assert(increment(QObject::tr("Anger Management"), 1));
    assert(increment(QObject::tr("Deep Wounds"), 3));
    assert(increment(QObject::tr("Impale"), 2));
    assert(increment(QObject::tr("Two-Handed Weapon Specialization"), 5));
    assert(increment(QObject::tr("Sweeping Strikes"), 1));
    assert(increment(QObject::tr("Sword Specialization"), 5));
    assert(increment(QObject::tr("Mortal Strike"), 1));
}
