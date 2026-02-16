#include <stdio.h>

int main() {
    int size;

    // Ask user for array size
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int arr[size];

    // Fill array with user input
    printf("Enter %d integers:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Print array in reverse
    printf("Array in reverse order:\n");
    for (int i = size - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}

