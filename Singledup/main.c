#include <stdio.h>

int singleNumber(int nums[], int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result ^= nums[i];
    }
    return result;
}

int main() {
    int nums[] = {4, 1, 2, 1, 2}; //All have duplicates except for 4
    int size = sizeof(nums) / sizeof(nums[0]);

    int single = singleNumber(nums, size);
    printf("The single number is: %d\n", single);// When run expected output should be 4 in this array

    return 0;
}
