#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "rapidcheck/gtest.h"
#include "sorting.h"
#include "test_helpers.h"

TEST(MinIndexOfArrayTests, SimpleMinIndexAtFrontOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the front of the array
     */
  int array[] = {1, 300, 23, 2};
  EXPECT_EQ(min_index_of_array(array, 4), 0) << "The lowest value of the array, 1, should be at index 0";
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtEndOfArray) {
    /*
     * See if we can find the index of the minimum value when it is at the end of the array
     */
  int array[] = {3, 100000, -1, 0, 2727, -5};
  EXPECT_EQ(min_index_of_array(array, 6), 5) << "The lowest value of the array, -5, should be at index 5";
}

TEST(MinIndexOfArrayTests, SimpleMinIndexAtMiddleOfArray) {
    /*
     * See if we can find the index of the minimum value when it is somewhere
     * in the "middle" of the array.
     */
  int array[] = {100, 2, 4, 0, 2929, 3111, 80};
  EXPECT_EQ(min_index_of_array(array, 7), 3) << "The lowest value of the array, 0, should be at index 3";
}

TEST(MinIndexOfArrayTests, SimpleDuplicateMinimums) {
    /*
     * See if we return the index of the first minimum in the array
     * When there are multiple values that are the minimum.
     */
  int array[] = {-2, 3, -2, -2, 199, -2};
  EXPECT_EQ(min_index_of_array(array, 6), 0) << "The lowest value of the array, -2, should be at index 0";
}

TEST(MinIndexOfArrayTests, SimpleArrayDoesNotChange) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
  int array[] = {0, 2, 100};
  int expected_array[] = {0, 2, 100};
  min_index_of_array(array, 3);
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(array[i], expected_array[i]) << "array was modified at index " << i;
  }
}


RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyFindMinIndex,
              ()) {
    /* Check that the value at the location of the minimum index
     * is not larger than any of the other values in the array
     */
  std::vector<int> values = *rc::gen::arbitrary<std::vector<int>>();
  if (values.empty()) {
    return;
  }
  int len = values.size();
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  int min_index = min_index_of_array(array, len);
  for (int i = 0; i < len; i++) {
    RC_ASSERT(array[min_index] <= array[i]);
  }
  free(array);
}

RC_GTEST_PROP(MinIndexOfArrayTests,
              PropertyArrayDoesNotChange,
              ()) {
    /*
     * Check that finding the minimum of the array did not change the contents of the array.
     */
  std::vector<int> values = *rc::gen::arbitrary<std::vector<int>>();
  int len = values.size();
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  std::vector<int> original = values;
  min_index_of_array(array, len);
  RC_ASSERT(elements_in_vector_and_array_are_same(original, array));
  free(array);
}
