#include "TestRestorationDruid.h"

#include <cassert>

#include "Druid.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Tauren.h"

TestRestorationDruid::TestRestorationDruid(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "RIGHT") {}

void TestRestorationDruid::set_up() {
    race = new Tauren();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Druid(race, equipment_db, sim_settings, raid_control);
}

void TestRestorationDruid::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestRestorationDruid::test_spending_talent_points() {}

void TestRestorationDruid::test_clearing_tree_after_filling() {
    spec_restoration();

    clear_tree();

    assert(tree_has_points(0));
}

void TestRestorationDruid::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_restoration();
    assert(tree_has_points(51));
}

void TestRestorationDruid::spec_restoration() {
    assert(increment(QObject::tr("Improved Mark of the Wild"), 5));
    assert(increment(QObject::tr("Furor"), 5));
    assert(increment(QObject::tr("Improved Healing Touch"), 5));
    assert(increment(QObject::tr("Nature's Focus"), 5));
    assert(increment(QObject::tr("Improved Enrage"), 2));
    assert(increment(QObject::tr("Reflection"), 3));
    assert(increment(QObject::tr("Insect Swarm"), 1));
    assert(increment(QObject::tr("Subtlety", "Druid talent"), 5));
    assert(increment(QObject::tr("Tranquil Spirit"), 5));
    assert(increment(QObject::tr("Improved Rejuvenation"), 3));
    assert(increment(QObject::tr("Nature's Swiftness"), 1));
    assert(increment(QObject::tr("Gift of Nature"), 5));
    assert(increment(QObject::tr("Improved Tranquility"), 2));
    assert(increment(QObject::tr("Improved Regrowth"), 4));

    assert(decrement(QObject::tr("Improved Regrowth"), 1));
    assert(increment(QObject::tr("Swiftmend"), 1));
}
