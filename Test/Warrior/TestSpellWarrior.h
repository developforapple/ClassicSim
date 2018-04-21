#ifndef TESTSPELLWARRIOR_H
#define TESTSPELLWARRIOR_H

#include "TestSpell.h"

class Warrior;

class TestSpellWarrior: public TestSpell {
public:
    void set_up();
    void tear_down();

    void given_0_of_2_impale();
    void given_1_of_2_impale();
    void given_2_of_2_impale();

protected:
    Warrior* warrior;
};

#endif // TESTSPELLWARRIOR_H
