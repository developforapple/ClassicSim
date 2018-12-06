#include "Assassination.h"

#include "GenericTalent.h"
#include "ImprovedEviscerate.h"
#include "ImprovedSliceAndDice.h"
#include "Lethality.h"
#include "Malice.h"
#include "Murder.h"
#include "RelentlessStrikesTalent.h"
#include "RuthlessnessTalent.h"
#include "SealFateTalent.h"
#include "Talent.h"
#include "Vigor.h"

Assassination::Assassination(Character *pchar) :
    TalentTree("Assassination", "Assets/rogue/rogue_assassination.jpg")
{
    QMap<QString, Talent*> tier1 {{"1LL", new ImprovedEviscerate(pchar, this)},
                                  {"1ML", new GenericTalent(pchar, this, "Remorseless Attacks", "1ML", "Assets/ability/Ability_fiegndead.png", 2, "After killing an opponent that yields experience or honor, gives you a %1 increased critical strike chance on your next Sinister Strike, Backstab, Ambush, or Ghostly Strike. Lasts 20 sec.", QVector<QPair<int, int>>{QPair<int, int>(20, 20)})},
                                  {"1MR", new Malice(pchar, this)}};
    add_talents(tier1);

    QMap<QString, Talent*> tier2 {{"2LL", new RuthlessnessTalent(pchar, this)},
                                  {"2ML", new Murder(pchar, this)},
                                  {"2RR", new ImprovedSliceAndDice(pchar, this)}};
    add_talents(tier2);

    QMap<QString, Talent*> tier3 {{"3LL", new RelentlessStrikesTalent(pchar, this)},
                                  {"3ML", new GenericTalent(pchar, this, "Improved Expose Armor", "3ML", "Assets/ability/Ability_warrior_riposte.png", 2, "Increases the armor reduced by your Expose Armor ability by %1%.", QVector<QPair<int, int>>{QPair<int, int>(25, 25)})},
                                  {"3MR", new Lethality(pchar, this)}};
    add_talents(tier3);

    QMap<QString, Talent*> tier4 {{"4ML", new GenericTalent(pchar, this, "Vile Poisons", "4ML", "Assets/ability/Ability_rogue_feigndeath.png", 5, "Increases the damage dealt by your poisons by %1% and gives your poisons an additional %2% chance to resist dispel effects.", QVector<QPair<int, int>>{QPair<int, int>(4, 4), QPair<int, int>(8, 8)})},
                                  {"4MR", new GenericTalent(pchar, this, "Improved Poisons", "4MR", "Assets/ability/Ability_poisons.png", 5, "Increases the chance to apply poisons to your target by %1%.", QVector<QPair<int, int>>{QPair<int, int>(2, 2)})}};
    add_talents(tier4);

    QMap<QString, Talent*> tier5 {{"5ML", new GenericTalent(pchar, this, "Cold Blood", "5ML", "Assets/spell/Spell_ice_lament.png", 1, "When activated, increases the critical strike chance of your next Sinister Strike, Backstab, Ambush, or Eviscerate by 100%.", QVector<QPair<int, int>>())},
                                  {"5MR", new GenericTalent(pchar, this, "Improved Kidney Shot", "5MR", "Assets/ability/Ability_rogue_kidneyshot.png", 3, "While affected by your Kidney Shot ability, the target receives an additional %1% damage from all sources.", QVector<QPair<int, int>>{QPair<int, int>(3, 3)})}};
    add_talents(tier5);

    QMap<QString, Talent*> tier6 {{"6ML", new SealFateTalent(pchar, this)}};
    add_talents(tier6);

    QMap<QString, Talent*> tier7 {{"7ML", new Vigor(pchar, this)}};
    add_talents(tier7);

    talents["1MR"]->talent->set_bottom_child(talents["3MR"]->talent);
    talents["3MR"]->talent->set_parent(talents["1MR"]->talent);

    talents["5ML"]->talent->set_bottom_child(talents["6ML"]->talent);
    talents["6ML"]->talent->set_parent(talents["5ML"]->talent);
}

Assassination::~Assassination() = default;