//
// Created by master on 29.01.20.
//

#include <V1/Hexapod.hpp>
#include "main.h"

Hexapod hp = Hexapod();

int main()
{
    hp.initialize();

    while (true) {
        hp.dispatch(1);
    }
}
