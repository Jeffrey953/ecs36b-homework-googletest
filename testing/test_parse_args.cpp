#include <cstdlib>
#include <string>
#include "gtest/gtest.h"
#include "formatting.h"
#include "test_helpers.h"
#include "rapidcheck/gtest.h"

auto word_generator() {
    /* Creates a generator for a string made up of
     * characters from [a - z]
     */
    return rc::gen::container<std::string>(
            rc::gen::inRange<char>('a', 'z' + 1)
        );
}

auto vector_of_ints_to_vector_of_strings(const std::vector<int>& numbers) {
    /* Create a vector of strings from a vector of ints
     */
    std::vector<std::string> result;
    for (int n : numbers) {
        result.push_back(std::to_string(n));
    }
    return result;
}


TEST(ParseArgsTests, SimpleCheckArgumentsParsedSuccessfully) {
    /*
     * Check that you parse the command line arguments correctly.
     * (ar_out and len_out are set to the right values).
     * Don't forget to free any memory that was dynamically allocated as part of your test.'
     */
  const char* argv[] = {"program", "123", "1"};
  int len_out;
  int* ar_out = NULL;
  parse_args(3, const_cast<char**>(argv), &ar_out, &len_out);
  EXPECT_EQ(len_out, 2);
  ASSERT_NE(ar_out, nullptr);
  EXPECT_EQ(ar_out[0], 123);
  EXPECT_EQ(ar_out[1], 1);
  free(ar_out);
}

TEST(ParseArgsTests, SimpleCheckParseNoArgs) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
  const char* argv[] = {"program"};
  int len_out;
  int* ar_out = NULL;
  parse_args(1, const_cast<char**>(argv), &ar_out, &len_out);
  EXPECT_EQ(len_out, 0);
  ASSERT_EQ(ar_out, nullptr);
}


RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckArgumentsParsedSuccessfully,
              (const std::vector<int>& numbers)
) {
    /* Check that we can correctly parse the command line
     * arguments when we receive 1 or more arguments.
     * Don't forget to free any memory that was dynamically allocated as part of this test
     */
    if (numbers.empty()) {
        return;
    }
    std::vector<std::string> str_numbers = vector_of_ints_to_vector_of_strings(numbers);
    std::vector<char*> argv;
    argv.push_back((char*)"program");
    for (auto& s : str_numbers) {
        argv.push_back(const_cast<char*>(s.c_str()));
    }
    int len;
    int* array = nullptr;
    parse_args(argv.size(), argv.data(), &array, &len);
    RC_ASSERT(len == (int)numbers.size());
    for (int i = 0; i < len; ++i) {
        RC_ASSERT(array[i] == numbers[i]);
    }
    free(array);
}

RC_GTEST_PROP(ParseArgsTests,
              PropertyCheckParseNoArgs,
              ()
) {
    /*
     * Check that you parse you can successfully parse "no" command line arguments.
     */
    char* argv[] = {(char*)"program"};
    int len;
    int* array = nullptr;
    parse_args(1, argv, &array, &len);
    RC_ASSERT(len == 0);
    RC_ASSERT(array == nullptr);
}
