#include <cstdlib>
#include <vector>
#include <algorithm>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "sorting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

TEST(CopyArrayTests, SimpleValuesAreSame) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {0, 1, 2};
  int* copied_array = copy_array(array, 3);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(array[i], copied_array[i]) << "The element of the copied array at index" << i << "is different from the element from the original array";
  }
  free(copied_array);
}

TEST(CopyArrayTests, SimpleOriginalDoesNotChange) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {0, 1, 2};
  int* copied_array = copy_array(array, 3);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(array[i], i) << "The element of the original array at index" << i << "has changed. It should be" << i << "instead.";
  }
  free(copied_array);
}

TEST(CopyArrayTests, SimpleCopyWasMade) {
    /*
     * Check that a copy was actually made
     * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int array[] = {0, 1, 2};
  int* copied_array = copy_array(array, 3);
  EXPECT_NE(copied_array, nullptr) << "The copied array failed to generate";
  EXPECT_NE(array, copied_array) << "The copied array should point at a different address than the original array";
  free(copied_array);
}


RC_GTEST_PROP(CopyArrayTests,
              PropertyValuesAreSame,
              (const std::vector<int>& values)
) {
    /*
     * Check that the values in the copy are the same as the values in the original array.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int len = values.size();
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  int* copied_array = copy_array(array, len);
  RC_ASSERT(elements_in_vector_and_array_are_same(values, copied_array));
  free(array);
  free(copied_array);
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyOriginalDoesNotChange,
              (const std::vector<int>&values)
) {
    /*
     * Check that the  values in the original array did not change.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
  int len = values.size();
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  std::vector<int> original = values;
  int* copied_array = copy_array(array, len);
  RC_ASSERT(elements_in_vector_and_array_are_same(original, array));
  free(array);
  free(copied_array);
}

RC_GTEST_PROP(CopyArrayTests,
              PropertyCopyWasMade,
              (const std::vector<int>&values)
) {
    /*
  * Check that a copy was actually made
  * (ar and copy point to different locations in memory and no parts of the two arrays overlap)
  * Don't forget to free any memory that was dynamically allocated as part of your test.
  */
  int len = values.size();
  int* array = (int*) malloc(len * sizeof(int));
  copy_vector_to_array(values, array);
  int* copied_array = copy_array(array, len);
  RC_ASSERT(copied_array != array);
  for (int i = 0; i < len; ++i) {
    RC_ASSERT((&copied_array[i] != &array[i]));
  }
  free(array);
  free(copied_array);
}