#include "TestHolyPaladin.h"

#include <cassert>

#include "Human.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "SimSettings.h"

TestHolyPaladin::TestHolyPaladin(EquipmentDb* equipment_db) : TestTalentTree(equipment_db, "LEFT") {}

void TestHolyPaladin::set_up() {
    race = new Human();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Paladin(race, equipment_db, sim_settings, raid_control);
}

void TestHolyPaladin::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestHolyPaladin::test_spending_talent_points() {
    assert(!decrement(QObject::tr("Divine Intellect")));

    assert(increment(QObject::tr("Divine Intellect"), 5));
    // 5 points
    assert(!increment(QObject::tr("Divine Intellect")));
    assert(decrement(QObject::tr("Divine Intellect")));
    assert(increment(QObject::tr("Divine Intellect")));

    // Spend point in T2 and check that T1 cannot be decremented below a total of 5 points.
    assert(increment(QObject::tr("Spiritual Focus")));
    assert(!decrement(QObject::tr("Divine Intellect")));
    assert(increment(QObject::tr("Divine Strength")));
    assert(decrement(QObject::tr("Divine Intellect")));
    assert(!decrement(QObject::tr("Divine Intellect")));
    assert(!decrement(QObject::tr("Divine Strength")));

    assert(increment(QObject::tr("Divine Intellect")));
    assert(decrement(QObject::tr("Divine Strength")));
    assert(increment(QObject::tr("Spiritual Focus"), 4));

    // Assert cannot spend points into Divine Favor if 5/5 Illumination is missing
    assert(increment(QObject::tr("Improved Lay on Hands"), 2));
    assert(increment(QObject::tr("Healing Light"), 3));
    assert(increment(QObject::tr("Consecration"), 1));
    assert(increment(QObject::tr("Unyielding Faith"), 2));
    assert(increment(QObject::tr("Improved Blessing of Wisdom"), 2));
    assert(tree_has_points(20));

    assert(!increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Illumination")));
    assert(!increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Illumination")));
    assert(!increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Illumination")));
    assert(!increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Illumination")));
    assert(!increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Illumination")));
    assert(increment(QObject::tr("Divine Favor")));
    assert(tree_has_points(26));

    // Assert cannot remove points from Illumination once points are spent in Holy Power
    assert(!decrement(QObject::tr("Illumination")));
    assert(decrement(QObject::tr("Divine Favor")));
    assert(decrement(QObject::tr("Illumination")));

    // Assert cannot increment Holy Shock without Divine Favor
    assert(increment(QObject::tr("Illumination")));
    assert(increment(QObject::tr("Holy Power"), 5));
    assert(tree_has_points(30));

    assert(!increment(QObject::tr("Holy Shock")));
    assert(increment(QObject::tr("Divine Favor")));
    assert(increment(QObject::tr("Holy Shock")));

    assert(tree_has_points(32));
    // Assert cannot decrement lower tiers
    assert(!decrement(QObject::tr("Divine Intellect")));
    assert(!decrement(QObject::tr("Spiritual Focus")));
    assert(decrement(QObject::tr("Improved Lay on Hands")));
    assert(!decrement(QObject::tr("Improved Lay on Hands")));
    assert(!decrement(QObject::tr("Improved Blessing of Wisdom")));
    assert(!decrement(QObject::tr("Divine Favor")));
    assert(!decrement(QObject::tr("Holy Power")));
}

void TestHolyPaladin::test_clearing_tree_after_filling() {
    spec_holy();

    clear_tree();

    assert(tree_has_points(0));
}

void TestHolyPaladin::test_refilling_tree_after_switching_talent_setup() {
    assert(tree_has_points(0));
    spec_holy();
    assert(tree_has_points(45));

    switch_to_setup(1);
    assert(tree_has_points(0));
    spec_holy();
    assert(tree_has_points(45));

    switch_to_setup(2);
    assert(tree_has_points(0));
    spec_holy();
    assert(tree_has_points(45));
}

void TestHolyPaladin::spec_holy() {
    assert(increment(QObject::tr("Divine Strength"), 5));
    assert(increment(QObject::tr("Divine Intellect"), 5));
    assert(increment(QObject::tr("Spiritual Focus"), 5));
    assert(increment(QObject::tr("Improved Seal of Righteousness"), 5));
    assert(increment(QObject::tr("Healing Light"), 3));
    assert(increment(QObject::tr("Consecration"), 1));
    assert(increment(QObject::tr("Improved Lay on Hands"), 2));
    assert(increment(QObject::tr("Unyielding Faith"), 2));
    assert(increment(QObject::tr("Illumination"), 5));
    assert(increment(QObject::tr("Improved Blessing of Wisdom"), 2));
    assert(increment(QObject::tr("Divine Favor"), 1));
    assert(increment(QObject::tr("Lasting Judgement"), 3));
    assert(increment(QObject::tr("Holy Power"), 5));
    assert(increment(QObject::tr("Holy Shock"), 1));
}
