#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_PE_Servo180_setDegree_0() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setDegree(&motor, 0);

    TEST_ASSERT_UINT16_WITHIN(5, 500, motor.ticks);
}

void test_PE_Servo180_setDegree_1() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setDegree(&motor, 90);

    TEST_ASSERT_UINT16_WITHIN(5, 1500, motor.ticks);
}

void test_PE_Servo180_setDegree_2() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setDegree(&motor, 180);

    TEST_ASSERT_UINT16_WITHIN(5, 2500, motor.ticks);
}

void test_PE_Servo180_setDegree_3() {
    PE_Servo180_Motor_t motor = {.min = 500, .max = 2500};

    PE_Servo180_setDegree(&motor, 1000);

    TEST_ASSERT_UINT16_WITHIN(5, 2500, motor.ticks);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_setDegree_0);
    RUN_TEST(test_PE_Servo180_setDegree_1);
    RUN_TEST(test_PE_Servo180_setDegree_2);
    RUN_TEST(test_PE_Servo180_setDegree_3);
    return UNITY_END();
}
