//
// Created by master on 29.01.20.
//

#include <V1/Hexapod.hpp>
#include <V1/Movement.hpp>
#include <V2/hexapod.h>
#include "main.h"

Hexapod hp = Hexapod();

int main()
{
    calculateInit();
    calculateIdle();
    calculateStep1();
    calculateStep2();
    calculateStep3();
    calculateStep4();
    calculateStep5();
    calculateStep6();
    calculateStep7();
    calculateStep8();

    hp.initialize();

    while (true) {
        hp.dispatch(1);
    }
}
