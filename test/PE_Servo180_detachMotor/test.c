#include <PE_Servo180v2.h>
#include <stdio.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_PE_Servo180_detachMotor_0() {
    PE_Servo180_Motor_t motor;
    PE_Servo180_Timer_t timer = {.motorCount = 0};

    PE_Servo180_Status_t status = PE_Servo180_detachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_FAILURE, status);
}

void test_PE_Servo180_detachMotor_1() {
    PE_Servo180_Motor_t motor;
    PE_Servo180_Timer_t timer = {.motorCount = 0};

    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_Status_t status = PE_Servo180_detachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_detachMotor_0);
    RUN_TEST(test_PE_Servo180_detachMotor_1);
    return UNITY_END();
}