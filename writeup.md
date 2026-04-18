# Google Test And Debugging Writeup

## Things I Thought To Test
1. Whether the swap function is capable of swapping two elements of an array
2. Whether the copy_array function is capable of both allocating memory for a new array and copying the elements of the original array into the new one
3. Whether the min_index_of_array function can correctly return the index of the smallest element no matter how large the array, where the min element is located in the array, and regardless of the number of occurrences of said element.
4. Whether the make_sorted function can properly sort arrays, with duplicate elements, negative numbers, and even arrays that are already sorted
5. Whether the get_sorted function properly generates a copy of the sorted array
6. Whether the parse_args function can properly turn all numbers provided in string form into integer form, and deal with the extreme case of no numbers given

## Bugs

### Bug 1

### Location

sorting.cpp, lines 66 to 68

```c++
int* temp = a;
  a = b;
  b = temp;
```

### How the bug was located

I used a test to swap two elements passed by pointer, the test failed.

### Description

The function actually swaps the addresses of the elements, not the elements themselves.

### Fix 

This bug can be fixed by dereferencing the pointers a and b so that their values get swapped instead of the addresses of the values and by changing the type of temp into int

```c++
int temp = *a;
  *a = *b;
  *b = temp;
```

### Bug 2

### Location

sorting.cpp, line 36

```c++
int* copy = ar;
```

### How the bug was located

I wrote a test to see if the copy_array function can copy the values of an array into a newly allocated array.

### Description

The function does not allocate memory for the new array, and it only gives the new pointer (which is not even allocated properly) the address of the original pointer

### Fix

These two bugs can be fixed by first allocating memory for the new pointer, then using a for loop to copy each element from the original array into the new one.

```c++
int* copy = (int*)malloc(len * sizeof(int));
for (int i = 0; i < len; ++i) {
  copy[i] = ar[i];
}
```

### Bug 3

### Location

sorting.cpp, line 56

```c++
return ar[min_index];
```

### How the bug was located

I wrote a test that checks if the min_index_of_array function can find the min element of an array if it is located at the start of the array.

### Description

The function did not return the index of the min element, instead returning the value of a largest element.

### Fix

First, I made sure the function returns the index, not value of the desired element. Then, I flipped the comparison sign so the function finds the smallest, not largest element of the array.

```c++
for (int i = 1; i < len; ++i) {
  if (ar[i] < ar[min_index]) {
    min_index = i;
  }
}
return min_index;
```