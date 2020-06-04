#include "Impale.h"
#include <QObject>
#include "Character.h"
#include "CharacterStats.h"

Impale::Impale(Character* pchar, TalentTree* tree) : Talent(pchar, tree, QObject::tr("Impale"), "4MR", "Assets/ability/Ability_searingarrow.png", 2) {
    QString base_str = QObject::tr("Increases the critical strike damage bonus of your abilities in Battle, Defensive, and Berserker stance by %1%.");
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{10, 10}});
}

Impale::~Impale() = default;

void Impale::apply_rank_effect() {
    pchar->get_stats()->increase_melee_ability_crit_dmg_mod(0.1);
}

void Impale::remove_rank_effect() {
    pchar->get_stats()->decrease_melee_ability_crit_dmg_mod(0.1);
}
