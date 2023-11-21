#include <math.h>

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
    for(size_t i = 0; i < STR_DEFAULT_SIZE * 2; i++) {
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

    str_free(&string);
}

void test_many_ints(void) {
    Str string = {0};
    size_t n = 100000;
    for(size_t i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL(0, str_fmt(&string, "%u", i));
    }
    size_t expected_len = 0;
    for(size_t i = 0; i < n; i++) {
        size_t digits = i > 0 ? (size_t)(log10((double)i)+1) : 1;
        for(size_t j = 0; j < digits; j++) {
            size_t pow10 = (size_t)pow(10, (double)(digits-j-1));
            char digit = (i / pow10) % 10 + '0';
            TEST_ASSERT_EQUAL(digit, str_get_at(&string, expected_len+j));
        }
        expected_len += digits;
    }
    TEST_ASSERT_EQUAL(expected_len, str_length(&string));

    str_free(&string);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_basics);
    RUN_TEST(test_int_123);
    RUN_TEST(test_many_ints);
    printf("\ndone\n");
    return UNITY_END();
}


