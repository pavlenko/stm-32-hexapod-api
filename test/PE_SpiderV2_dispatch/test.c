#include <PE_SpiderV2.h>
#include <unity.h>

PE_SpiderV2_t spider;

uint8_t executedOnEntering = 0;
uint8_t executedOnDispatch = 0;

void executorOnEntering () {
    executedOnEntering += 1;
}

void executorOnDispatch () {
    executedOnDispatch += 1;
}

void test_PE_SpiderV2_dispatch_millis_skip() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 5);

    TEST_ASSERT(0 == spider.millis);
}

void test_PE_SpiderV2_dispatch_millis_update() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT(25 == spider.millis);
}

void test_PE_SpiderV2_dispatch_state_changed() {
    PE_SpiderV2_State_t nextState = {NULL, NULL};

    spider.millis    = 0;
    spider.currState = NULL;
    spider.nextState = &nextState;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT(&nextState == spider.currState);
}

void test_PE_SpiderV2_dispatch_onDispatch1() {
    spider.millis    = 0;
    spider.currState = NULL;
    spider.nextState = NULL;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT_EQUAL(0, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_onDispatch2() {
    PE_SpiderV2_State_t state = {NULL, NULL};

    spider.millis    = 0;
    spider.currState = NULL;
    spider.nextState = &state;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT_EQUAL(0, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_onDispatch3() {
    PE_SpiderV2_State_t state = {NULL, executorOnDispatch};

    spider.millis    = 0;
    spider.currState = NULL;
    spider.nextState = &state;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT_EQUAL(1, executedOnDispatch);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_skip);
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_update);
    RUN_TEST(test_PE_SpiderV2_dispatch_state_changed);
    RUN_TEST(test_PE_SpiderV2_dispatch_onDispatch1);
    RUN_TEST(test_PE_SpiderV2_dispatch_onDispatch2);
    RUN_TEST(test_PE_SpiderV2_dispatch_onDispatch3);
    return UNITY_END();
}
