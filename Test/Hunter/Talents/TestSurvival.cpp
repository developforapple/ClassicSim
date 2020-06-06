#include "TestSurvival.h"

#include <cassert>

#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestSurvival::TestSurvival(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "RIGHT") {}

void TestSurvival::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestSurvival::tear_down() {
    delete pchar;
    delete race;
    delete raid_control;
    delete sim_settings;
}

void TestSurvival::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Deflection")));

    assert(increment(QObject::tr("Deflection"), 5));
    // 5 points
    assert(!increment(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Deflection")));
    assert(increment(QObject::tr("Deflection")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Savage Strikes")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(increment(QObject::tr("Monster Slaying")));
    assert(decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Deflection")));
    assert(!decrement(QObject::tr("Monster Slaying")));

    assert(increment(QObject::tr("Deflection")));
    assert(decrement(QObject::tr("Monster Slaying")));
    assert(decrement(QObject::tr("Savage Strikes")));

    // Make Counterattack available via raw points
    assert(increment(QObject::tr("Improved Wing Clip"), 5));
    assert(increment(QObject::tr("Survivalist"), 5));
    assert(increment(QObject::tr("Surefooted"), 3));
    assert(increment(QObject::tr("Trap Mastery"), 2));

    // Assert cannot spend points into Counterattack if 1/1 Deterrence is missing
    assert(!increment(QObject::tr("Counterattack")));
    assert(increment(QObject::tr("Deterrence")));
    assert(increment(QObject::tr("Counterattack")));

    // Make Wyvern Sting available via raw points
    assert(increment(QObject::tr("Monster Slaying"), 3));
    assert(increment(QObject::tr("Lightning Reflexes"), 5));

    // Assert cannot spend points into Wyvern Sting if 3/3 Killer Instinct is missing
    assert(!increment(QObject::tr("Wyvern Sting")));
    assert(increment(QObject::tr("Killer Instinct")));
    assert(!increment(QObject::tr("Wyvern Sting")));
    assert(increment(QObject::tr("Killer Instinct")));
    assert(!increment(QObject::tr("Wyvern Sting")));
    assert(increment(QObject::tr("Killer Instinct")));
    assert(increment(QObject::tr("Wyvern Sting")));
}

void TestSurvival::test_clearing_tree_after_filling() {
    spec_survival();

    clear_tree();

    assert(tree_has_points(0));
}

void TestSurvival::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_survival();
    assert(tree_has_points(48));
}

void TestSurvival::spec_survival() {
    assert(increment(QObject::tr("Humanoid Slaying"), 3));
    assert(increment(QObject::tr("Monster Slaying"), 3));
    assert(increment(QObject::tr("Deflection"), 5));
    assert(increment(QObject::tr("Entrapment"), 5));
    assert(increment(QObject::tr("Savage Strikes"), 2));
    assert(increment(QObject::tr("Improved Wing Clip"), 5));
    assert(increment(QObject::tr("Clever Traps"), 2));
    assert(increment(QObject::tr("Survivalist"), 5));
    assert(increment(QObject::tr("Deterrence"), 1));
    assert(increment(QObject::tr("Trap Mastery"), 2));
    assert(increment(QObject::tr("Surefooted"), 3));
    assert(increment(QObject::tr("Improved Feign Death"), 2));
    assert(increment(QObject::tr("Killer Instinct"), 3));
    assert(increment(QObject::tr("Counterattack"), 1));
    assert(increment(QObject::tr("Lightning Reflexes"), 5));
    assert(increment(QObject::tr("Wyvern Sting"), 1));
}
