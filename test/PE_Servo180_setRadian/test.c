#include <PE_Servo180v2.h>
#include <stdio.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_PE_Servo180_setRadian_0() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setRadian(&motor, 0);

    TEST_ASSERT_UINT16_WITHIN(5, 500, motor.ticks);
}

void test_PE_Servo180_setRadian_1() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setRadian(&motor, M_PI_2);

    TEST_ASSERT_UINT16_WITHIN(5, 1500, motor.ticks);
}

void test_PE_Servo180_setRadian_2() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setRadian(&motor, M_PI);

    TEST_ASSERT_UINT16_WITHIN(5, 2500, motor.ticks);
}

void test_PE_Servo180_setRadian_3() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setRadian(&motor, M_PI * 2);

    TEST_ASSERT_UINT16_WITHIN(5, 2500, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_setRadian_0);
    RUN_TEST(test_PE_Servo180_setRadian_1);
    RUN_TEST(test_PE_Servo180_setRadian_2);
    RUN_TEST(test_PE_Servo180_setRadian_3);
    return UNITY_END();
}
