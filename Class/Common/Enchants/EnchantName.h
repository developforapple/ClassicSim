#pragma once

#include <QObject>

#include "Utils/Check.h"

class EnchantName : public QObject {
    Q_OBJECT

public:
    enum Name
    {
        NoEnchant = -1,
        Crusader,
        FieryWeapon,
        SuperiorStriking,
        EnchantWeaponAgility,
        EnchantWeaponStrength,
        EnchantWeaponSpellPower,
        IronCounterweight,
        Enchant2HWeaponAgility,
        Enchant2HWeaponSuperiorImpact,
        Biznicks247x128Accurascope,
        SniperScope,
        FalconsCall,
        InstantPoison,
        WindfuryTotem,
        EnchantBracerGreaterIntellect,
        EnchantBracerManaRegeneration,
        EnchantBracerMinorAgility,
        EnchantBracerGreaterStrength,
        EnchantBracerSuperiorStrength,
        EnchantGlovesSuperiorAgility,
        EnchantGlovesGreaterAgility,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        EnchantGlovesFirePower,
        EnchantGlovesFrostPower,
        ArcanumOfFocus,
        ArcanumOfRapidity,
        LesserArcanumOfVoracityAgility,
        LesserArcanumOfVoracityIntellect,
        LesserArcanumOfVoracitySpirit,
        LesserArcanumOfVoracityStamina,
        LesserArcanumOfVoracityStrength,
        DeathsEmbrace,
        PresenceOfSight,
        EnchantCloakLesserAgility,
        ZandalarSignetOfMight,
        ZandalarSignetOfMojo,
        MightOfTheScourge,
        EnchantChestStats,
        EnchantChestGreaterStats,
        EnchantBootsMinorSpeed,
        EnchantBootsGreaterAgility,
        EnchantBootsAgility,
        EnchantBootsSpirit,
        ElementalSharpeningStone,
        ConsecratedSharpeningStone,
        DenseSharpeningStone,
        LesserManaOil,
        BrilliantManaOil,
        BrilliantWizardOil,
        ShadowOil,
        SolidWeightstone,
        DenseWeightstone,
    };

    Q_ENUM(Name)

