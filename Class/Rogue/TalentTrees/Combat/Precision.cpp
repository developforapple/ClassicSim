#include "Precision.h"
#include <QObject>
#include "Character.h"
#include "CharacterStats.h"

Precision::Precision(Character* pchar, TalentTree* tree) : Talent(pchar, tree, QObject::tr("Precision"), "2MR", "Assets/ability/Ability_marksmanship.png", 5) {
    QString base_str = QObject::tr("Increases your chance to hit with melee weapons by %1%.");
    initialize_rank_descriptions(rank_descriptions, base_str, max_points, QVector<QPair<unsigned, unsigned>> {{1, 1}});
}

Precision::~Precision() = default;

void Precision::apply_rank_effect() {
    pchar->get_stats()->increase_melee_hit(100);
}

void Precision::remove_rank_effect() {
    pchar->get_stats()->decrease_melee_hit(100);
}
