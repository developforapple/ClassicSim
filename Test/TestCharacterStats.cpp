#include "TestCharacterStats.h"

#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Warrior.h"
#include "Weapon.h"

TestCharacterStats::TestCharacterStats(EquipmentDb* equipment_db) : TestObject(equipment_db) {}

void TestCharacterStats::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    cstats = pchar->get_stats();
}

void TestCharacterStats::tear_down() {
    delete pchar;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestCharacterStats::test_all() {
    qDebug() << "TestCharacterStats";
    set_up();
    test_values_after_initialization();
    tear_down();

    set_up();
    test_attack_speed_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_melee_and_ranged_attack_speed_modifiers_are_independent();
    tear_down();

    set_up();
    test_physical_damage_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_physical_damage_taken_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_spell_damage_taken_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_damage_bonuses_vs_creature_type();
    tear_down();

    set_up();
    test_ap_bonuses_vs_creature_type();
    tear_down();

    set_up();
    test_ap_multipliers();
    tear_down();

    set_up();
    test_physical_damage_mod_depends_on_attack_mode();
    tear_down();

    set_up();
    test_crit_dmg_mod_affected_by_creature_type();
    tear_down();

    set_up();
    test_spell_school_damage_mods();
    tear_down();

    set_up();
    test_no_negative_target_resistances_with_spell_pen_bonuses();
    tear_down();

    set_up();
    test_spell_damage_includes_relevant_sources();
    tear_down();

    set_up();
    test_magic_damage_includes_target_mods();
    tear_down();
}

void TestCharacterStats::test_values_after_initialization() {
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.0));
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.0));
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 1.0));
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 1.0));
}

void TestCharacterStats::test_attack_speed_multipliers_stacks_multiplicatively() {
    cstats->increase_melee_attack_speed(10);
    // 1.1 = 1.0 * 1.1
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.10));

    cstats->increase_melee_attack_speed(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.32));

    cstats->increase_melee_attack_speed(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.98));

    cstats->increase_melee_attack_speed(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.96));

    cstats->decrease_melee_attack_speed(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.30));

    cstats->decrease_melee_attack_speed(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.00));

    cstats->decrease_melee_attack_speed(100);
    // 1.50 = 1.0 * 1.5
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.50));

    cstats->decrease_melee_attack_speed(50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.00));
}

void TestCharacterStats::test_physical_damage_multipliers_stacks_multiplicatively() {
    cstats->increase_total_phys_dmg_mod(10);
    // 1.2 = 1.0 * 1.2
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.10));

    cstats->increase_total_phys_dmg_mod(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.32));

    cstats->increase_total_phys_dmg_mod(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.98));

    cstats->increase_total_phys_dmg_mod(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 3.96));

    cstats->decrease_total_phys_dmg_mod(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 3.30));

    cstats->decrease_total_phys_dmg_mod(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 3.00));

    cstats->decrease_total_phys_dmg_mod(100);
    // 1.50 = 1.0 * 1.5
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.50));

    cstats->decrease_total_phys_dmg_mod(50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.00));
}

void TestCharacterStats::test_physical_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_phys_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.90));

    cstats->add_phys_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.72));

    cstats->add_phys_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.36));

    cstats->remove_phys_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.45));

    cstats->remove_phys_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.50));

    cstats->remove_phys_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 1.00));
}

void TestCharacterStats::test_spell_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_spell_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.90));

    cstats->add_spell_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.72));

    cstats->add_spell_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.36));

    cstats->remove_spell_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.45));

    cstats->remove_spell_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.50));

    cstats->remove_spell_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 1.00));
}

void TestCharacterStats::test_damage_bonuses_vs_creature_type() {
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.0));
    assert(pchar->get_target()->get_creature_type() == Target::CreatureType::Dragonkin);

    cstats->increase_dmg_vs_type(Target::CreatureType::Dragonkin, 0.01);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.01));

    cstats->increase_dmg_vs_type(Target::CreatureType::Dragonkin, 0.1);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.11));

    cstats->decrease_dmg_vs_type(Target::CreatureType::Dragonkin, 0.05);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.06));

    cstats->decrease_dmg_vs_type(Target::CreatureType::Dragonkin, 0.06);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.0));
}

