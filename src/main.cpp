//
// Created by master on 29.01.20.
//

#include <V1/Hexapod.hpp>
#include "main.h"

PE_FSM ModeFSM = PE_FSM();

int main()
{
    while (true) {
        ModeFSM.dispatch();
    }
}
