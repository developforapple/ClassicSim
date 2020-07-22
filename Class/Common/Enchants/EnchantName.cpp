#include "EnchantName.h"

EnchantInfo::EnchantInfo() {
    enchant_specs = {
        new EnchantSpec(EnchantName::Name::ArcanumOfFocus, QObject::tr("Arcanum Of Focus"), QObject::tr("Arcanum Of Focus"), QObject::tr("+8 Spell Damage/Healing")),
        new EnchantSpec(EnchantName::Name::ArcanumOfRapidity, QObject::tr("Arcanum Of Rapidity"), QObject::tr("Arcanum Of Rapidity"), QObject::tr("+1% Haste")),
        new EnchantSpec(EnchantName::Name::Biznicks247x128Accurascope, QObject::tr("Biznicks 247x128 Accurascope"), QObject::tr("Biznicks 247x128 Accurascope"),
                        QObject::tr("+3% Ranged Hit")),
        new EnchantSpec(EnchantName::Name::BrilliantManaOil, QObject::tr("Brilliant Mana Oil"), QObject::tr("Brilliant Mana Oil"), QObject::tr("+12mp5/+25 Heal")),
        new EnchantSpec(EnchantName::Name::BrilliantWizardOil, QObject::tr("Brilliant Wizard Oil"), QObject::tr("Brilliant Wizard Oil"), QObject::tr("+36 SP\n+1% Spell Crit")),
        new EnchantSpec(EnchantName::Name::ConsecratedSharpeningStone, QObject::tr("Consecrated Sharpening Stone"), QObject::tr("Consecrated Sharpening Stone"),
                        QObject::tr("+100 AP\nvs Undead")),
        new EnchantSpec(EnchantName::Name::Crusader, QObject::tr("Crusader"), QObject::tr("Enchant Weapon - Crusader"), QObject::tr("Crusader")),
        new EnchantSpec(EnchantName::Name::DeathsEmbrace, QObject::tr("Death's Embrace"), QObject::tr("Deaths Embrace"), QObject::tr("+28 Attack and\n1% Dodge")),
        new EnchantSpec(EnchantName::Name::DenseSharpeningStone, QObject::tr("Dense Sharpening Stone"), QObject::tr("Dense Sharpening Stone"), QObject::tr("+8 Damage")),
        new EnchantSpec(EnchantName::Name::DenseWeightstone, QObject::tr("Dense Weightstone"), QObject::tr("Dense Weightstone"), QObject::tr("+8 Damage")),
        new EnchantSpec(EnchantName::Name::ElementalSharpeningStone, QObject::tr("Elemental Sharpening Stone"), QObject::tr("Elemental Sharpening Stone"), QObject::tr("+2% Crit")),
        new EnchantSpec(EnchantName::Name::Enchant2HWeaponAgility, QObject::tr("2H Weapon Agility"), QObject::tr("Enchant 2H Weapon - Agility"), QObject::tr("+25 Agility")),
        new EnchantSpec(EnchantName::Name::Enchant2HWeaponSuperiorImpact, QObject::tr("2H Weapon Superior Impact"), QObject::tr("Enchant 2H Weapon - Superior Impact"),
                        QObject::tr("+9 Damage")),
        new EnchantSpec(EnchantName::Name::EnchantBootsAgility, QObject::tr("Agility", "Enchant Boots Agility"), QObject::tr("Enchant Boots - Agility"), QObject::tr("+5 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantBootsGreaterAgility, QObject::tr("Greater Agility", "Enchant Boots Greater Agility"), QObject::tr("Enchant Boots - Greater Agility"), QObject::tr("+7 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantBootsMinorSpeed, QObject::tr("Minor Speed", "Enchant Boots Minor Speed"), QObject::tr("Enchant Boots - Minor Speed"), QObject::tr("Speed Increase")),
        new EnchantSpec(EnchantName::Name::EnchantBootsSpirit, QObject::tr("Spirit", "Enchant Boots Spirit"), QObject::tr("Enchant Boots - Spirit"), QObject::tr("+5 Spirit")),
        new EnchantSpec(EnchantName::Name::EnchantBracerGreaterIntellect, QObject::tr("Greater Intellect", "Enchant Bracer Greater Intellect"), QObject::tr("Enchant Bracer - Greater Intellect"), QObject::tr("+7 Intellect")),
        new EnchantSpec(EnchantName::Name::EnchantBracerGreaterStrength, QObject::tr("Greater Strength", "Enchant Bracer Greater Strength"), QObject::tr("Enchant Bracer - Greater - Strength"), QObject::tr("+7 Strength")),
        new EnchantSpec(EnchantName::Name::EnchantBracerManaRegeneration, QObject::tr("Mana Regeneration", "Enchant Bracer Mana Regeneration"), QObject::tr("Enchant Bracer - Mana Regeneration"), QObject::tr("+4 mp5")),
        new EnchantSpec(EnchantName::Name::EnchantBracerMinorAgility, QObject::tr("Minor Agility", "Enchant Bracer Minor Agility"), QObject::tr("Enchant Bracer - Minor Agility"), QObject::tr("+1 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantBracerSuperiorStrength, QObject::tr("Superior Strength", "Enchant Bracer Superior Strength"), QObject::tr("Enchant Bracer - Superior Strength"), QObject::tr("+9 Strength")),
        new EnchantSpec(EnchantName::Name::EnchantChestGreaterStats, QObject::tr("Greater Stats", "Enchant Chest Greater Stats"), QObject::tr("Enchant Chest - Greater Stats"), QObject::tr("+4 Attributes")),
        new EnchantSpec(EnchantName::Name::EnchantChestMajorMana, QObject::tr("Major Mana", "Enchant Chest Major Mana"), QObject::tr("Enchant Chest - Major Mana"), QObject::tr("+100 Mana")),
        new EnchantSpec(EnchantName::Name::EnchantChestStats, QObject::tr("Stats", "Enchant Chest Stats"), QObject::tr("Enchant Chest - Stats"), QObject::tr("+3 Attributes")),
        new EnchantSpec(EnchantName::Name::EnchantCloakLesserAgility, QObject::tr("Lesser Agility", "Enchant Cloak Lesser Agility"), QObject::tr("Enchant Cloak - Lesser Agility"), QObject::tr("+3 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesFirePower, QObject::tr("Fire Power", "Enchant Gloves Fire Power"), QObject::tr("Enchant Gloves - Fire Power"), QObject::tr("+20 Fire Damage")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesFrostPower, QObject::tr("Frost Power", "Enchant Gloves Frost Power"), QObject::tr("Enchant Gloves - Frost Power"), QObject::tr("+20 Frost Damage")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesGreaterAgility, QObject::tr("Greater Agility", "Enchant Gloves Greater Agility"), QObject::tr("Enchant Gloves - Greater Agility"), QObject::tr("+7 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesGreaterStrength, QObject::tr("Greater Strength", "Enchant Gloves Greater Strength"), QObject::tr("Enchant Gloves - Greater Strength"), QObject::tr("+7 Strength")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesMinorHaste, QObject::tr("Minor Haste", "Enchant Gloves Minor Haste"), QObject::tr("Enchant Gloves - Minor Haste"), QObject::tr("+1% Attack Speed")),
        new EnchantSpec(EnchantName::Name::EnchantGlovesSuperiorAgility, QObject::tr("Superior Agility", "Enchant Gloves Superior Agility"), QObject::tr("Enchant Gloves - Superior Agility"), QObject::tr("+15 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantWeaponAgility, QObject::tr("Agility", "Enchant Weapon Agility"), QObject::tr("Enchant Weapon - Agility"), QObject::tr("+15 Agility")),
        new EnchantSpec(EnchantName::Name::EnchantWeaponSpellPower, QObject::tr("Spell Power", "Enchant Weapon Spell Power"), QObject::tr("Enchant Weapon - Spell Power"), QObject::tr("+30 Spell Damage/Healing")),
        new EnchantSpec(EnchantName::Name::EnchantWeaponStrength, QObject::tr("Strength", "Enchant Weapon Strength"), QObject::tr("Enchant Weapon - Strength"), QObject::tr("+15 Strength")),
        new EnchantSpec(EnchantName::Name::FalconsCall, QObject::tr("Falcon's Call"), QObject::tr("Falcons Call"), QObject::tr("+24 Ranged Attack Power\n10 Stamina, +1% Hit")),
        new EnchantSpec(EnchantName::Name::FieryWeapon, QObject::tr("Fiery Weapon"), QObject::tr("Enchant Weapon - Fiery Weapon"), QObject::tr("Fiery Weapon")),
        new EnchantSpec(EnchantName::Name::InstantPoison, QObject::tr("Instant Poison"), QObject::tr("Instant Poison"), QObject::tr("Instant Poison")),
        new EnchantSpec(EnchantName::Name::IronCounterweight, QObject::tr("Iron Counterweight"), QObject::tr("Iron Counterweight"), QObject::tr("+3% Attack Speed")),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityAgility, QObject::tr("Lesser Arcanum Of Voracity - Agility"),
                        QObject::tr("Lesser Arcanum Of Voracity - Agility"), QObject::tr("+8 Agility")),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityIntellect, QObject::tr("Lesser Arcanum Of Voracity - Intellect"),
                        QObject::tr("Lesser Arcanum Of Voracity - Intellect"), QObject::tr("+8 Intellect")),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracitySpirit, QObject::tr("Lesser Arcanum Of Voracity - Spirit"),
                        QObject::tr("Lesser Arcanum Of Voracity - Spirit"), QObject::tr("+8 Spirit")),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityStamina, QObject::tr("Lesser Arcanum Of Voracity - Stamina"),
                        QObject::tr("Lesser Arcanum Of Voracity - Stamina"), QObject::tr("+8 Stamina")),
        new EnchantSpec(EnchantName::Name::LesserArcanumOfVoracityStrength, QObject::tr("Lesser Arcanum Of Voracity - Strength"),
                        QObject::tr("Lesser Arcanum Of Voracity - Strength"), QObject::tr("+8 Strength")),
        new EnchantSpec(EnchantName::Name::LesserManaOil, QObject::tr("Lesser Mana Oil"), QObject::tr("Lesser Mana Oil"), QObject::tr("+8 mp5")),
        new EnchantSpec(EnchantName::Name::MightOfTheScourge, QObject::tr("Might of the Scourge"), QObject::tr("Might of the Scourge"), QObject::tr("+1% Crit and\n+26 Attack Power")),
        new EnchantSpec(EnchantName::Name::PowerOfTheScourge, QObject::tr("Power Of The Scourge"), QObject::tr("Power Of The Scourge"),
                        QObject::tr("+15 Spell Damage/Healing\n+1% Spell Crit")),
        new EnchantSpec(EnchantName::Name::PresenceOfSight, QObject::tr("Presence Of Sight"), QObject::tr("Presence Of Sight"), QObject::tr("+18 Spell Damage/Healing\n+1% Spell Hit")),
        new EnchantSpec(EnchantName::Name::ShadowOil, QObject::tr("Shadow Oil"), QObject::tr("Shadow Oil"), QObject::tr("15% R3 Shadow Bolt")),
        new EnchantSpec(EnchantName::Name::SniperScope, QObject::tr("Sniper Scope"), QObject::tr("Sniper Scope"), QObject::tr("+7 Damage")),
        new EnchantSpec(EnchantName::Name::SolidWeightstone, QObject::tr("Solid Weightstone"), QObject::tr("Solid Weightstone"), QObject::tr("+6 Damage")),
        new EnchantSpec(EnchantName::Name::SuperiorStriking, QObject::tr("Superior Striking"), QObject::tr("Enchant Weapon - Superior Striking"), QObject::tr("+5 Damage")),
        new EnchantSpec(EnchantName::Name::WindfuryTotem, QObject::tr("Windfury Totem"), QObject::tr("Windfury Totem"), QObject::tr("Windfury")),
        new EnchantSpec(EnchantName::Name::ZandalarSignetOfMight, QObject::tr("Zandalar Signet Of Might"), QObject::tr("Zandalar Signet Of Might"), QObject::tr("+30 Attack Power")),
        new EnchantSpec(EnchantName::Name::ZandalarSignetOfMojo, QObject::tr("Zandalar Signet Of Mojo"), QObject::tr("Zandalar Signet Of Mojo"), QObject::tr("+18 Spell Damage/Healing")),
    };
}

EnchantInfo::~EnchantInfo() {
    for (const auto& spec : enchant_specs)
        delete spec;
}

QString EnchantInfo::get_display_name(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->display_name;
    }

    return "<failed to find enchant info>";
}

QString EnchantInfo::get_unique_name(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->unique_name;
    }

    return "<failed to find enchant info>";
}

QString EnchantInfo::get_effect(EnchantName::Name enum_val) const {
    for (const auto& spec : enchant_specs) {
        if (spec->enum_name == enum_val)
            return spec->effect;
    }

    return "<failed to find enchant info>";
}

EnchantName::Name EnchantInfo::get_enum_val(const QString& unique_name) const {
    for (const auto& spec : enchant_specs) {
        if (spec->unique_name == unique_name)
            return spec->enum_name;
    }

    return EnchantName::Name::NoEnchant;
}
