#include "TestFeralCombat.h"

#include <cassert>

#include "Druid.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Tauren.h"

TestFeralCombat::TestFeralCombat(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "MID") {}

void TestFeralCombat::set_up() {
    race = new Tauren();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Druid(race, equipment_db, sim_settings, raid_control);
}

void TestFeralCombat::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestFeralCombat::test_spending_talent_points() {}

void TestFeralCombat::test_clearing_tree_after_filling() {
    spec_feral_combat();

    clear_tree();

    assert(tree_has_points(0));
}

void TestFeralCombat::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_feral_combat();
    assert(tree_has_points(46));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_feral_combat();
    assert(tree_has_points(46));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_feral_combat();
    assert(tree_has_points(46));
}

void TestFeralCombat::spec_feral_combat() {
    assert(increment(QObject::tr("Ferocity"), 5));
    assert(increment(QObject::tr("Feral Aggression"), 5));
    assert(increment(QObject::tr("Feral Instinct"), 5));
    assert(increment(QObject::tr("Brutal Impact"), 2));
    assert(increment(QObject::tr("Thick Hide"), 5));
    assert(increment(QObject::tr("Feline Swiftness"), 2));
    assert(increment(QObject::tr("Feral Charge"), 1));
    assert(increment(QObject::tr("Sharpened Claws"), 3));
    assert(increment(QObject::tr("Improved Shred"), 2));
    assert(increment(QObject::tr("Predatory Strikes"), 3));
    assert(increment(QObject::tr("Blood Frenzy"), 2));
    assert(increment(QObject::tr("Primal Fury"), 2));
    assert(increment(QObject::tr("Savage Fury"), 2));
    assert(increment(QObject::tr("Faerie Fire (Feral)"), 1));
    assert(increment(QObject::tr("Heart of the Wild"), 5));
    assert(increment(QObject::tr("Leader of the Pack"), 1));
}
