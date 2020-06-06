#include "TestFire.h"

#include <cassert>

#include "Mage.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Troll.h"

TestFire::TestFire(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestFire::set_up() {
    race = new Troll();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Mage(race, equipment_db, sim_settings, raid_control);
}

void TestFire::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFire::test_spending_talent_points() {
    assert(increment(QObject::tr("Improved Fireball"), 5));
    assert(increment(QObject::tr("Impact"), 5));
    assert(increment(QObject::tr("Ignite"), 5));
    assert(increment(QObject::tr("Flame Throwing"), 2));
    assert(increment(QObject::tr("Improved Fire Blast"), 3));

    // Assert cannot spend points into Blast Wave if 1/1 Pyroblast is missing
    assert(tree_has_points(20));

    assert(!increment(QObject::tr("Blast Wave")));
    assert(increment(QObject::tr("Pyroblast")));
    assert(increment(QObject::tr("Blast Wave")));

    // Assert cannot remove points from Pyroblast once points are spent in Blast Wave
    assert(!decrement(QObject::tr("Pyroblast")));
    assert(decrement(QObject::tr("Blast Wave")));
    assert(decrement(QObject::tr("Pyroblast")));

    // Assert cannot increment Combustion without Blast Wave
    assert(increment(QObject::tr("Incinerate"), 2));
    assert(increment(QObject::tr("Improved Flamestrike"), 3));
    assert(increment(QObject::tr("Fire Power"), 5));
    assert(tree_has_points(30));

    assert(!increment(QObject::tr("Combustion")));
    assert(increment(QObject::tr("Critical Mass")));
    assert(!increment(QObject::tr("Combustion")));
    assert(increment(QObject::tr("Critical Mass")));
    assert(!increment(QObject::tr("Combustion")));
    assert(increment(QObject::tr("Critical Mass")));
    assert(increment(QObject::tr("Combustion")));
    assert(!decrement(QObject::tr("Critical Mass")));
}

void TestFire::test_clearing_tree_after_filling() {
    spec_fire();

    clear_tree();

    assert(tree_has_points(0));
}

void TestFire::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_fire();
    assert(tree_has_points(46));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_fire();
    assert(tree_has_points(46));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_fire();
    assert(tree_has_points(46));
}

void TestFire::spec_fire() {
    assert(increment(QObject::tr("Improved Fireball"), 5));
    assert(increment(QObject::tr("Impact"), 5));
    assert(increment(QObject::tr("Ignite"), 5));
    assert(increment(QObject::tr("Flame Throwing"), 2));
    assert(increment(QObject::tr("Improved Fire Blast"), 3));
    assert(increment(QObject::tr("Incinerate"), 2));
    assert(increment(QObject::tr("Improved Flamestrike"), 3));
    assert(increment(QObject::tr("Pyroblast"), 1));
    assert(increment(QObject::tr("Burning Soul"), 2));
    assert(increment(QObject::tr("Improved Scorch"), 3));
    assert(increment(QObject::tr("Improved Fire Ward"), 2));
    assert(increment(QObject::tr("Master of Elements"), 3));
    assert(increment(QObject::tr("Critical Mass"), 3));
    assert(increment(QObject::tr("Blast Wave"), 1));
    assert(increment(QObject::tr("Fire Power"), 5));
    assert(increment(QObject::tr("Combustion"), 1));
}
