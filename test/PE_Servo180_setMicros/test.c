#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_PE_Servo180_setMicros_0() {
    PE_Servo180_Motor_t motor = {.min = 100, .max = 200};

    PE_Servo180_setMicros(&motor, 0);

    TEST_ASSERT_EQUAL(100, motor.ticks);
}

void test_PE_Servo180_setMicros_1() {
    PE_Servo180_Motor_t motor = {.min = 100, .max = 200};

    PE_Servo180_setMicros(&motor, 300);

    TEST_ASSERT_EQUAL(200, motor.ticks);
}

void test_PE_Servo180_setMicros_2() {
    PE_Servo180_Motor_t motor = {.min = 100, .max = 200};

    PE_Servo180_setMicros(&motor, 150);

    TEST_ASSERT_EQUAL(150, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_setMicros_0);
    RUN_TEST(test_PE_Servo180_setMicros_1);
    RUN_TEST(test_PE_Servo180_setMicros_2);
    return UNITY_END();
}