void TestCharacterStats::test_ap_bonuses_vs_creature_type() {
    const unsigned base_melee_ap = cstats->get_melee_ap();
    const unsigned base_ranged_ap = cstats->get_ranged_ap();
    assert(pchar->get_target()->get_creature_type() == Target::CreatureType::Dragonkin);

    cstats->increase_ap_vs_type(Target::CreatureType::Dragonkin, 100);
    assert(base_melee_ap + 100 == cstats->get_melee_ap());
    assert(base_ranged_ap + 100 == cstats->get_ranged_ap());

    cstats->decrease_ap_vs_type(Target::CreatureType::Dragonkin, 100);
    assert(base_melee_ap == cstats->get_melee_ap());
    assert(base_ranged_ap == cstats->get_ranged_ap());
}

void TestCharacterStats::test_ap_multipliers() {
    const unsigned base_melee_ap = cstats->get_melee_ap();
    const unsigned base_ranged_ap = cstats->get_ranged_ap();

    cstats->add_ap_multiplier(100);
    assert(cstats->get_melee_ap() == base_melee_ap * 2);
    assert(cstats->get_ranged_ap() == base_ranged_ap * 2);

    cstats->remove_ap_multiplier(100);
    assert(cstats->get_melee_ap() == base_melee_ap);
    assert(cstats->get_ranged_ap() == base_ranged_ap);
}

void TestCharacterStats::test_physical_damage_mod_depends_on_attack_mode() {
    pchar->get_equipment()->set_mainhand(19362);
    assert(pchar->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::AXE);
    pchar->get_equipment()->set_ranged(17069);
    assert(pchar->get_equipment()->get_ranged()->get_weapon_type() == WeaponTypes::BOW);

    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.0));
    cstats->increase_total_phys_dmg_for_weapon_type(WeaponTypes::AXE, 10);
    cstats->increase_total_phys_dmg_for_weapon_type(WeaponTypes::BOW, 20);

    pchar->get_spells()->set_attack_mode(AttackMode::MeleeAttack);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.1));

    pchar->get_spells()->set_attack_mode(AttackMode::RangedAttack);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.2));

    pchar->get_spells()->set_attack_mode(AttackMode::MagicAttack);
    assert(almost_equal(cstats->get_total_physical_damage_mod(), 1.0));
}

void TestCharacterStats::test_crit_dmg_mod_affected_by_creature_type() {
    assert(almost_equal(cstats->get_melee_ability_crit_dmg_mod(), 2.0));
    assert(almost_equal(cstats->get_spell_crit_dmg_mod(), 1.5));
    assert(almost_equal(cstats->get_ranged_ability_crit_dmg_mod(), 2.0));

    cstats->increase_crit_dmg_vs_type(Target::CreatureType::Dragonkin, 1);
    pchar->get_target()->set_creature_type(QObject::tr("Humanoid"));
    assert(almost_equal(cstats->get_melee_ability_crit_dmg_mod(), 2.0));
    assert(almost_equal(cstats->get_spell_crit_dmg_mod(), 1.5));
    assert(almost_equal(cstats->get_ranged_ability_crit_dmg_mod(), 2.0));

    pchar->get_target()->set_creature_type(QObject::tr("Dragonkin"));
    assert(almost_equal(cstats->get_melee_ability_crit_dmg_mod(), 2.01));
    assert(almost_equal(cstats->get_spell_crit_dmg_mod(), 1.51));
    assert(almost_equal(cstats->get_ranged_ability_crit_dmg_mod(), 2.01));

    cstats->decrease_crit_dmg_vs_type(Target::CreatureType::Dragonkin, 1);
    assert(almost_equal(cstats->get_melee_ability_crit_dmg_mod(), 2.0));
    assert(almost_equal(cstats->get_spell_crit_dmg_mod(), 1.5));
    assert(almost_equal(cstats->get_ranged_ability_crit_dmg_mod(), 2.0));
}

void TestCharacterStats::test_melee_and_ranged_attack_speed_modifiers_are_independent() {
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.0));
    assert(almost_equal(cstats->get_ranged_attack_speed_mod(), 1.0));

    cstats->increase_melee_attack_speed(30);
    cstats->increase_ranged_attack_speed(20);

    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.3));
    assert(almost_equal(cstats->get_ranged_attack_speed_mod(), 1.2));

    cstats->decrease_melee_attack_speed(30);
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.0));
    assert(almost_equal(cstats->get_ranged_attack_speed_mod(), 1.2));

    cstats->decrease_ranged_attack_speed(20);
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.0));
    assert(almost_equal(cstats->get_ranged_attack_speed_mod(), 1.0));
}