    static QString get_name(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            check(false, "Requested enchant name for EnchantName::NoEnchant");
            return QObject::tr("no enchant");
        case EnchantName::Crusader:
            return QObject::tr("Crusader");
        case EnchantName::FieryWeapon:
            return QObject::tr("Fiery Weapon");
        case EnchantName::WindfuryTotem:
            return QObject::tr("Windfury Totem");
        case EnchantName::InstantPoison:
            return QObject::tr("Instant Poison");
        case EnchantName::SuperiorStriking:
            return QObject::tr("Superior Striking");
        case EnchantName::EnchantWeaponAgility:
            return QObject::tr("Agility", "Enchant Weapon Agility");
        case EnchantName::EnchantWeaponStrength:
            return QObject::tr("Strength", "Enchant Weapon Strength");
        case EnchantName::EnchantWeaponSpellPower:
            return QObject::tr("Spell Power", "Enchant Weapon Spell Power");
        case EnchantName::EnchantBracerGreaterIntellect:
            return QObject::tr("Greater Intellect", "Enchant Bracer Greater Intellect");
        case EnchantName::EnchantBracerManaRegeneration:
            return QObject::tr("Mana Regeneration", "Enchant Bracer Mana Regeneration");
        case EnchantName::EnchantBracerMinorAgility:
            return QObject::tr("Minor Agility", "Enchant Bracer Minor Agility");
        case EnchantName::EnchantBracerGreaterStrength:
            return QObject::tr("Greater Strength", "Enchant Bracer Greater Strength");
        case EnchantName::EnchantBracerSuperiorStrength:
            return QObject::tr("Superior Strength", "Enchant Bracer Superior Strength");
        case EnchantName::EnchantGlovesSuperiorAgility:
            return QObject::tr("Superior Agility", "Enchant Gloves Superior Agility");
        case EnchantName::EnchantGlovesGreaterAgility:
            return QObject::tr("Greater Agility", "Enchant Gloves Greater Agility");
        case EnchantName::EnchantGlovesGreaterStrength:
            return QObject::tr("Greater Strength", "Enchant Gloves Greater Strength");
        case EnchantName::EnchantGlovesMinorHaste:
            return QObject::tr("Minor Haste", "Enchant Gloves Minor Haste");
        case EnchantName::EnchantGlovesFirePower:
            return QObject::tr("Fire Power", "Enchant Gloves Fire Power");
        case EnchantName::EnchantGlovesFrostPower:
            return QObject::tr("Frost Power", "Enchant Gloves Frost Power");
        case EnchantName::IronCounterweight:
            return QObject::tr("Iron Counterweight");
        case EnchantName::Enchant2HWeaponAgility:
            return QObject::tr("2H Weapon Agility");
        case EnchantName::Enchant2HWeaponSuperiorImpact:
            return QObject::tr("2H Weapon Superior Impact");
        case EnchantName::Biznicks247x128Accurascope:
            return QObject::tr("Biznicks 247x128 Accurascope");
        case EnchantName::SniperScope:
            return QObject::tr("Sniper Scope");
        case EnchantName::ArcanumOfFocus:
            return QObject::tr("Arcanum of Focus");
        case EnchantName::ArcanumOfRapidity:
            return QObject::tr("Arcanum of Rapidity");
        case EnchantName::LesserArcanumOfVoracityAgility:
        case EnchantName::LesserArcanumOfVoracityIntellect:
        case EnchantName::LesserArcanumOfVoracitySpirit:
        case EnchantName::LesserArcanumOfVoracityStamina:
        case EnchantName::LesserArcanumOfVoracityStrength:
            return QObject::tr("Lesser Arcanum of Voracity");
        case EnchantName::DeathsEmbrace:
            return QObject::tr("Death's Embrace");
        case EnchantName::FalconsCall:
            return QObject::tr("Falcon's Call");
        case EnchantName::PresenceOfSight:
            return QObject::tr("Presence of Sight");
        case EnchantName::EnchantCloakLesserAgility:
            return QObject::tr("Lesser Agility", "Enchant Cloak Lesser Agility");
        case EnchantName::ZandalarSignetOfMight:
            return QObject::tr("Zandalar Signet of Might");
        case EnchantName::ZandalarSignetOfMojo:
            return QObject::tr("Zandalar Signet of Mojo");
        case EnchantName::MightOfTheScourge:
            return QObject::tr("Might of the Scourge");
        case EnchantName::EnchantChestStats:
            return QObject::tr("Stats", "Enchant Chest Stats");
        case EnchantName::EnchantChestGreaterStats:
            return QObject::tr("Greater Stats", "Enchant Chest Greater Stats");
        case EnchantName::EnchantBootsMinorSpeed:
            return QObject::tr("Minor Speed");
        case EnchantName::EnchantBootsAgility:
            return QObject::tr("Agility", "Enchant Boots Agility");
        case EnchantName::EnchantBootsGreaterAgility:
            return QObject::tr("Greater Agility", "Enchant Boots Greater Agility");
        case EnchantName::EnchantBootsSpirit:
            return QObject::tr("Spirit", "Enchant Boots Spirit");
        case EnchantName::ElementalSharpeningStone:
            return QObject::tr("Elemental Sharpening Stone");
        case EnchantName::ConsecratedSharpeningStone:
            return QObject::tr("Consecrated Sharpening Stone");
        case EnchantName::DenseSharpeningStone:
            return QObject::tr("Dense Sharpening Stone");
        case EnchantName::LesserManaOil:
            return QObject::tr("Lesser Mana Oil");
        case EnchantName::BrilliantManaOil:
            return QObject::tr("Brilliant Mana Oil");
        case EnchantName::BrilliantWizardOil:
            return QObject::tr("Brilliant Wizard Oil");
        case EnchantName::ShadowOil:
            return QObject::tr("Shadow Oil");
        case EnchantName::SolidWeightstone:
            return QObject::tr("Solid Weightstone");
        case EnchantName::DenseWeightstone:
            return QObject::tr("Dense Weightstone");
        }

