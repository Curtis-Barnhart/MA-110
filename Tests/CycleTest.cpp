#include <gtest/gtest.h>

#include "../Cycle.h"

/**
 * Tests for CycleNotation::simplify
 */
TEST(CycleSimplifyTest, one_source_array) {
    char s1_array[7] = {1, 2, 0, 1, 2, 3, 0};
    char e1_array[3] = {3, 1, 0};
    char r1_array[3];

    char *end = CycleNotation::simplify(s1_array, s1_array + 7, r1_array);

    ASSERT_EQ(end, r1_array + 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, two_source_array) {
    char s1_array[3] = {1, 2, 0};
    char s2_array[4] = {1, 2, 3, 0};
    char e1_array[3] = {3, 1, 0};
    char r1_array[3];

    char *end = CycleNotation::simplify(
            s1_array,
            s1_array + 3,
            s2_array,
            s2_array + 4,
            r1_array
            );

    ASSERT_EQ(end, r1_array + 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, one_source_empty) {
    char s1_array[1] = {0};
    char e1_array[1] = {0};
    char r1_array[1];

    char *end = CycleNotation::simplify(s1_array, s1_array + 1, r1_array);

    ASSERT_EQ(end, r1_array + 1);
    for (int i = 0; i < 1; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, two_sources_empty) {
    char s1_array[1] = {0};
    char s2_array[1] = {0};
    char e1_array[1] = {0};
    char r1_array[1];

    char *end = CycleNotation::simplify(
            s1_array,
            s1_array + 1,
            s2_array,
            s2_array + 1,
            r1_array
            );

    ASSERT_EQ(end, r1_array + 1);
    for (int i = 0; i < 1; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, one_source_big) {
    char s1_array[13] = {1, 3, 7, 2, 4, 0, 2, 6, 7, 0, 1, 8, 0};
    char e1_array[9] = {3, 2, 4, 8, 1, 0, 7, 6, 0};
    char r1_array[9];

    char *end = CycleNotation::simplify(s1_array, s1_array + 13, r1_array);

    ASSERT_EQ(end, r1_array + 9);
    for (int i = 0; i < 9; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, one_source_inverse) {
    char s1_array[10] = {1, 3, 2, 4, 0, 3, 1, 4, 2, 0};
    char e1_array[1] = {0};
    char r1_array[1];

    char *end = CycleNotation::simplify(s1_array, s1_array + 10, r1_array);

    ASSERT_EQ(end, r1_array + 1);
    for (int i = 0; i < 1; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

TEST(CycleSimplifyTest, one_source_identity) {
    char s1_array[4] = {1, 2, 0, 0};
    char e1_array[3] = {2, 1, 0};
    char r1_array[3];

    char *end = CycleNotation::simplify(s1_array, s1_array + 4, r1_array);

    ASSERT_EQ(end, r1_array + 3);
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(r1_array[i], e1_array[i]);
    }
}

/**
* Tests for CycleNotation::apply
*/
TEST(CycleApplyTest, trivial) {
    char s_array[1] = {0};
    EXPECT_EQ(5, CycleNotation::apply(5, s_array, s_array + 1));
}

TEST(CycleApplyTest, complicated) {
    char s_array[13] = {1, 3, 7, 2, 4, 0, 2, 6, 7, 0, 1, 8, 0};
    char e_array[8] = {3, 4, 2, 8, 5, 7, 6, 1};

    for (char i = 0; i < 8; i++) {
        EXPECT_EQ(e_array[i], CycleNotation::apply(i + 1, s_array, s_array + 13));
    }
}
