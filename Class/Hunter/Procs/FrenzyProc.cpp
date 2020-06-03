#include "FrenzyProc.h"
#include <QObject>
#include "FrenzyBuff.h"
#include "Pet.h"
#include "ProcInfo.h"

FrenzyProc::FrenzyProc(Character* pchar, Pet* pet) :
    Proc(QObject::tr("Frenzy (%1)").arg(pet->get_name()),
         "Assets/items/Inv_misc_monsterclaw_03.png",
         0.0,
         0,
         QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::Manual}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*> {new TalentRequirerInfo(QObject::tr("Frenzy"), 5, DisabledAtZero::Yes)}),
    frenzy_buff(new FrenzyBuff(pchar, pet)),
    talent_ranks({0, 2000, 4000, 6000, 8000, 10000}) {
    this->enabled = false;
    proc_range = talent_ranks[0];
}

FrenzyProc::~FrenzyProc() {
    if (frenzy_buff->is_enabled())
        frenzy_buff->disable_buff();
    if (is_enabled()) {
        disable();
        disable_proc();
    }

    delete frenzy_buff;
}

void FrenzyProc::proc_effect() {
    frenzy_buff->apply_buff();
}

void FrenzyProc::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];

    if (curr == 1)
        frenzy_buff->enable_buff();
}

void FrenzyProc::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr];

    if (curr == 0)
        frenzy_buff->disable_buff();
}
