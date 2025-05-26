#include <stdio.h>

int getMaximum(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

int getMinimum(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min)
            min = arr[i];
    }
    return min;
}

void Max_Min(int numbers[], int n) {
    int p = 0, k = 0;
    int winners[n / 2], losers[n / 2];

    for (int i = 0; i < n; i += 2) {
        if (numbers[i] < numbers[i + 1]) {
            losers[p++] = numbers[i];
            winners[k++] = numbers[i + 1];
        } else {
            losers[p++] = numbers[i + 1];
            winners[k++] = numbers[i];
        }
    }

    printf("Maximum: %d\n", getMaximum(winners, n / 2));
    printf("Minimum: %d\n", getMinimum(losers, n / 2));
}

int main() {
    int numbers[] = {7, 2, 9, 1, 6, 3, 8, 4};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    // Make sure the array has even number of elements
    if (n % 2 != 0) {
        printf("Array must contain even number of elements.\n");
        return 1;
    }

    Max_Min(numbers, n);
    return 0;
}
 
