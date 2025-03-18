#include <stdio.h>
#include <stdbool.h>

bool containsDuplicate(int nums[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (nums[i] == nums[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int nums[] = {1, 2, 3, 3, 4, 5, 6 };// Code will print true for this array , to test fro false just remove the "3"
    int size = sizeof(nums) / sizeof(nums[0]);

    if (containsDuplicate(nums, size)) {
        printf("True - a value in array appears atleast twice.\n");
    } else {
        printf("False - every element is distinct..\n");
    }

    return 0;
}

