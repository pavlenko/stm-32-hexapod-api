//
// Created by master on 02.02.20.
//

#ifndef HEXAPOD_HPP
#define HEXAPOD_HPP

#include <cstdint>
#include "PE_FSM.hpp"

class Hexapod {
private:
    uint32_t updated;
public:
    void initialize();

    void dispatch(uint32_t millis);
};

#endif //HEXAPOD_HPP
