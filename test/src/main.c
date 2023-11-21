#include "unity.h"
#include "unity_internals.h"
#include "str.h"
#include "vec.h"

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}



void test_basics(void) {
    Str string = {0};
    TEST_ASSERT_EQUAL(0, str_length(&string));
    TEST_ASSERT_EQUAL(0, str_reserved(&string));
    TEST_ASSERT_EQUAL(0, str_push_back(&string, 'a'));

    TEST_ASSERT_EQUAL(1, str_length(&string));
    for(size_t i = 0; i < VEC_DEFAULT_SIZE * 2; i++) {
        TEST_ASSERT_EQUAL(0, str_push_back(&string, 'a'));
        TEST_ASSERT_GREATER_THAN(str_length(&string), string.cap);
    }

    str_free(&string);
    TEST_ASSERT_EQUAL(0, str_length(&string));
    TEST_ASSERT_EQUAL(0, str_reserved(&string));
}

void test_int_123(void) {
    Str string = {0};
    int i = 123;
    str_fmt(&string, "%i", i);

    TEST_ASSERT_EQUAL(3, str_length(&string));
    TEST_ASSERT_EQUAL('1', str_get_at(&string, 0));
    TEST_ASSERT_EQUAL('2', str_get_at(&string, 1));
    TEST_ASSERT_EQUAL('3', str_get_at(&string, 2));
    TEST_ASSERT_EQUAL(0, string.s[3]); /* brute-force access, because otherwise out-of-bounds */
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_basics);
    RUN_TEST(test_int_123);
    printf("\ndone\n");
    return UNITY_END();
}


