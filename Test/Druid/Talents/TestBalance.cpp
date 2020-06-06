#include "TestBalance.h"

#include <cassert>

#include "Druid.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Tauren.h"

TestBalance::TestBalance(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "LEFT") {}

void TestBalance::set_up() {
    race = new Tauren();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Druid(race, equipment_db, sim_settings, raid_control);
}

void TestBalance::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestBalance::test_spending_talent_points() {}

void TestBalance::test_clearing_tree_after_filling() {
    spec_balance();

    clear_tree();

    assert(tree_has_points(0));
}

void TestBalance::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_balance();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_balance();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_balance();
    assert(tree_has_points(51));
}

void TestBalance::spec_balance() {
    assert(increment(QObject::tr("Improved Wrath"), 5));
    assert(increment(QObject::tr("Nature's Grasp"), 1));
    assert(increment(QObject::tr("Improved Nature's Grasp"), 4));
    assert(increment(QObject::tr("Improved Entangling Roots"), 3));
    assert(increment(QObject::tr("Improved Moonfire"), 5));
    assert(increment(QObject::tr("Natural Weapons"), 5));
    assert(increment(QObject::tr("Natural Shapeshifter"), 3));
    assert(increment(QObject::tr("Improved Thorns"), 3));
    assert(increment(QObject::tr("Omen of Clarity"), 1));
    assert(increment(QObject::tr("Nature's Reach"), 2));
    assert(increment(QObject::tr("Vengeance"), 5));
    assert(increment(QObject::tr("Improved Starfire"), 5));
    assert(increment(QObject::tr("Nature's Grace"), 1));
    assert(increment(QObject::tr("Moonglow"), 3));
    assert(increment(QObject::tr("Moonfury"), 5));

    assert(decrement(QObject::tr("Moonfury"), 1));
    assert(increment(QObject::tr("Moonkin Form"), 1));
}
