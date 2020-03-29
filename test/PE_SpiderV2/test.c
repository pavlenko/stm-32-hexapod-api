#include <PE_SpiderV2.h>
#include <stdio.h>
#include <unity.h>

PE_SpiderV2_t spider = {
    .moving = {.height = 50},
    .legs = {
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, 120, 0},  .src = {-135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, 120, 0},   .src = {135, 190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-170, 0, 0},   .src = {-270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {170, 0, 0},    .src = {270, 0, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {-85, -120, 0}, .src = {-135, -190, 0}},
        {.cLength = 28, .fLength = 69, .tLength = 52, .mnt = {85, -120, 0},  .src = {135, -190, 0}},
    }
};

void PE_SpiderV2_dump() {
    uint8_t index;
    printf("-----\n");
    for (index = 0; index < 6; index++) {
        printf(
            "%d: dst{x: %.3f, y: %.3f, z: %.3f} deg{c: %.3f, f: %.3f, t: %.3f}\n",
            index,
            spider.legs[index].dst.x,
            spider.legs[index].dst.y,
            spider.legs[index].dst.z,
            spider.legs[index].cDegree,
            spider.legs[index].fDegree,
            spider.legs[index].tDegree
        );
    }
    printf("-----\n");
}

void test_PE_SpiderV2_init_0() {
    PE_SpiderV2_handlerInit_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_idle_0() {
    PE_SpiderV2_handlerIdle_onEntering(&spider);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_idle_1() {
    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(NULL, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_idle_2() {
    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_idle_3() {
    spider.remote    = (PE_SpiderV2_Remote_t) {0, 1, 0};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_idle_4() {
    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 1};
    spider.nextState = NULL;

    PE_SpiderV2_handlerIdle_onDispatch(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move1_0() {
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove1_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove2, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move2_0() {
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove2_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove3, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move3_0() {
    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove3_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move3_1() {
    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove3_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove4, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move4_0() {
    spider.remote.rotateZ = 0;

    PE_SpiderV2_handlerMove4_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove5, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetLinear, spider.calculate);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move4_1() {
    spider.remote.rotateZ = 1;

    PE_SpiderV2_handlerMove4_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove5, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetRotate, spider.calculate);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move5_0() {
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove5_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove6, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move6_0() {
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove6_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove7, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move7_0() {
    spider.remote    = (PE_SpiderV2_Remote_t) {0, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove7_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateIdle, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move7_1() {
    spider.remote    = (PE_SpiderV2_Remote_t) {1, 0, 0};
    spider.calculate = PE_SpiderV2_calculateTargetLinear;

    PE_SpiderV2_handlerMove7_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove8, spider.nextState);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move8_0() {
    spider.remote.rotateZ = 0;

    PE_SpiderV2_handlerMove8_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetLinear, spider.calculate);

    PE_SpiderV2_dump();
}

void test_PE_SpiderV2_move8_1() {
    spider.remote.rotateZ = 1;

    PE_SpiderV2_handlerMove8_onEntering(&spider);

    TEST_ASSERT_EQUAL_PTR(&PE_SpiderV2_stateMove1, spider.nextState);
    TEST_ASSERT_EQUAL_PTR(PE_SpiderV2_calculateTargetRotate, spider.calculate);

    PE_SpiderV2_dump();
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_init_0);
    RUN_TEST(test_PE_SpiderV2_idle_0);
    RUN_TEST(test_PE_SpiderV2_idle_1);
    RUN_TEST(test_PE_SpiderV2_idle_2);
    RUN_TEST(test_PE_SpiderV2_idle_3);
    RUN_TEST(test_PE_SpiderV2_idle_4);
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
