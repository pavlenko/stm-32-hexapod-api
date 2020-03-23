#include <PE_SpiderV2.h>
#include <unity.h>

void test_PE_SpiderV2_initialize() {
    PE_SpiderV2_t spider;

    spider.currState = NULL;
    spider.nextState = NULL;

    TEST_ASSERT_EQUAL(NULL, spider.nextState);

    PE_SpiderV2_initialize(&spider);

    TEST_ASSERT_EQUAL(&PE_SpiderV2_stateInit, spider.nextState);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_initialize);
    return UNITY_END();
}
