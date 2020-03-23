#include <PE_SpiderV2.h>
#include <unity.h>

void test_PE_SpiderV2_calculateTargetLinearX() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_Moving_t) {0, 1, 0, 0, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {20, 20, 20};

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, 10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, spider.legTargets[0].x);

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, spider.legTargets[0].x);
}

void test_PE_SpiderV2_calculateTargetLinearY() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_Moving_t) {0, 0, 1, 0, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {20, 20, 20};

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, 10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(30, spider.legTargets[0].y);

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, -10, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(10, spider.legTargets[0].y);
}

void test_PE_SpiderV2_calculateTargetLinearZ() {
    PE_SpiderV2_t spider;
    spider.moving        = (PE_SpiderV2_Moving_t) {10, 0, 0, 0, 0};
    spider.legMounts[0]  = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    spider.legSources[0] = (PE_SpiderV2_Point3D_t) {20, 20, -20};

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, 0, PE_SPIDER_V2_LEG_MODE_FLOATING);

    TEST_ASSERT_EQUAL(-20, spider.legTargets[0].z);

    spider.legTargets[0] = (PE_SpiderV2_Point3D_t) {0, 0, 0};
    PE_SpiderV2_calculateTargetLinear(&spider, 0, 0, PE_SPIDER_V2_LEG_MODE_GROUNDED);

    TEST_ASSERT_EQUAL(-30, spider.legTargets[0].z);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearX);
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearY);
    RUN_TEST(test_PE_SpiderV2_calculateTargetLinearZ);
    return UNITY_END();
}
