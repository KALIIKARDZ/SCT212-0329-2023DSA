#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int nums[], int size) {
    if (size == 0) return 0;

    int j = 0;
    for (int i = 1; i < size; i++) {
        if (nums[i] != nums[j]) {
            nums[++j] = nums[i];
        } 
    }
    return j + 1;
}

int main() {
    int nums[] = {1,7, 1, 2, 2, 3, 4, 4, 5};
    int size = sizeof(nums) / sizeof(nums[0]);

    int newLength = removeDuplicates(nums, size);

    printf("New length of array is : %d\n", newLength);
    printf("Modified array: ");
    for (int i = 0; i < newLength; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}