        check(false, "EnchantName::get_name reached end of switch");
        return "";
    }

    static QString get_effect(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            check(false, "Requested tooltip effect for EnchantName::NoEnchant");
            return QObject::tr("no enchant");
        case EnchantName::Crusader:
            return QObject::tr("Crusader");
        case EnchantName::FieryWeapon:
            return QObject::tr("Fiery Weapon");
        case EnchantName::WindfuryTotem:
            return QObject::tr("Windfury Totem");
        case EnchantName::InstantPoison:
            return QObject::tr("Instant Poison");
        case EnchantName::SuperiorStriking:
            return QObject::tr("+5 Damage");
        case EnchantName::EnchantWeaponAgility:
            return QObject::tr("+15 Agility");
        case EnchantName::EnchantWeaponStrength:
            return QObject::tr("+15 Strength");
        case EnchantName::EnchantWeaponSpellPower:
            return QObject::tr("+30 Spell Damage/Healing");
        case EnchantName::EnchantBracerGreaterIntellect:
            return QObject::tr("+7 Intellect");
        case EnchantName::EnchantBracerManaRegeneration:
            return QObject::tr("+4 mp5");
        case EnchantName::EnchantBracerMinorAgility:
            return QObject::tr("+1 Agility");
        case EnchantName::EnchantBracerGreaterStrength:
            return QObject::tr("+7 Strength");
        case EnchantName::EnchantBracerSuperiorStrength:
            return QObject::tr("+9 Strength");
        case EnchantName::EnchantGlovesSuperiorAgility:
            return QObject::tr("+15 Agility");
        case EnchantName::EnchantGlovesGreaterAgility:
            return QObject::tr("+7 Agility");
        case EnchantName::EnchantGlovesGreaterStrength:
            return QObject::tr("+7 Strength");
        case EnchantName::EnchantGlovesMinorHaste:
            return QObject::tr("+1% Attack Speed");
        case EnchantName::EnchantGlovesFirePower:
            return QObject::tr("+20 Fire Damage");
        case EnchantName::EnchantGlovesFrostPower:
            return QObject::tr("+20 Frost Damage");
        case EnchantName::IronCounterweight:
            return QObject::tr("+3% Attack Speed");
        case EnchantName::Enchant2HWeaponAgility:
            return QObject::tr("+25 Agility");
        case EnchantName::Enchant2HWeaponSuperiorImpact:
            return QObject::tr("+9 Damage");
        case EnchantName::Biznicks247x128Accurascope:
            return QObject::tr("+3% Ranged Hit");
        case EnchantName::SniperScope:
            return QObject::tr("+7 Damage");
        case EnchantName::ArcanumOfFocus:
            return QObject::tr("+8 Spell Damage/Healing");
        case EnchantName::ArcanumOfRapidity:
            return QObject::tr("+1% Haste");
        case EnchantName::LesserArcanumOfVoracityAgility:
            return QObject::tr("+8 Agility");
        case EnchantName::LesserArcanumOfVoracityIntellect:
            return QObject::tr("+8 Intellect");
        case EnchantName::LesserArcanumOfVoracitySpirit:
            return QObject::tr("+8 Spirit");
        case EnchantName::LesserArcanumOfVoracityStamina:
            return QObject::tr("+8 Stamina");
        case EnchantName::LesserArcanumOfVoracityStrength:
            return QObject::tr("+8 Strength");
        case EnchantName::DeathsEmbrace:
            return QObject::tr("+28 Attack and\n1% Dodge");
        case EnchantName::PresenceOfSight:
            return QObject::tr("+18 Spell Damage/Healing\n+1% Spell Hit");
        case EnchantName::FalconsCall:
            return QObject::tr("+24 Ranged Attack Power\n10 Stamina, +1% Hit");
        case EnchantName::EnchantCloakLesserAgility:
            return QObject::tr("+3 Agility");
        case EnchantName::ZandalarSignetOfMight:
            return QObject::tr("+30 Attack Power");
        case EnchantName::ZandalarSignetOfMojo:
            return QObject::tr("+18 Spell Damage/Healing");
        case EnchantName::MightOfTheScourge:
            return QObject::tr("+1% Crit and\n+26 Attack Power");
        case EnchantName::EnchantChestStats:
            return QObject::tr("+3 Attributes");
        case EnchantName::EnchantChestGreaterStats:
            return QObject::tr("+4 Attributes");
        case EnchantName::EnchantBootsMinorSpeed:
            return QObject::tr("Speed Increase");
        case EnchantName::EnchantBootsAgility:
            return QObject::tr("+5 Agility");
        case EnchantName::EnchantBootsGreaterAgility:
            return QObject::tr("+7 Agility");
        case EnchantName::EnchantBootsSpirit:
            return QObject::tr("+5 Spirit");
        case EnchantName::ElementalSharpeningStone:
            return QObject::tr("+2% Crit");
        case EnchantName::ConsecratedSharpeningStone:
            return QObject::tr("+100 AP\nvs Undead");
        case EnchantName::DenseSharpeningStone:
            return QObject::tr("+8 Damage");
        case EnchantName::LesserManaOil:
            return QObject::tr("+8 mp5");
        case EnchantName::BrilliantManaOil:
            return QObject::tr("+12mp5/+25 Heal");
        case EnchantName::BrilliantWizardOil:
            return QObject::tr("+36 SP\n+1% Spell Crit");
        case EnchantName::ShadowOil:
            return QObject::tr("15% R3 Shadow Bolt");
        case EnchantName::SolidWeightstone:
            return QObject::tr("+6 Damage");
        case EnchantName::DenseWeightstone:
            return QObject::tr("+8 Damage");
        }

        check(false, "EnchantName::get_effect reached end of switch");
        return "";
    }
};
