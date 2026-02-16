#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n = 0;          // Always initialize variables
    int *arr = NULL;    // Initialize pointer before use

    // Ask user for number of elements
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    // Handle zero or negative sizes
    if (n <= 0) {
        printf("Cannot allocate memory for %d elements.\n", n);
        return 1;
    }

    // Allocate memory
    arr = malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Fill the array
    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            free(arr);   // Prevent memory leak
            return 1;
        }
    }

    // Print in reverse order
    printf("Numbers in reverse order:\n");
    for (int i = n - 1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Free memory
    free(arr);
    arr = NULL;   // Good practice (prevents dangling pointer)

    return 0;
}
