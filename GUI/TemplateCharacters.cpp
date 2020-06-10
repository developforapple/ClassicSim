#include "TemplateCharacters.h"
#include <QObject>
#include "Utils/Check.h"

TemplateCharacterInfo TemplateCharacters::template_character_info(const QString& template_char) {
    QString warrior_buffs = QString("BUFFS[")
            + QObject::tr("Strength of Earth Totem") + "=N/A:"
            + QObject::tr("Mark of the Wild") + "=N/A:"
            + QObject::tr("Dragonbreath Chili") + "=N/A:"
            + QObject::tr("Elixir of Brute Force") + "=N/A:"
            + QObject::tr("Elixir of the Mongoose") + "=N/A:"
            + QObject::tr("Juju Might") + "=N/A:"
            + QObject::tr("Juju Power") + "=N/A:"
            + QObject::tr("Scroll of Strength IV") + "=N/A:"
            + QObject::tr("Battle Squawk") + "=N/A:"
            + QObject::tr("Rallying Cry of the Dragonslayer") + "=N/A:"
            + QObject::tr("Songflower Serenade") + "=N/A]";
    QString warrior_debuffs = QString("DEBUFFS[")
            + QObject::tr("Sunder Armor") + "=N/A:"
            + QObject::tr("Curse of Recklessness") + "=N/A:"
            + QObject::tr("Faerie Fire") + "=N/A:"
            + QObject::tr("Annihilator Proc") + "=N/A:"
            + QObject::tr("Improved Shadow Bolt") + "=N/A:"
            + QObject::tr("Fire Vulnerability") + "=N/A]";
    QString target = "TARGET_LVL=63|TARGET_TYPE=" + QObject::tr("Beast") + "|TARGET_BASE_ARMOR=3750";

    if (template_char == QObject::tr("Warrior DW Fury Pre-Raid"))
        return TemplateCharacterInfo(
            "Warrior",
            QString("PHASE=%1|RACE=Orc|CLASS=Warrior|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=811|OFFHAND=871|RANGED=12651|HEAD=12587|NECK=17044|SHOULDERS="
                    "12927|BACK=13340|CHEST=11726|WRIST=12936|GLOVES=15063|BELT=13959001|LEGS=15062|BOOTS=11731|RING1=17713|RING2=13098|TRINKET1=11815|"
                    "TRINKET2=13965|LEFT[1LL=2:1MR=3:2ML=5:3LL=2:3MR=3:4MR=2]|MID[1MR=5:2MR=5:3RR=5:4LL=5:4ML=2:4MR=5:5ML=1:6MR=5:7ML=1]|")
            + warrior_buffs + "|" + warrior_debuffs + "|" + target
            + "|ROTATION=" + QObject::tr("DW Fury High Rage")
            + "|MH_TEMPORARY_ENCHANT=13|MH_ENCHANT=0|OH_TEMPORARY_ENCHANT=41|OH_ENCHANT=0|HEAD_ENCHANT=-1|SHOULDER_ENCHANT=-1|BACK_ENCHANT=31|"
              "CHEST_ENCHANT=35|WRIST_ENCHANT=-1|GLOVES_ENCHANT=18|LEGS_ENCHANT=-1|BOOTS_ENCHANT=36|RANGED_ENCHANT=-1|RULESET=0");

    if (template_char == QObject::tr("Warrior DW Fury BWL"))
        return TemplateCharacterInfo(
            "Warrior",
            QString("PHASE=%1|RACE=Orc|CLASS=Warrior|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=19363|OFFHAND=871|RANGED=12651|HEAD=12640|NECK=18404|SHOULDERS="
                    "12927|BACK=13340|CHEST=11726|WRIST=18812|GLOVES=15063|BELT=19137|LEGS=15062|BOOTS=19387|RING1=19325|RING2=19384|TRINKET1=11815|"
                    "TRINKET2=19406|LEFT[1LL=2:1MR=3:2ML=5:3LL=2:3MR=3:4MR=2]|MID[1MR=5:2MR=5:3RR=5:4LL=5:4ML=2:4MR=5:5ML=1:6MR=5:7ML=1]|")
            + warrior_buffs + "|" + warrior_debuffs + "|" + target
            + "|ROTATION=" + QObject::tr("DW Fury High Rage")
            + "|MH_TEMPORARY_ENCHANT=13|MH_ENCHANT=0|OH_TEMPORARY_ENCHANT=41|OH_ENCHANT=0|HEAD_ENCHANT=23|SHOULDER_ENCHANT=-1|BACK_ENCHANT=31|"
              "CHEST_ENCHANT=35|WRIST_ENCHANT=16|GLOVES_ENCHANT=18|LEGS_ENCHANT=23|BOOTS_ENCHANT=36|RANGED_ENCHANT=-1|RULESET=0");

    if (template_char == QObject::tr("Warrior DW Fury AQ"))
        return TemplateCharacterInfo(
            "Warrior",
            QString("PHASE=%1|RACE=Orc|CLASS=Warrior|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=19363|OFFHAND=871|RANGED=17069|HEAD=12640|NECK=18404|SHOULDERS="
                    "21330|BACK=21701|CHEST=11726|WRIST=18812|GLOVES=21581|BELT=19137|LEGS=22385|BOOTS=19387|RING1=19325|RING2=19384|TRINKET1=11815|"
                    "TRINKET2=19406|LEFT[1LL=2:1MR=3:2ML=5:3LL=2:3MR=3:4MR=2]|MID[1MR=5:2MR=5:3RR=5:4LL=5:4ML=2:4MR=5:5ML=1:6MR=5:7ML=1]|")
            + warrior_buffs + "|" + warrior_debuffs + "|" + target
            + "|ROTATION=" + QObject::tr("DW Fury High Rage")
            + "|MH_TEMPORARY_ENCHANT=13|MH_ENCHANT=0|OH_TEMPORARY_ENCHANT=39|OH_ENCHANT=0|HEAD_ENCHANT=23|SHOULDER_ENCHANT=32|BACK_ENCHANT=31|"
              "CHEST_ENCHANT=35|WRIST_ENCHANT=16|GLOVES_ENCHANT=18|LEGS_ENCHANT=23|BOOTS_ENCHANT=36|RANGED_ENCHANT=-1|RULESET=0");

    if (template_char == QObject::tr("Warrior DW Fury Naxx"))
        return TemplateCharacterInfo(
            "Warrior",
            QString("PHASE=%1|RACE=Orc|CLASS=Warrior|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=22816|OFFHAND=871|RANGED=17069|HEAD=12640|NECK=18404|SHOULDERS="
                    "21330|BACK=21701|CHEST=23000|WRIST=22936|GLOVES=21581|BELT=23219|LEGS=23068|BOOTS=19387|RING1=23038|RING2=19384|TRINKET1=22954|"
                    "TRINKET2=19406|LEFT[1LL=2:1MR=3:2ML=5:3LL=2:3MR=3:4MR=2]|MID[1MR=5:2MR=5:3RR=5:4LL=5:4ML=2:4MR=5:5ML=1:6MR=5:7ML=1]|")
            + warrior_buffs + "|" + warrior_debuffs + "|" + target
            + "|ROTATION=" + QObject::tr("DW Fury High Rage")
            + "|MH_TEMPORARY_ENCHANT=13|MH_ENCHANT=0|OH_TEMPORARY_ENCHANT=39|OH_ENCHANT=0|HEAD_ENCHANT=23|SHOULDER_ENCHANT=32|BACK_ENCHANT=31|"
              "CHEST_ENCHANT=35|WRIST_ENCHANT=16|GLOVES_ENCHANT=18|LEGS_ENCHANT=23|BOOTS_ENCHANT=36|RANGED_ENCHANT=-1|RULESET=0");

    if (template_char == QObject::tr("Hunter 8/8 T2"))
        return TemplateCharacterInfo(
            "Hunter",
            QString("PHASE=%1|RACE=Dwarf|CLASS=Hunter|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=19364|RANGED=19361|HEAD=16939|NECK=19377|SHOULDERS=16937|BACK="
                    "21710|CHEST=16942|WRIST=16935|GLOVES=16940|BELT=16936|LEGS=16938|BOOTS=16941|RING1=21205|RING2=19384|TRINKET1=21670|TRINKET2=21180|"
                    "QUIVER=18714|PROJECTILE=12654|LEFT[1ML=5:2MR=3:2RR=2:3MR=5:4MR=2]|MID[1MR=5:2ML=2:2MR=5:3LL=1:3RR=3:4MR=5:5LL=1:5ML=3:6MR=5:7ML=1]|"
                    "RIGHT[1LL=3]|BUFFS[")
            + QObject::tr("Greater Blessing of Might") + "=N/A:"
            + QObject::tr("Greater Blessing of Kings") + "=N/A:"
            + QObject::tr("Greater Blessing of Wisdom") + "=N/A:"
            + QObject::tr("Mark of the Wild") + "=N/A:"
            + QObject::tr("Nightfin Soup") + "=N/A:"
            + QObject::tr("Mageblood Potion") + "=N/A:"
            + QObject::tr("Elixir of Brute Force") + "=N/A:"
            + QObject::tr("Elixir of Giants") + "=N/A:"
            + QObject::tr("Elixir of the Mongoose") + "=N/A:"
            + QObject::tr("Winterfall Firewater") + "=N/A:"
            + QObject::tr("Scroll of Strength IV") + "=N/A:"
            + QObject::tr("Ground Scorpok Assay") + "=N/A:"
            + QObject::tr("Battle Squawk") + "=N/A:"
            + QObject::tr("Slip'kik's Savvy") + "=N/A:"
            + QObject::tr("Fengus' Ferocity") + "=N/A:"
            + QObject::tr("Rallying Cry of the Dragonslayer") + "=N/A:"
            + QObject::tr("Songflower Serenade") + "=N/A:"
            + QObject::tr("Spirit of Zandalar") + "=N/A]"
            + "|DEBUFFS["
            + QObject::tr("Sunder Armor") + "=N/A:"
            + QObject::tr("Curse of Recklessness") + "=N/A:"
            + QObject::tr("Faerie Fire") + "=N/A:"
            + QObject::tr("Annihilator Proc") + "=N/A:"
            + QObject::tr("Improved Shadow Bolt") + "=N/A:"
            + QObject::tr("Fire Vulnerability") + "=N/A]"
            + target
            + "|ROTATION=" + QObject::tr("Aimed/Multi-Shot")
            + "|MH_TEMPORARY_ENCHANT=43|MH_ENCHANT=7|HEAD_ENCHANT=11|SHOULDER_ENCHANT=32|BACK_ENCHANT=31|CHEST_ENCHANT=35|WRIST_ENCHANT="
              "14|GLOVES_ENCHANT=17|LEGS_ENCHANT=11|BOOTS_ENCHANT=36|RANGED_ENCHANT=10|RULESET=0");

    if (template_char == QObject::tr("Fire Mage T3"))
        return TemplateCharacterInfo(
            "Mage",
            QString("PHASE=%1|RACE=Gnome|CLASS=Mage|PARTY=%2|PARTY_MEMBER=%3|MAINHAND=22807|HEAD=22498|NECK=22943|SHOULDERS=22499|BACK=23017|CHEST=22496|"
                    "WRIST=22503|GLOVES=22501|BELT=22502|LEGS=22497|BOOTS=22500|RING1=23062|RING2=21709|TRINKET1=19379|TRINKET2=19339|LEFT[1LL=2:1MR=3:"
                    "2ML=2:2MR=5:3LL=2:3MR=1:4RR=2]|MID[1ML=5:2LL=5:2ML=2:3MR=1:3RR=2:4LL=3:4RR=3:5ML=3:5MR=1:6MR=5:7ML=1]|RIGHT[1MR=3]|BUFFS[")
            + QObject::tr("Greater Blessing of Kings") + "=N/A:"
            + QObject::tr("Greater Blessing of Wisdom") + "=N/A:"
            + QObject::tr("Mark of the Wild") + "=N/A:"
            + QObject::tr("Nightfin Soup") + "=N/A:"
            + QObject::tr("Mageblood Potion") + "=N/A:"
            + QObject::tr("Greater Arcane Elixir") + "=N/A:"
            + QObject::tr("Flask of Supreme Power") + "=N/A:"
            + QObject::tr("Slip'kik's Savvy") + "=N/A:"
            + QObject::tr("Rallying Cry of the Dragonslayer") + "=N/A:"
            + QObject::tr("Songflower Serenade") + "=N/A:"
            + QObject::tr("Spirit of Zandalar") + "=N/A:"
            + QObject::tr("Sayge's Dark Fortune of Damage") + "=N/A]"
            "|DEBUFFS["
            + QObject::tr("Sunder Armor") + "=N/A:"
            + QObject::tr("Curse of Recklessness") + "=N/A:"
            + QObject::tr("Faerie Fire") + "=N/A:"
            + QObject::tr("Annihilator Proc") + "=N/A:"
            + QObject::tr("Improved Shadow Bolt") + "=N/A]"
            + target
            + "|ROTATION=" + QObject::tr("Fire")
            + "|MH_TEMPORARY_ENCHANT=44|MH_ENCHANT=5|HEAD_ENCHANT=30|SHOULDER_ENCHANT=33|BACK_ENCHANT=-1|CHEST_ENCHANT=35|WRIST_ENCHANT="
              "14|GLOVES_ENCHANT=20|LEGS_ENCHANT=30|BOOTS_ENCHANT=36|RULESET=0");

    check(false, QString("Missing template '%1'").arg(template_char).toStdString());
    return TemplateCharacterInfo("Warrior", "");
}
