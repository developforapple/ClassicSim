#include "TestAssassination.h"

#include <cassert>

#include "Assassination.h"
#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"

TestAssassination::TestAssassination(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "LEFT") {}

void TestAssassination::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestAssassination::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestAssassination::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Malice")));

    assert(increment(QObject::tr("Malice"), 5));
    // 5 points
    assert(!increment(QObject::tr("Malice")));
    assert(decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Malice")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Murder")));
    assert(!decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Improved Eviscerate")));
    assert(decrement(QObject::tr("Malice")));
    assert(!decrement(QObject::tr("Malice")));
    assert(!decrement(QObject::tr("Improved Eviscerate")));

    assert(increment(QObject::tr("Malice")));
    assert(decrement(QObject::tr("Improved Eviscerate")));
    assert(decrement(QObject::tr("Murder")));
    assert(decrement(QObject::tr("Malice"), 5));

    // 0 points spent, make Lethality "available" via other talents
    assert(increment(QObject::tr("Improved Eviscerate"), 3));
    assert(increment(QObject::tr("Remorseless Attacks"), 2));
    assert(increment(QObject::tr("Ruthlessness"), 3));
    assert(increment(QObject::tr("Murder"), 2));

    // Assert cannot spend points into Lethality if 5/5 Malice is missing
    assert(!increment(QObject::tr("Lethality")));
    assert(increment(QObject::tr("Malice")));
    assert(!increment(QObject::tr("Lethality")));
    assert(increment(QObject::tr("Malice")));
    assert(!increment(QObject::tr("Lethality")));
    assert(increment(QObject::tr("Malice")));
    assert(!increment(QObject::tr("Lethality")));
    assert(increment(QObject::tr("Malice")));
    assert(!increment(QObject::tr("Lethality")));
    assert(increment(QObject::tr("Malice")));

    // Assert cannot remove points from Malice once points are spent in Lethality
    assert(increment(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Malice")));
    assert(increment(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Malice")));

    // 20 points spent, shift around points in T1 into T4 for assertions.
    assert(increment(QObject::tr("Vile Poisons"), 3));
    assert(decrement(QObject::tr("Improved Eviscerate"), 3));
    assert(tree_has_points(20));

    assert(increment(QObject::tr("Cold Blood")));

    // Cannot decrement lower tiers
    assert(!decrement(QObject::tr("Vile Poisons")));
    assert(!decrement(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Ruthlessness")));
    assert(!decrement(QObject::tr("Malice")));

    // Try shifting points in T1
    assert(increment(QObject::tr("Improved Eviscerate")));
    assert(decrement(QObject::tr("Remorseless Attacks")));
    assert(!decrement(QObject::tr("Remorseless Attacks")));
    assert(!decrement(QObject::tr("Improved Eviscerate")));

    assert(increment(QObject::tr("Remorseless Attacks")));
    assert(decrement(QObject::tr("Improved Eviscerate")));

    // Try shifting points in T2
    assert(increment(QObject::tr("Improved Slice And Dice")));
    assert(decrement(QObject::tr("Murder")));
    assert(!decrement(QObject::tr("Improved Slice And Dice")));
    assert(!decrement(QObject::tr("Murder")));

    assert(increment(QObject::tr("Murder")));
    assert(decrement(QObject::tr("Improved Slice And Dice")));

    // Try shifting points in T3
    assert(increment(QObject::tr("Improved Expose Armor")));
    assert(decrement(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Improved Expose Armor")));
    assert(!decrement(QObject::tr("Lethality")));

    assert(increment(QObject::tr("Lethality")));
    assert(decrement(QObject::tr("Improved Expose Armor")));

    // Try shifting points in T4
    assert(!decrement(QObject::tr("Vile Poisons")));
    assert(increment(QObject::tr("Improved Poisons")));
    assert(decrement(QObject::tr("Vile Poisons")));
    assert(!decrement(QObject::tr("Improved Poisons")));

    assert(increment(QObject::tr("Vile Poisons")));
    assert(decrement(QObject::tr("Improved Poisons")));

    // Assert cannot remove parent (Cold Blood) when child (Seal Fate) is active although points allow
    assert(increment(QObject::tr("Improved Poisons"), 5));
    assert(increment(QObject::tr("Vile Poisons"), 2));
    assert(tree_has_points(28));
    assert(increment(QObject::tr("Seal Fate")));
    assert(!decrement(QObject::tr("Cold Blood")));
    assert(increment(QObject::tr("Seal Fate")));

    // Assert lower tiers cannot be decremented with Vigor enabled (31 pts)
    assert(increment(QObject::tr("Vigor")));
    assert(!decrement(QObject::tr("Improved Poisons")));
    assert(!decrement(QObject::tr("Lethality")));
    assert(!decrement(QObject::tr("Murder")));
    assert(!decrement(QObject::tr("Remorseless Attacks")));

    assert(decrement(QObject::tr("Vigor")));
}

void TestAssassination::test_clearing_tree_after_filling() {
    assert(increment(QObject::tr("Improved Eviscerate"), 3));
    assert(increment(QObject::tr("Malice"), 5));
    assert(increment(QObject::tr("Ruthlessness"), 3));
    assert(increment(QObject::tr("Murder"), 2));
    assert(increment(QObject::tr("Improved Slice And Dice"), 3));
    assert(increment(QObject::tr("Relentless Strikes"), 1));
    assert(increment(QObject::tr("Lethality"), 5));
    assert(increment(QObject::tr("Improved Poisons"), 5));
    assert(increment(QObject::tr("Vile Poisons"), 5));
    assert(increment(QObject::tr("Cold Blood")));
    assert(increment(QObject::tr("Seal Fate"), 5));
    assert(increment(QObject::tr("Vigor")));

    assert(!decrement(QObject::tr("Cold Blood")));

    clear_tree();
}

void TestAssassination::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_seal_fate();
    assert(tree_has_points(30));
}

void TestAssassination::spec_seal_fate() {
    assert(increment(QObject::tr("Malice"), 5));
    assert(increment(QObject::tr("Ruthlessness"), 3));
    assert(increment(QObject::tr("Murder"), 2));
    assert(increment(QObject::tr("Improved Slice And Dice"), 3));
    assert(increment(QObject::tr("Relentless Strikes"), 1));
    assert(increment(QObject::tr("Lethality"), 5));
    assert(increment(QObject::tr("Improved Poisons"), 5));
    assert(increment(QObject::tr("Cold Blood"), 1));
    assert(increment(QObject::tr("Seal Fate"), 5));
}
