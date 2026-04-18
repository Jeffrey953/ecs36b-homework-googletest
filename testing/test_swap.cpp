#include <cstdlib>
#include <vector>
#include <algorithm>
#include "test_helpers.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"


TEST(SwapTests, SimpleSwapTwoValues) {
    /*
     * Swap two values and see if the swap was successful.
     */
  int a = 1;
  int b = 2;
  swap(&a, &b);
  EXPECT_EQ(a, 2) << "The value of a should be swapped to 2";
  EXPECT_EQ(b, 1) << "The value of b should be swapped to 1";
}

TEST(SwapTests, SimpleSwapValuesInArray) {
    /*
     * Swap a few values in an array.
     * Check that the ones that swapped did swap and the ones that didn't swap
     * are still at the same locations
     */
  int* array = (int*)malloc(4 * sizeof(int));
  for (int i = 0; i < 4; i++) {
    array[i] = i;
  }
  swap(&array[0], &array[1]);
  swap(&array[1], &array[3]);
  EXPECT_EQ(array[0], 1) << "The value of array[0] should be swapped to 1";
  EXPECT_EQ(array[1], 3) << "The value of array[1] should be swapped to 3";
  EXPECT_EQ(array[2], 2) << "The value of array[2] should remain 2";
  EXPECT_EQ(array[3], 0) << "The value of array[3] should be swapped to 0";
  free(array);
}

RC_GTEST_PROP(SwapTests,
              PropertySwapTwoValues,
              (int a_start, int b_start)
) {
    /*
     * Swap two values and see if the swap was successful.
     */
  int a = a_start;
  int b = b_start;
  swap(&a, &b);
  RC_ASSERT(a == b_start);
  RC_ASSERT(b == a_start);
}


RC_GTEST_PROP(SwapTests,
              PropertySwapValuesInArray,
              (const std::vector<int>& values)
) {
    /*
     * Swap two values in an array. See that they swapped and the others did not
     */
  if (values.size() < 2) {
    return;
  }
  int len = values.size();
  int* array = (int*)malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  int i = *rc::gen::inRange(0, len);
  int j = *rc::gen::inRange(0, len);
  int value_i = array[i];
  int value_j = array[j];
  swap(&array[i], &array[j]);
  RC_ASSERT(array[i] == value_j);
  RC_ASSERT(array[j] == value_i);
  for (int k = 0; k < len; ++k) {
    if (k != i && k != j) {
      RC_ASSERT(array[k] == values[k]);
    }
  }
}
