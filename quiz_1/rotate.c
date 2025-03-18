#include <stdio.h>

void rotateArray(int nums[], int size, int k) {
    k = k % size; // Handle cases where k >= size
    for (int i = 0; i < k; i++) {
        int last = nums[size - 1];
        for (int j = size - 1; j > 0; j--) {
            nums[j] = nums[j - 1];
        }
        nums[0] = last;
    }
}

int main() {
    int nums[] = {1, 2, 3, 4, 5, 6, 7};
    int size = sizeof(nums) / sizeof(nums[0]);
    int k = 3;

    rotateArray(nums, size, k);

    printf("Rotated array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");

    return 0;
}

