#include "TestFury.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warrior.h"

TestFury::TestFury(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestFury::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestFury::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFury::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Cruelty")));

    assert(increment(QObject::tr("Cruelty"), 5));
    // 5 points
    assert(!increment(QObject::tr("Cruelty")));
    assert(decrement(QObject::tr("Cruelty")));
    assert(increment(QObject::tr("Cruelty")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Unbridled Wrath")));
    assert(!decrement(QObject::tr("Cruelty")));
    assert(increment(QObject::tr("Booming Voice")));
    assert(decrement(QObject::tr("Cruelty")));
    assert(!decrement(QObject::tr("Cruelty")));
    assert(!decrement(QObject::tr("Booming Voice")));

    assert(increment(QObject::tr("Cruelty")));
    assert(decrement(QObject::tr("Booming Voice")));
    // 5 Cruelty 1 UW.

    assert(increment(QObject::tr("Unbridled Wrath"), 4));
    assert(increment(QObject::tr("Improved Battle Shout"), 5));
    assert(increment(QObject::tr("Enrage"), 5));
    assert(increment(QObject::tr("Death Wish")));

    // Cannot decrement lower tiers
    assert(!decrement(QObject::tr("Improved Battle Shout")));
    assert(!decrement(QObject::tr("Enrage")));
    assert(!decrement(QObject::tr("Unbridled Wrath")));
    assert(!decrement(QObject::tr("Cruelty")));

    // Try shifting points in T1
    assert(increment(QObject::tr("Booming Voice")));
    assert(decrement(QObject::tr("Cruelty")));
    assert(!decrement(QObject::tr("Cruelty")));
    assert(!decrement(QObject::tr("Booming Voice")));

    assert(increment(QObject::tr("Cruelty")));
    assert(decrement(QObject::tr("Booming Voice")));

    // Try shifting points in T2
    assert(increment(QObject::tr("Improved Demoralizing Shout")));
    assert(decrement(QObject::tr("Unbridled Wrath")));
    assert(!decrement(QObject::tr("Unbridled Wrath")));
    assert(!decrement(QObject::tr("Improved Demoralizing Shout")));

    assert(increment(QObject::tr("Unbridled Wrath")));
    assert(decrement(QObject::tr("Improved Demoralizing Shout")));

    // Try shifting points in T3
    assert(increment(QObject::tr("Improved Cleave")));
    assert(decrement(QObject::tr("Improved Battle Shout")));
    assert(!decrement(QObject::tr("Improved Cleave")));
    assert(!decrement(QObject::tr("Improved Battle Shout")));

    assert(increment(QObject::tr("Improved Battle Shout")));
    assert(decrement(QObject::tr("Improved Cleave")));

    // Try shifting points in T4
    assert(increment(QObject::tr("Improved Execute")));
    assert(decrement(QObject::tr("Enrage")));
    assert(!decrement(QObject::tr("Improved Execute")));
    assert(!decrement(QObject::tr("Enrage")));

    assert(increment(QObject::tr("Enrage")));
    assert(decrement(QObject::tr("Improved Execute")));

    assert(increment(QObject::tr("Dual Wield Specialization"), 5));
    assert(increment(QObject::tr("Flurry"), 5));
    assert(increment(QObject::tr("Improved Execute"), 2));
    assert(increment(QObject::tr("Bloodthirst")));

    // Assert cannot remove parent (Death Wish) when child (BT) is active although points allow (34 spent)
    assert(!decrement(QObject::tr("Death Wish")));

    // Assert lower tiers with only 5 points per tier cannot be decremented
    assert(!decrement(QObject::tr("Improved Battle Shout")));
    assert(!decrement(QObject::tr("Unbridled Wrath")));
    assert(!decrement(QObject::tr("Cruelty")));

    // Assert can decrement tier 4 to 31 (including BT) but not any lower
    assert(decrement(QObject::tr("Dual Wield Specialization")));
    assert(decrement(QObject::tr("Dual Wield Specialization")));
    assert(decrement(QObject::tr("Dual Wield Specialization")));
    assert(!decrement(QObject::tr("Dual Wield Specialization")));

    assert(decrement(QObject::tr("Bloodthirst")));
}

void TestFury::test_clearing_tree_after_filling() {
    assert(increment(QObject::tr("Booming Voice"), 5));
    assert(increment(QObject::tr("Cruelty"), 5));
    assert(increment(QObject::tr("Unbridled Wrath"), 5));
    assert(increment(QObject::tr("Improved Battle Shout"), 5));
    assert(increment(QObject::tr("Enrage"), 5));
    assert(increment(QObject::tr("Flurry"), 5));
    assert(increment(QObject::tr("Death Wish")));
    assert(increment(QObject::tr("Bloodthirst")));

    clear_tree();
}

void TestFury::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_dw_fury();
    assert(tree_has_points(34));
}

void TestFury::spec_dw_fury() {
    assert(increment(QObject::tr("Cruelty"), 5));
    assert(increment(QObject::tr("Unbridled Wrath"), 5));
    assert(increment(QObject::tr("Improved Battle Shout"), 5));
    assert(increment(QObject::tr("Dual Wield Specialization"), 5));
    assert(increment(QObject::tr("Enrage"), 5));
    assert(increment(QObject::tr("Flurry"), 5));
    assert(increment(QObject::tr("Improved Execute"), 2));
    assert(increment(QObject::tr("Death Wish")));
    assert(increment(QObject::tr("Bloodthirst")));
}
