#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[]= {0, 1, 100, 3400, 12345};
  int same_array[]= {0, 1, 100, 3400, 12345};
  make_sorted(array, 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(array[i], same_array[i]) << "The array's value changed at index " << i;
  }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {1000, 234, 2, -32};
  int sorted_array[] = {-32, 2, 234, 1000};
  make_sorted(array, 4);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(array[i], sorted_array[i]) << "The array's value is wrong at index " << i;
  }
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {6767, -1000, 0, 234, -3};
  int sorted_array[] = {-1000, -3, 0, 234, 6767};
  make_sorted(array, 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(array[i], sorted_array[i]) << "The array's value is wrong at index " << i;
  }
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {0, 123, 0, -123, 123, 0, 0, 1};
  int sorted_array[] = {-123, 0, 0, 0, 0, 1, 123, 123};
  make_sorted(array, 8);
  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(array[i], sorted_array[i]) << "The array's value is wrong at index " << i;
  }
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int len = values.size();
  if (len == 0) {
    return;
  }
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  make_sorted(array, len);
  for (int i = 0; i < len - 1; i++) {
    RC_ASSERT(array[i] <= array[i + 1]);
  }
  free(array);
}