void TestCharacterStats::test_spell_school_damage_mods() {
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.0));

    cstats->increase_magic_school_damage_mod(10, MagicSchool::Holy);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.1));

    cstats->increase_magic_school_damage_mod(20, MagicSchool::Holy);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.32));

    cstats->decrease_magic_school_damage_mod(10, MagicSchool::Holy);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.2));

    cstats->decrease_magic_school_damage_mod(20, MagicSchool::Holy);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.0));
}

void TestCharacterStats::test_no_negative_target_resistances_with_spell_pen_bonuses() {
    assert(cstats->get_target_resistance(MagicSchool::Holy) == 0);
    cstats->increase_spell_penetration(MagicSchool::Holy, 10);
    assert(cstats->get_target_resistance(MagicSchool::Holy) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Holy, 10);
    assert(cstats->get_target_resistance(MagicSchool::Holy) == 0);

    assert(cstats->get_target_resistance(MagicSchool::Arcane) == 70);
    cstats->increase_spell_penetration(MagicSchool::Arcane, 80);
    assert(cstats->get_target_resistance(MagicSchool::Arcane) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Arcane, 10);
    assert(cstats->get_target_resistance(MagicSchool::Arcane) == 0);

    assert(cstats->get_target_resistance(MagicSchool::Fire) == 70);
    cstats->increase_spell_penetration(MagicSchool::Fire, 80);
    assert(cstats->get_target_resistance(MagicSchool::Fire) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Fire, 10);
    assert(cstats->get_target_resistance(MagicSchool::Fire) == 0);

    assert(cstats->get_target_resistance(MagicSchool::Frost) == 70);
    cstats->increase_spell_penetration(MagicSchool::Frost, 80);
    assert(cstats->get_target_resistance(MagicSchool::Frost) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Frost, 10);
    assert(cstats->get_target_resistance(MagicSchool::Frost) == 0);

    assert(cstats->get_target_resistance(MagicSchool::Nature) == 70);
    cstats->increase_spell_penetration(MagicSchool::Nature, 80);
    assert(cstats->get_target_resistance(MagicSchool::Nature) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Nature, 10);
    assert(cstats->get_target_resistance(MagicSchool::Nature) == 0);

    assert(cstats->get_target_resistance(MagicSchool::Shadow) == 70);
    cstats->increase_spell_penetration(MagicSchool::Shadow, 80);
    assert(cstats->get_target_resistance(MagicSchool::Shadow) == 0);
    cstats->decrease_spell_penetration(MagicSchool::Shadow, 10);
    assert(cstats->get_target_resistance(MagicSchool::Shadow) == 0);
}

void TestCharacterStats::test_spell_damage_includes_relevant_sources() {
    const Target::CreatureType target_type = pchar->get_target()->get_creature_type();
    const unsigned initial_spell_damage = cstats->get_spell_damage(MagicSchool::Fire);

    cstats->increase_base_spell_damage(100);
    assert(initial_spell_damage + 100 == cstats->get_spell_damage(MagicSchool::Fire));
    cstats->decrease_base_spell_damage(100);
    assert(initial_spell_damage == cstats->get_spell_damage(MagicSchool::Fire));

    cstats->increase_spell_damage_vs_school(100, MagicSchool::Fire);
    assert(initial_spell_damage + 100 == cstats->get_spell_damage(MagicSchool::Fire));
    cstats->decrease_spell_damage_vs_school(100, MagicSchool::Fire);
    assert(initial_spell_damage == cstats->get_spell_damage(MagicSchool::Fire));

    cstats->increase_spell_damage_vs_type(target_type, 100);
    assert(initial_spell_damage + 100 == cstats->get_spell_damage(MagicSchool::Fire));
    cstats->decrease_spell_damage_vs_type(target_type, 100);
    assert(initial_spell_damage == cstats->get_spell_damage(MagicSchool::Fire));
}

void TestCharacterStats::test_magic_damage_includes_target_mods() {
    pchar->get_target()->set_creature_type(QObject::tr("Undead"));
    assert(pchar->get_target()->get_creature_type() == Target::CreatureType::Undead);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.0));

    cstats->increase_magic_damage_mod_vs_type(Target::CreatureType::Undead, 10);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.1));

    cstats->increase_magic_damage_mod_vs_type(Target::CreatureType::Undead, 20);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.32));

    cstats->decrease_magic_damage_mod_vs_type(Target::CreatureType::Undead, 10);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.2));

    cstats->decrease_magic_damage_mod_vs_type(Target::CreatureType::Undead, 20);
    assert(almost_equal(cstats->get_magic_school_damage_mod(MagicSchool::Holy), 1.0));
}
