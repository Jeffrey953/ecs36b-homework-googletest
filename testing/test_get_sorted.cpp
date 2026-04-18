#include <cstdlib>
#include "gtest/gtest.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(GetSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {1, 2, 3, 4, 5};
    int sorted_array[] = {1, 2, 3, 4, 5};
    int* result = get_sorted(array, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(result[i], sorted_array[i]) << "The sort failed at index " << i;
    }
    free(result);
}

TEST(GetSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {5, 4, 3, 2, 1};
    int sorted_array[] = {1, 2, 3, 4, 5};
    int* result = get_sorted(array, 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(result[i], sorted_array[i]) << "The sort failed at index " << i;
    }
    free(result);
}

TEST(GetSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {2, 1, 3, 0};
    int sorted_array[] = {0, 1, 2, 3};
    int* result = get_sorted(array, 4);
    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(result[i], sorted_array[i]) << "The sort failed at index " << i;
    }
    free(result);
}

TEST(GetSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {0, 1, 0, 2, 0, 1};
    int sorted_array[] = {0, 0, 0, 1, 1, 2};
    int* result = get_sorted(array, 6);
    for (int i = 0; i < 6; i++) {
        EXPECT_EQ(result[i], sorted_array[i]) << "The sort failed at index " << i;
    }
    free(result);
}

TEST(GetSortedTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {1, 3, 0};
    int same_array[] = {1, 3, 0};
    get_sorted(array, 3);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(array[i], same_array[i]) << "The original array changed at index " << i;
    }
}

TEST(GetSortedTests, SimpleCopyWasMade) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[] = {0, 1, 0};
    int* result = get_sorted(array, 3);
    EXPECT_NE(result, array) << " The original array and the sorted one overlap";
    free(result);
}


RC_GTEST_PROP(GetSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Check that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    int len = values.size();
    int* array = (int*) malloc(len * sizeof(int));
    copy_vector_to_array(values, array);
    int* sorted_array = get_sorted(array, len);
    for (int i = 0; i < len - 1; i++) {
        RC_ASSERT(sorted_array[i] <= sorted_array[i + 1]);
    }
    free(array);
    free(sorted_array);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the original array was not modified.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* array = (int*) malloc(len * sizeof(int));
    copy_vector_to_array(values, array);
    std::vector<int> original = values;
    int* sorted_array = get_sorted(array, len);
    RC_ASSERT(elements_in_vector_and_array_are_same(original, array));
    free(array);
    free(sorted_array);
}

RC_GTEST_PROP(GetSortedTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
     * Check that the sorted array is copy of the original array in sorted order.
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int len = values.size();
    int* array = (int*) malloc(len * sizeof(int));
    copy_vector_to_array(values, array);
    int* sorted_array = get_sorted(array, len);
    RC_ASSERT(sorted_array != array);
    for (int i = 0; i < len; i++) {
        RC_ASSERT(&sorted_array[i] != &array[i]);
    }
    free(array);
    free(sorted_array);
}











