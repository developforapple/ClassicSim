#include "TestProtectionPaladin.h"

#include <cassert>

#include "Human.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestProtectionPaladin::TestProtectionPaladin(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestProtectionPaladin::set_up() {
    race = new Human();
    raid_control = new RaidControl(sim_settings);
    pchar = new Paladin(race, equipment_db, sim_settings, raid_control);
}

void TestProtectionPaladin::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestProtectionPaladin::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Redoubt")));

    assert(increment(QObject::tr("Redoubt"), 5));
    // 5 points
    assert(!increment(QObject::tr("Redoubt")));
    assert(decrement(QObject::tr("Redoubt")));
    assert(increment(QObject::tr("Redoubt")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Precision")));
    assert(!decrement(QObject::tr("Redoubt")));
    assert(increment(QObject::tr("Improved Devotion Aura")));
    assert(decrement(QObject::tr("Redoubt")));
    assert(!decrement(QObject::tr("Redoubt")));
    assert(!decrement(QObject::tr("Improved Devotion Aura")));

    assert(increment(QObject::tr("Redoubt")));
    assert(decrement(QObject::tr("Improved Devotion Aura")));
    assert(increment(QObject::tr("Precision"), 2));
    assert(increment(QObject::tr("Guardian's Favor"), 2));

    // Assert cannot spend points into Shield Specialization if Redoubt is missing.
    assert(increment(QObject::tr("Improved Devotion Aura")));
    assert(decrement(QObject::tr("Redoubt")));
    assert(!increment(QObject::tr("Shield Specialization")));
    assert(increment(QObject::tr("Redoubt")));
    assert(increment(QObject::tr("Shield Specialization")));
    assert(!decrement(QObject::tr("Redoubt")));
}

void TestProtectionPaladin::test_clearing_tree_after_filling() {
    spec_protection();

    clear_tree();

    assert(tree_has_points(0));
}

void TestProtectionPaladin::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_protection();
    assert(tree_has_points(50));
}

void TestProtectionPaladin::spec_protection() {
    assert(increment(QObject::tr("Improved Devotion Aura"), 5));
    assert(increment(QObject::tr("Redoubt"), 5));
    assert(increment(QObject::tr("Precision"), 3));
    assert(increment(QObject::tr("Guardian's Favor"), 2));
    assert(increment(QObject::tr("Toughness"), 5));
    assert(increment(QObject::tr("Blessing of Kings"), 1));
    assert(increment(QObject::tr("Improved Righteous Fury"), 3));
    assert(increment(QObject::tr("Shield Specialization"), 3));
    assert(increment(QObject::tr("Anticipation"), 5));
    assert(increment(QObject::tr("Improved Hammer of Justice"), 3));
    assert(increment(QObject::tr("Improved Concentration Aura"), 3));
    assert(increment(QObject::tr("Blessing of Sanctuary"), 1));
    assert(increment(QObject::tr("Reckoning"), 5));
    assert(increment(QObject::tr("One-Handed Weapon Specialization"), 5));
    assert(increment(QObject::tr("Holy Shield"), 1));
}
