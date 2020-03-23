#include <PE_Servo180.h>
#include <stdio.h>
#include <unity.h>

void test_PE_Servo180_attachMotor_0() {
    PE_Servo180_Motor_t motor = {.min = 0, .max = 0};
    PE_Servo180_Timer_t timer = {.motorCount = 0};

    PE_Servo180_Status_t status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);
    TEST_ASSERT_EQUAL(1, timer.motorCount);
    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MIN, motor.min);
    TEST_ASSERT_EQUAL(PE_Servo180_MOTOR_MAX, motor.max);
}

void test_PE_Servo180_attachMotor_1() {
    PE_Servo180_Motor_t motor = {.min = 100, .max = 1000};
    PE_Servo180_Timer_t timer = {.motorCount = 0};

    PE_Servo180_Status_t status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_SUCCESS, status);
    TEST_ASSERT_EQUAL(1, timer.motorCount);
    TEST_ASSERT_EQUAL(100, motor.min);
    TEST_ASSERT_EQUAL(1000, motor.max);
}

void test_PE_Servo180_attachMotor_2() {
    PE_Servo180_Motor_t motor;
    PE_Servo180_Timer_t timer = {.motorCount = 0};

    PE_Servo180_attachMotor(&timer, &motor);

    PE_Servo180_Status_t status = PE_Servo180_attachMotor(&timer, &motor);

    TEST_ASSERT_EQUAL(PE_Servo180_FAILURE, status);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_Servo180_attachMotor_0);
    RUN_TEST(test_PE_Servo180_attachMotor_1);
    RUN_TEST(test_PE_Servo180_attachMotor_2);
    return UNITY_END();
}