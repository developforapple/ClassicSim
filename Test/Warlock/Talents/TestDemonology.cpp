#include "TestDemonology.h"

#include <cassert>

#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warlock.h"

TestDemonology::TestDemonology(EquipmentDb* equipment_db_) : TestTalentTree(equipment_db_, "MID") {}

void TestDemonology::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warlock(race, equipment_db, sim_settings, raid_control);
}

void TestDemonology::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestDemonology::test_spending_talent_points() {
    assert(increment(QObject::tr("Improved Healthstone"), 2));
    assert(increment(QObject::tr("Improved Imp"), 3));
    assert(increment(QObject::tr("Demonic Embrace"), 5));
    assert(increment(QObject::tr("Improved Health Funnel"), 2));
    assert(increment(QObject::tr("Fel Intellect"), 5));
    assert(increment(QObject::tr("Improved Succubus"), 3));
    assert(increment(QObject::tr("Fel Stamina"), 5));
    assert(increment(QObject::tr("Improved Enslave Demon"), 5));
    assert(tree_has_points(30));

    // Assert cannot spend points into Soul Link if 1/1 Demonic Sacrifice is missing
    assert(!increment(QObject::tr("Soul Link")));
    assert(increment(QObject::tr("Demonic Sacrifice")));
    assert(increment(QObject::tr("Soul Link")));

    // Assert cannot remove points from Demonic Sacrifice once points are spent in Soul Link
    assert(!decrement(QObject::tr("Demonic Sacrifice")));
    assert(decrement(QObject::tr("Soul Link")));
    assert(decrement(QObject::tr("Demonic Sacrifice")));
    assert(tree_has_points(30));

    // Assert cannot spend points into Master Demonologist if 5/5 Unholy Power is missing
    assert(!increment(QObject::tr("Master Demonologist")));
    assert(increment(QObject::tr("Unholy Power"), 4));
    assert(!increment(QObject::tr("Master Demonologist")));
    assert(increment(QObject::tr("Unholy Power")));
    assert(increment(QObject::tr("Master Demonologist")));

    // Assert cannot remove points from Unholy Power once points are spent in Master Demonologist
    assert(!decrement(QObject::tr("Unholy Power")));
    assert(decrement(QObject::tr("Master Demonologist")));
    assert(decrement(QObject::tr("Unholy Power")));

    // Assert cannot increment Master Summoner without Fel Domination
    assert(!increment(QObject::tr("Master Summoner")));
    assert(increment(QObject::tr("Fel Domination")));
    assert(increment(QObject::tr("Master Summoner")));

    assert(!decrement(QObject::tr("Fel Domination")));
    assert(decrement(QObject::tr("Master Summoner")));
    assert(decrement(QObject::tr("Fel Domination")));
}

void TestDemonology::test_clearing_tree_after_filling() {
    spec_demonology();

    clear_tree();

    assert(tree_has_points(0));
}

void TestDemonology::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_demonology();
    assert(tree_has_points(51));
}

void TestDemonology::spec_demonology() {
    assert(increment(QObject::tr("Improved Healthstone"), 2));
    assert(increment(QObject::tr("Improved Imp"), 3));
    assert(increment(QObject::tr("Demonic Embrace"), 5));
    assert(increment(QObject::tr("Improved Health Funnel"), 2));
    assert(increment(QObject::tr("Improved Voidwalker"), 3));
    assert(increment(QObject::tr("Fel Intellect"), 5));
    assert(increment(QObject::tr("Improved Succubus"), 3));
    assert(increment(QObject::tr("Fel Domination"), 1));
    assert(increment(QObject::tr("Fel Stamina"), 5));
    assert(increment(QObject::tr("Master Summoner"), 2));
    assert(increment(QObject::tr("Unholy Power"), 5));
    assert(increment(QObject::tr("Improved Enslave Demon"), 5));
    assert(increment(QObject::tr("Demonic Sacrifice"), 1));
    assert(increment(QObject::tr("Improved Firestone"), 2));
    assert(increment(QObject::tr("Master Demonologist"), 5));
    assert(increment(QObject::tr("Soul Link"), 1));
    assert(increment(QObject::tr("Improved Spellstone"), 1));
}
