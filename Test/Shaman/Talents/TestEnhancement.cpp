#include "TestEnhancement.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "Shaman.h"
#include "SimSettings.h"

TestEnhancement::TestEnhancement(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestEnhancement::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Shaman(race, equipment_db, sim_settings, raid_control);
}

void TestEnhancement::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestEnhancement::test_spending_talent_points() {
    assert(increment(QObject::tr("Ancestral Knowledge"), 5));
    assert(increment(QObject::tr("Shield Specialization"), 5));
    assert(increment(QObject::tr("Anticipation"), 5));

    // Assert cannot spend points into Flurry if 5/5 Thundering Strikes is missing
    assert(tree_has_points(15));

    assert(!increment(QObject::tr("Flurry")));
    assert(increment(QObject::tr("Thundering Strikes")));
    assert(!increment(QObject::tr("Flurry")));
    assert(increment(QObject::tr("Thundering Strikes")));
    assert(!increment(QObject::tr("Flurry")));
    assert(increment(QObject::tr("Thundering Strikes")));
    assert(!increment(QObject::tr("Flurry")));
    assert(increment(QObject::tr("Thundering Strikes")));
    assert(!increment(QObject::tr("Flurry")));
    assert(increment(QObject::tr("Thundering Strikes")));
    assert(increment(QObject::tr("Flurry")));

    // Assert cannot remove points from Thundering Strikes once points are spent in Flurry
    assert(!decrement(QObject::tr("Thundering Strikes")));
    assert(decrement(QObject::tr("Flurry")));
    assert(decrement(QObject::tr("Thundering Strikes")));
    assert(increment(QObject::tr("Thundering Strikes")));

    // Assert cannot increment Stormstrike without Elemental Weapons
    assert(increment(QObject::tr("Flurry"), 5));
    assert(increment(QObject::tr("Toughness"), 5));
    assert(tree_has_points(30));

    assert(!increment(QObject::tr("Stormstrike")));
    assert(increment(QObject::tr("Elemental Weapons"), 3));
    assert(increment(QObject::tr("Stormstrike")));
    assert(!decrement(QObject::tr("Elemental Weapons")));
}

void TestEnhancement::test_clearing_tree_after_filling() {
    spec_enhancement();

    clear_tree();

    assert(tree_has_points(0));
}

void TestEnhancement::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_enhancement();
    assert(tree_has_points(51));
}

void TestEnhancement::spec_enhancement() {
    assert(increment(QObject::tr("Ancestral Knowledge"), 5));
    assert(increment(QObject::tr("Shield Specialization"), 5));
    assert(increment(QObject::tr("Guardian Totems"), 2));
    assert(increment(QObject::tr("Thundering Strikes"), 5));
    assert(increment(QObject::tr("Improved Ghost Wolf"), 2));
    assert(increment(QObject::tr("Improved Lightning Shield"), 3));
    assert(increment(QObject::tr("Enhancing Totems"), 2));
    assert(increment(QObject::tr("Two-Handed Axes and Maces"), 1));
    assert(increment(QObject::tr("Anticipation"), 5));
    assert(increment(QObject::tr("Flurry"), 5));
    assert(increment(QObject::tr("Toughness"), 5));
    assert(increment(QObject::tr("Improved Weapon Totems"), 2));
    assert(increment(QObject::tr("Elemental Weapons"), 3));
    assert(increment(QObject::tr("Parry"), 1));
    assert(increment(QObject::tr("Weapon Mastery"), 4));
    assert(increment(QObject::tr("Stormstrike"), 1));
}
