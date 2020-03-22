#include <PE_Servo180v2.h>
#include <stdio.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

uint8_t PE_Servo180_setMotorPin0ID = 0;
void PE_Servo180_setMotorPin0(uint8_t id) {
    PE_Servo180_setMotorPin0ID = id;
}

uint8_t PE_Servo180_setMotorPin1ID = 0;
void PE_Servo180_setMotorPin1(uint8_t id) {
    PE_Servo180_setMotorPin1ID = id;
}

void test_PE_Servo180_dispatchTimer_0() {
    volatile uint16_t compare = 10;
    volatile uint16_t counter = 10;

    PE_Servo180_Timer_t timer = {.motorIndex = -1, .compare = &compare, .counter = &counter};

    PE_Servo180_dispatchTimer(&timer);

    TEST_ASSERT_EQUAL(0, counter);
    TEST_ASSERT_EQUAL(PE_Servo180_REFRESH_INTERVAL, compare);
    TEST_ASSERT_EQUAL(-1, timer.motorIndex);
}

void test_PE_Servo180_dispatchTimer_1() {
    volatile uint16_t compare = 0;
    volatile uint16_t counter = 0;

    PE_Servo180_Motor_t motor = {.ID = 1};
    PE_Servo180_Timer_t timer = {.compare = &compare, .counter = &counter};

    timer.motorIndex    = 0;
    timer.motorCount    = 1;
    timer.motorItems[0] = &motor;

    PE_Servo180_dispatchTimer(&timer);

    TEST_ASSERT_EQUAL(1, PE_Servo180_setMotorPin0ID);
}

void test_PE_Servo180_dispatchTimer_2() {
    volatile uint16_t compare = 0;
    volatile uint16_t counter = 0;

    PE_Servo180_Motor_t motor = {.ID = 1, .ticks = 1000};
    PE_Servo180_Timer_t timer = {.compare = &compare, .counter = &counter};

    timer.motorIndex    = -1;
    timer.motorCount    = 1;
    timer.motorItems[0] = &motor;

    PE_Servo180_dispatchTimer(&timer);

    TEST_ASSERT_EQUAL(1, PE_Servo180_setMotorPin1ID);
    TEST_ASSERT_EQUAL(motor.ticks, compare);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_dispatchTimer_0);
    RUN_TEST(test_PE_Servo180_dispatchTimer_1);
    RUN_TEST(test_PE_Servo180_dispatchTimer_2);
    return UNITY_END();
}

