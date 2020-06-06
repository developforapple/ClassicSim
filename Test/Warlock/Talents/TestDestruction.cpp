#include "TestDestruction.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestDestruction::TestDestruction(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "RIGHT") {}

void TestDestruction::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestDestruction::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestDestruction::test_spending_talent_points() {
    assert(increment(QObject::tr("Improved Shadow Bolt"), 5));
    assert(increment(QObject::tr("Cataclysm"), 5));
    assert(increment(QObject::tr("Bane"), 5));
    assert(increment(QObject::tr("Aftermath"), 5));
    assert(increment(QObject::tr("Improved Searing Pain"), 5));
    assert(increment(QObject::tr("Emberstorm"), 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Conflagrate if 5/5 Improved Immolate is missing
    assert(!increment(QObject::tr("Conflagrate")));
    assert(increment(QObject::tr("Improved Immolate"), 4));
    assert(!increment(QObject::tr("Conflagrate")));
    assert(increment(QObject::tr("Improved Immolate")));
    assert(increment(QObject::tr("Conflagrate")));

    // Assert cannot remove points from Improved Immolate once points are spent in Conflagrate
    assert(!decrement(QObject::tr("Improved Immolate")));
    assert(decrement(QObject::tr("Conflagrate")));
    assert(decrement(QObject::tr("Improved Immolate"), 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Ruin if 5/5 Devastation is missing
    assert(!increment(QObject::tr("Ruin")));
    assert(increment(QObject::tr("Devastation"), 4));
    assert(!increment(QObject::tr("Ruin")));
    assert(increment(QObject::tr("Devastation")));
    assert(increment(QObject::tr("Ruin")));

    // Assert cannot remove points from Devastation once points are spent in Ruin
    assert(!decrement(QObject::tr("Devastation")));
    assert(decrement(QObject::tr("Ruin")));
    assert(decrement(QObject::tr("Devastation")));

    // Assert cannot increment Pyroclasm without 2/2 Intensity
    assert(!increment(QObject::tr("Pyroclasm")));
    assert(increment(QObject::tr("Intensity")));
    assert(!increment(QObject::tr("Pyroclasm")));
    assert(increment(QObject::tr("Intensity")));
    assert(increment(QObject::tr("Pyroclasm")));

    assert(!decrement(QObject::tr("Intensity")));
    assert(decrement(QObject::tr("Pyroclasm")));
    assert(decrement(QObject::tr("Intensity")));
}

void TestDestruction::test_clearing_tree_after_filling() {
    spec_destruction();

    clear_tree();

    assert(tree_has_points(0));
}

void TestDestruction::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_destruction();
    assert(tree_has_points(51));
}

void TestDestruction::spec_destruction() {
    assert(increment(QObject::tr("Improved Shadow Bolt"), 5));
    assert(increment(QObject::tr("Cataclysm"), 5));
    assert(increment(QObject::tr("Bane"), 5));
    assert(increment(QObject::tr("Aftermath"), 5));
    assert(increment(QObject::tr("Improved Firebolt"), 2));
    assert(increment(QObject::tr("Improved Lash of Pain"), 2));
    assert(increment(QObject::tr("Devastation"), 5));
    assert(increment(QObject::tr("Shadowburn"), 1));
    assert(increment(QObject::tr("Intensity"), 2));
    assert(increment(QObject::tr("Destructive Reach"), 2));
    assert(increment(QObject::tr("Improved Searing Pain"), 5));
    assert(increment(QObject::tr("Pyroclasm"), 2));
    assert(increment(QObject::tr("Improved Immolate"), 5));
    assert(increment(QObject::tr("Ruin"), 1));
    assert(increment(QObject::tr("Emberstorm"), 3));
    assert(increment(QObject::tr("Conflagrate"), 1));
}
