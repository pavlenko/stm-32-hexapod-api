#include <PE_SpiderV2.h>
#include <unity.h>

PE_SpiderV2_t spider;

void test_PE_SpiderV2_dispatch_millis_skip() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 5);

    TEST_ASSERT_EQUAL(0, spider.millis);
}

void test_PE_SpiderV2_dispatch_millis_update() {
    spider.millis = 0;

    PE_SpiderV2_dispatch(&spider, 25);

    TEST_ASSERT_EQUAL(25, spider.millis);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_skip);
    RUN_TEST(test_PE_SpiderV2_dispatch_millis_update);
    return UNITY_END();
}
