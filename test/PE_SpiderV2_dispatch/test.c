#include <PE_SpiderV2.h>
#include <unity.h>

PE_SpiderV2_t spider;

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
    spider.prevState = NULL;
    spider.nextState = &nextState;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT(&nextState == spider.prevState);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_skip);
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_update);
    RUN_TEST(test_PE_SpiderV2_dispatch_state_changed);
    return UNITY_END();
}
