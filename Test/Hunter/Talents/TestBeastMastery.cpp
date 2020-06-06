#include "TestBeastMastery.h"

#include <cassert>

#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestBeastMastery::TestBeastMastery(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "LEFT") {}

void TestBeastMastery::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestBeastMastery::tear_down() {
    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
}

void TestBeastMastery::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Endurance Training")));

    assert(increment(QObject::tr("Endurance Training"), 5));
    // 5 points
    assert(!increment(QObject::tr("Endurance Training")));
    assert(decrement(QObject::tr("Endurance Training")));
    assert(increment(QObject::tr("Endurance Training")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Improved Aspect of the Monkey")));
    assert(!decrement(QObject::tr("Endurance Training")));
    assert(increment(QObject::tr("Improved Aspect of the Hawk")));
    assert(decrement(QObject::tr("Endurance Training")));
    assert(!decrement(QObject::tr("Endurance Training")));
    assert(!decrement(QObject::tr("Improved Aspect of the Hawk")));

    assert(increment(QObject::tr("Endurance Training")));
    assert(decrement(QObject::tr("Improved Aspect of the Hawk")));
    assert(increment(QObject::tr("Improved Aspect of the Monkey"), 4));

    // Assert cannot spend points into Frenzy if 5/5 Ferocity is missing
    assert(increment(QObject::tr("Unleashed Fury"), 5));
    assert(increment(QObject::tr("Pathfinding"), 2));
    assert(increment(QObject::tr("Bestial Swiftness"), 1));
    assert(increment(QObject::tr("Improved Mend Pet"), 2));
    assert(increment(QObject::tr("Spirit Bond"), 2));
    assert(increment(QObject::tr("Bestial Discipline"), 2));
    assert(increment(QObject::tr("Improved Revive Pet")));
    assert(tree_has_points(25));

    assert(!increment(QObject::tr("Frenzy")));
    assert(increment(QObject::tr("Ferocity")));
    assert(!increment(QObject::tr("Frenzy")));
    assert(increment(QObject::tr("Ferocity")));
    assert(!increment(QObject::tr("Frenzy")));
    assert(increment(QObject::tr("Ferocity")));
    assert(!increment(QObject::tr("Frenzy")));
    assert(increment(QObject::tr("Ferocity")));
    assert(!increment(QObject::tr("Frenzy")));
    assert(increment(QObject::tr("Ferocity")));
    assert(increment(QObject::tr("Frenzy")));
    assert(tree_has_points(31));
    assert(increment(QObject::tr("Frenzy"), 4));

    // Assert cannot remove points from Ferocity once points are spent in Frenzy
    assert(!decrement(QObject::tr("Ferocity")));
    assert(decrement(QObject::tr("Frenzy")));
    assert(!decrement(QObject::tr("Ferocity")));
    assert(decrement(QObject::tr("Frenzy")));
    assert(!decrement(QObject::tr("Ferocity")));
    assert(decrement(QObject::tr("Frenzy")));
    assert(!decrement(QObject::tr("Ferocity")));
    assert(decrement(QObject::tr("Frenzy")));
    assert(!decrement(QObject::tr("Ferocity")));
    assert(decrement(QObject::tr("Frenzy")));
    assert(!decrement(QObject::tr("Frenzy")));
    assert(decrement(QObject::tr("Ferocity")));
    assert(tree_has_points(29));

    // Assert cannot increment Bestial Wrath without Intimidation
    assert(increment(QObject::tr("Ferocity")));
    assert(increment(QObject::tr("Frenzy")));
    assert(tree_has_points(31));

    assert(!increment(QObject::tr("Bestial Wrath")));
    assert(increment(QObject::tr("Intimidation")));
    assert(increment(QObject::tr("Bestial Wrath")));

    assert(decrement(QObject::tr("Spirit Bond"), 2));
    assert(tree_has_points(31));
    // Assert cannot decrement lower tiers
    assert(!decrement(QObject::tr("Endurance Training")));
    assert(!decrement(QObject::tr("Improved Aspect of the Monkey")));
    assert(!decrement(QObject::tr("Unleashed Fury")));
    assert(!decrement(QObject::tr("Ferocity")));
    assert(!decrement(QObject::tr("Improved Mend Pet")));
    assert(!decrement(QObject::tr("Bestial Discpline")));
    assert(!decrement(QObject::tr("Frenzy")));
}

void TestBeastMastery::test_clearing_tree_after_filling() {
    spec_beast_mastery();

    clear_tree();

    assert(tree_has_points(0));
}

void TestBeastMastery::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_beast_mastery();
    assert(tree_has_points(48));
}

void TestBeastMastery::spec_beast_mastery() {
    assert(increment(QObject::tr("Improved Aspect of the Hawk"), 5));
    assert(increment(QObject::tr("Endurance Training"), 5));
    assert(increment(QObject::tr("Improved Eyes of the Beast"), 2));
    assert(increment(QObject::tr("Improved Aspect of the Monkey"), 5));
    assert(increment(QObject::tr("Thick Hide"), 3));
    assert(increment(QObject::tr("Improved Revive Pet"), 2));
    assert(increment(QObject::tr("Pathfinding"), 2));
    assert(increment(QObject::tr("Bestial Swiftness"), 1));
    assert(increment(QObject::tr("Unleashed Fury"), 5));
    assert(increment(QObject::tr("Improved Mend Pet"), 2));
    assert(increment(QObject::tr("Ferocity"), 5));
    assert(increment(QObject::tr("Spirit Bond"), 2));
    assert(increment(QObject::tr("Intimidation"), 1));
    assert(increment(QObject::tr("Bestial Discipline"), 2));
    assert(increment(QObject::tr("Frenzy"), 5));
    assert(increment(QObject::tr("Bestial Wrath"), 1));
}
