#include "SealFate.h"
#include <QObject>
#include "ProcInfo.h"
#include "Rogue.h"

SealFate::SealFate(Rogue* rogue) :
    Proc(QObject::tr("Seal Fate"),
         "Assets/spell/Spell_shadow_chilltouch.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         rogue),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Seal Fate"), 5, DisabledAtZero::Yes)}),
    rogue(rogue),
    talent_ranks({0, 2000, 4000, 6000, 8000, 10000}) {
    this->enabled = false;
    proc_range = talent_ranks[0];
}

void SealFate::proc_effect() {
    rogue->gain_combo_points(1);
}

void SealFate::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}

void SealFate::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];
}
