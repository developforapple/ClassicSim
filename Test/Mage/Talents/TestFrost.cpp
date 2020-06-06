#include "TestFrost.h"

#include <cassert>

#include "Mage.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Troll.h"

TestFrost::TestFrost(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "RIGHT") {}

void TestFrost::set_up() {
    race = new Troll();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Mage(race, equipment_db, sim_settings, raid_control);
}

void TestFrost::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFrost::test_spending_talent_points() {
    assert(increment(QObject::tr("Frost Warding"), 2));
    assert(increment(QObject::tr("Improved Frostbolt"), 5));
    assert(increment(QObject::tr("Elemental Precision"), 3));
    assert(increment(QObject::tr("Ice Shards"), 5));

    // Assert cannot spend points into Shatter if 1/1 Improved Frost Nova is missing
    assert(tree_has_points(15));

    assert(!increment(QObject::tr("Shatter")));
    assert(increment(QObject::tr("Improved Frost Nova")));
    assert(!increment(QObject::tr("Shatter")));
    assert(increment(QObject::tr("Improved Frost Nova")));
    assert(increment(QObject::tr("Shatter")));

    // Assert cannot remove points from Improved Frost Nova once points are spent in Shatter
    assert(!decrement(QObject::tr("Improved Frost Nova")));
    assert(decrement(QObject::tr("Shatter")));
    assert(decrement(QObject::tr("Improved Frost Nova")));

    // Assert cannot increment Ice Barrier without Ice Block
    assert(increment(QObject::tr("Improved Frost Nova")));
    assert(increment(QObject::tr("Shatter"), 5));
    assert(increment(QObject::tr("Improved Cone of Cold"), 3));
    assert(increment(QObject::tr("Winter's Chill"), 5));
    assert(tree_has_points(30));

    assert(!increment(QObject::tr("Ice Barrier")));
    assert(increment(QObject::tr("Ice Block")));
    assert(increment(QObject::tr("Ice Barrier")));
    assert(!decrement(QObject::tr("Ice Block")));
}

void TestFrost::test_clearing_tree_after_filling() {
    spec_frost();

    clear_tree();

    assert(tree_has_points(0));
}

void TestFrost::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_frost();
    assert(tree_has_points(50));
}

void TestFrost::spec_frost() {
    assert(increment(QObject::tr("Frost Warding"), 2));
    assert(increment(QObject::tr("Improved Frostbolt"), 5));
    assert(increment(QObject::tr("Elemental Precision"), 3));
    assert(increment(QObject::tr("Ice Shards"), 5));
    assert(increment(QObject::tr("Frostbite", "Mage Frost Talent 2ML"), 3));
    assert(increment(QObject::tr("Improved Frost Nova"), 2));
    assert(increment(QObject::tr("Permafrost"), 3));
    assert(increment(QObject::tr("Piercing Ice"), 3));
    assert(increment(QObject::tr("Cold Snap"), 1));
    assert(increment(QObject::tr("Improved Blizzard"), 3));
    assert(increment(QObject::tr("Arctic Reach"), 2));
    assert(increment(QObject::tr("Frost Channeling"), 3));
    assert(increment(QObject::tr("Shatter"), 5));
    assert(increment(QObject::tr("Ice Block"), 1));
    assert(increment(QObject::tr("Improved Cone of Cold"), 3));
    assert(increment(QObject::tr("Winter's Chill"), 5));
    assert(increment(QObject::tr("Ice Barrier"), 1));
}
