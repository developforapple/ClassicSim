#include "TestAffliction.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestAffliction::TestAffliction(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "LEFT") {}

void TestAffliction::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestAffliction::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestAffliction::test_spending_talent_points() {
    assert(increment(QObject::tr("Suppression"), 5));
    assert(increment(QObject::tr("Improved Corruption"), 5));
    assert(increment(QObject::tr("Improved Curse of Weakness"), 3));
    assert(increment(QObject::tr("Improved Drain Soul"), 2));
    assert(increment(QObject::tr("Improved Drain Life"), 5));

    // Assert cannot spend points into Curse of Exhaustion if 1/1 Amplify Curse is missing
    assert(tree_has_points(20));

    assert(!increment(QObject::tr("Curse of Exhaustion")));
    assert(increment(QObject::tr("Amplify Curse")));
    assert(increment(QObject::tr("Curse of Exhaustion")));

    // Assert cannot remove points from Amplify Curse once points are spent in Curse of Exhaustion
    assert(!decrement(QObject::tr("Amplify Curse")));
    assert(decrement(QObject::tr("Curse of Exhaustion")));
    assert(decrement(QObject::tr("Amplify Curse")));
    assert(tree_has_points(20));

    // Assert cannot spend points into Improved Curse of Exhaustion if 1/1 Curse of Exhaustion is missing
    assert(!increment(QObject::tr("Improved Curse of Exhaustion")));
    assert(increment(QObject::tr("Amplify Curse")));
    assert(!increment(QObject::tr("Improved Curse of Exhaustion")));
    assert(increment(QObject::tr("Curse of Exhaustion")));
    assert(increment(QObject::tr("Improved Curse of Exhaustion")));

    // Assert cannot remove points from Curse of Exhaustion or Amplify Curse once points are spent in Improved Curse of Exhaustion
    assert(!decrement(QObject::tr("Curse of Exhaustion")));
    assert(!decrement(QObject::tr("Amplify Curse")));
    assert(decrement(QObject::tr("Improved Curse of Exhaustion")));
    assert(decrement(QObject::tr("Curse of Exhaustion")));
    assert(decrement(QObject::tr("Amplify Curse")));

    // Assert cannot increment Shadow Mastery without Siphon Life
    assert(increment(QObject::tr("Fel Concentration"), 5));
    assert(tree_has_points(25));

    assert(!increment(QObject::tr("Shadow Mastery")));
    assert(increment(QObject::tr("Siphon Life")));
    assert(increment(QObject::tr("Shadow Mastery")));

    assert(!decrement(QObject::tr("Siphon Life")));
    assert(decrement(QObject::tr("Shadow Mastery")));
    assert(decrement(QObject::tr("Siphon Life")));
}

void TestAffliction::test_clearing_tree_after_filling() {
    spec_affliction();

    clear_tree();

    assert(tree_has_points(0));
}

void TestAffliction::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_affliction();
    assert(tree_has_points(49));
}

void TestAffliction::spec_affliction() {
    assert(increment(QObject::tr("Suppression"), 5));
    assert(increment(QObject::tr("Improved Corruption"), 5));
    assert(increment(QObject::tr("Improved Curse of Weakness"), 3));
    assert(increment(QObject::tr("Improved Drain Soul"), 2));
    assert(increment(QObject::tr("Improved Life Tap"), 2));
    assert(increment(QObject::tr("Improved Drain Life"), 5));
    assert(increment(QObject::tr("Improved Curse of Agony"), 3));
    assert(increment(QObject::tr("Fel Concentration"), 5));
    assert(increment(QObject::tr("Amplify Curse"), 1));
    assert(increment(QObject::tr("Grim Reach"), 2));
    assert(increment(QObject::tr("Nightfall"), 2));
    assert(increment(QObject::tr("Improved Drain Mana"), 2));
    assert(increment(QObject::tr("Siphon Life"), 1));
    assert(increment(QObject::tr("Curse of Exhaustion"), 1));
    assert(increment(QObject::tr("Improved Curse of Exhaustion"), 4));
    assert(increment(QObject::tr("Shadow Mastery"), 5));
    assert(increment(QObject::tr("Dark Pact"), 1));
}
