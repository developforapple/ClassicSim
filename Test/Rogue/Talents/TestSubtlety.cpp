#include "TestSubtlety.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Subtlety.h"

TestSubtlety::TestSubtlety(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "RIGHT") {}

void TestSubtlety::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestSubtlety::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestSubtlety::test_spending_talent_points() {
    assert(increment(QObject::tr("Opportunity"), 5));
    assert(increment(QObject::tr("Sleight of Hand"), 2));
    assert(increment(QObject::tr("Elusiveness"), 2));
    assert(increment(QObject::tr("Camouflage"), 1));
    assert(increment(QObject::tr("Initiative"), 3));
    assert(increment(QObject::tr("Ghostly Strike"), 1));
    assert(increment(QObject::tr("Improved Ambush"), 3));
    assert(increment(QObject::tr("Setup"), 2));
    assert(increment(QObject::tr("Improved Sap"), 3));

    // assert cannot increment Hemorrhage due to missing 3/3 Serrated Bldes
    assert(!increment(QObject::tr("Hemorrhage")));
    assert(increment(QObject::tr("Serrated Blades")));
    assert(!increment(QObject::tr("Hemorrhage")));
    assert(increment(QObject::tr("Serrated Blades")));
    assert(!increment(QObject::tr("Hemorrhage")));
    assert(increment(QObject::tr("Serrated Blades")));
    assert(increment(QObject::tr("Hemorrhage")));

    assert(increment(QObject::tr("Setup")));
    assert(increment(QObject::tr("Deadliness"), 3));

    // assert cannot increment Premeditation due to missing Preparation
    assert(tree_has_points(30));
    assert(!increment(QObject::tr("Premeditation")));
    assert(increment(QObject::tr("Preparation")));
    assert(increment(QObject::tr("Premeditation")));
}

void TestSubtlety::test_clearing_tree_after_filling() {
    spec_hemo();

    assert(!decrement(QObject::tr("Preparation")));
    assert(!decrement(QObject::tr("Serrated Blades")));

    clear_tree();
}

void TestSubtlety::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_hemo();
    assert(tree_has_points(47));
}

void TestSubtlety::spec_hemo() {
    assert(increment(QObject::tr("Master of Deception"), 5));
    assert(increment(QObject::tr("Opportunity"), 5));
    assert(increment(QObject::tr("Sleight of Hand"), 2));
    assert(increment(QObject::tr("Elusiveness"), 2));
    assert(increment(QObject::tr("Camouflage"), 5));
    assert(increment(QObject::tr("Initiative"), 3));
    assert(increment(QObject::tr("Ghostly Strike"), 1));
    assert(increment(QObject::tr("Improved Ambush"), 3));
    assert(increment(QObject::tr("Setup"), 3));
    assert(increment(QObject::tr("Improved Sap"), 3));
    assert(increment(QObject::tr("Serrated Blades"), 3));
    assert(increment(QObject::tr("Heightened Senses"), 2));
    assert(increment(QObject::tr("Preparation"), 1));
    assert(increment(QObject::tr("Dirty Deeds"), 2));
    assert(increment(QObject::tr("Hemorrhage"), 1));
    assert(increment(QObject::tr("Deadliness"), 5));
    assert(increment(QObject::tr("Premeditation"), 1));
}
