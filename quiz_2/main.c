#include <stdio.h>
#include <stdlib.h> 
//Rotate the array to the right by k steps, where k is non-negative.(i set mine to three it will take the last three in array and will rotate to 1st 2nd 3rd pos

 void rotateArray(int nums[], int size, int k) {
    k = k % size;
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
