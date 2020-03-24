#include <PE_SpiderV2.h>
#include <unity.h>

uint8_t executedOnEntering = 0;
uint8_t executedOnDispatch = 0;

void executorOnEntering () {
    executedOnEntering += 1;
}

void executorOnDispatch () {
    executedOnDispatch += 1;
}

uint8_t onDispatch = 0;

void PE_SpiderV2_onDispatch(PE_SpiderV2_t *spider) {
    (void) spider;

    onDispatch++;
}

void test_PE_SpiderV2_dispatch_0() {
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = NULL;
    spider.startMs   = 0;
    spider.delayMs   = 20;

    onDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 10);

    TEST_ASSERT_EQUAL(0, onDispatch);
}

void test_PE_SpiderV2_dispatch_1() {
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = NULL;
    spider.startMs   = 0;
    spider.delayMs   = 20;

    onDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 30);

    TEST_ASSERT_EQUAL(1, onDispatch);
}

void test_PE_SpiderV2_dispatch_2() {
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = NULL;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(NULL, spider.currState);

    TEST_ASSERT_EQUAL(0, executedOnEntering);
    TEST_ASSERT_EQUAL(0, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_3() {
    PE_SpiderV2_State_t state = {NULL, NULL};
    PE_SpiderV2_t spider;

    spider.currState = &state;
    spider.nextState = &state;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(&state, spider.currState);

    TEST_ASSERT_EQUAL(0, executedOnEntering);
    TEST_ASSERT_EQUAL(0, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_4() {
    PE_SpiderV2_State_t state = {executorOnEntering, executorOnDispatch};
    PE_SpiderV2_t spider;

    spider.currState = &state;
    spider.nextState = &state;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(&state, spider.currState);

    TEST_ASSERT_EQUAL(0, executedOnEntering);
    TEST_ASSERT_EQUAL(2, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_5() {
    PE_SpiderV2_State_t state = {NULL, NULL};
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = &state;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(&state, spider.currState);

    TEST_ASSERT_EQUAL(0, executedOnEntering);
    TEST_ASSERT_EQUAL(0, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_6() {
    PE_SpiderV2_State_t state = {NULL, executorOnDispatch};
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = &state;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(&state, spider.currState);

    TEST_ASSERT_EQUAL(0, executedOnEntering);
    TEST_ASSERT_EQUAL(2, executedOnDispatch);
}

void test_PE_SpiderV2_dispatch_7() {
    PE_SpiderV2_State_t state = {executorOnEntering, executorOnDispatch};
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = &state;
    spider.startMs   = 0;
    spider.delayMs   = 0;

    executedOnEntering = 0;
    executedOnDispatch = 0;

    PE_SpiderV2_dispatchMs(&spider, 0);
    PE_SpiderV2_dispatchMs(&spider, 0);

    TEST_ASSERT_EQUAL(&state, spider.currState);

    TEST_ASSERT_EQUAL(1, executedOnEntering);
    TEST_ASSERT_EQUAL(2, executedOnDispatch);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_dispatch_0);
    RUN_TEST(test_PE_SpiderV2_dispatch_1);
    RUN_TEST(test_PE_SpiderV2_dispatch_2);
    RUN_TEST(test_PE_SpiderV2_dispatch_3);
    RUN_TEST(test_PE_SpiderV2_dispatch_4);
    RUN_TEST(test_PE_SpiderV2_dispatch_5);
    RUN_TEST(test_PE_SpiderV2_dispatch_6);
    RUN_TEST(test_PE_SpiderV2_dispatch_7);
    return UNITY_END();
}
