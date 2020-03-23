#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

void test_PE_SpiderV2_init_0() {
    PE_SpiderV2_t spider;

    PE_SpiderV2_handlerInit_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);
}

void test_PE_SpiderV2_idle_0() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(NULL, spider.nextState);
}

void test_PE_SpiderV2_idle_1() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
}

void test_PE_SpiderV2_idle_2() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {0, 1, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
}

void test_PE_SpiderV2_idle_3() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 1};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
}

void test_PE_SpiderV2_move1_0() {
    PE_SpiderV2_t spider;

    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove1_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove2, spider.nextState);
}

void test_PE_SpiderV2_move2_0() {
    PE_SpiderV2_t spider;

    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove2_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove3, spider.nextState);
}

void test_PE_SpiderV2_move3_0() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove3_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);
}

void test_PE_SpiderV2_move3_1() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove3_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove4, spider.nextState);
}

void test_PE_SpiderV2_move4_0() {
    PE_SpiderV2_t spider;

    spider.remote.rotateZ = 0;

    PE_SpiderV2_handlerMove4_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove5, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetLinear, spider.calculate);
}

void test_PE_SpiderV2_move4_1() {
    PE_SpiderV2_t spider;

    spider.remote.rotateZ = 1;

    PE_SpiderV2_handlerMove4_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove5, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetRotate, spider.calculate);
}

void test_PE_SpiderV2_move5_0() {
    PE_SpiderV2_t spider;

    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove5_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove6, spider.nextState);
}

void test_PE_SpiderV2_move6_0() {
    PE_SpiderV2_t spider;

    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove6_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove7, spider.nextState);
}

void test_PE_SpiderV2_move7_0() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove7_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);
}

void test_PE_SpiderV2_move7_1() {
    PE_SpiderV2_t spider;

    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove7_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove8, spider.nextState);
}

void test_PE_SpiderV2_move8_0() {
    PE_SpiderV2_t spider;

    spider.remote.rotateZ = 0;

    PE_SpiderV2_handlerMove8_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetLinear, spider.calculate);
}

void test_PE_SpiderV2_move8_1() {
    PE_SpiderV2_t spider;

    spider.remote.rotateZ = 1;

    PE_SpiderV2_handlerMove8_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetRotate, spider.calculate);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_init_0);
    RUN_TEST(test_PE_SpiderV2_idle_0);
    RUN_TEST(test_PE_SpiderV2_idle_1);
    RUN_TEST(test_PE_SpiderV2_idle_2);
    RUN_TEST(test_PE_SpiderV2_idle_3);
    RUN_TEST(test_PE_SpiderV2_move1_0);
    RUN_TEST(test_PE_SpiderV2_move2_0);
    RUN_TEST(test_PE_SpiderV2_move3_0);
    RUN_TEST(test_PE_SpiderV2_move3_1);
    RUN_TEST(test_PE_SpiderV2_move4_0);
    RUN_TEST(test_PE_SpiderV2_move4_1);
    RUN_TEST(test_PE_SpiderV2_move5_0);
    RUN_TEST(test_PE_SpiderV2_move6_0);
    RUN_TEST(test_PE_SpiderV2_move7_0);
    RUN_TEST(test_PE_SpiderV2_move7_1);
    RUN_TEST(test_PE_SpiderV2_move8_0);
    RUN_TEST(test_PE_SpiderV2_move8_1);
    return UNITY_END();
}
