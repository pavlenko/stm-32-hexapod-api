#include <PE_Servo180v2.h>
#include <stdio.h>
#include <unity.h>

void test_PE_Servo180_dispatchTimer_0() {
    volatile uint16_t compare;
    volatile uint16_t counter;

    PE_Servo180_Timer_t timer = {.compare = &compare, .counter = &counter};

    PE_Servo180_dispatchTimer(&timer);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_dispatchTimer_0);
    return UNITY_END();
}

