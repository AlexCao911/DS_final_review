#include <iostream> // Only allowed header

// Function to print the array
void printArray(int arr[], int n) {
    for (int k = 0; k < n; ++k) {
        std::cout << arr[k];
        if (k < n - 1) {
            std::cout << " "; // Print space between numbers
        }
    }
    std::cout << std::endl; // Newline at the end
}

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of data elements

    // Dynamically allocate an array
    // Since we can't use std::vector, we need to manage memory manually.
    // For competitive programming, often a fixed-size array is used if N is small enough,
    // but dynamic allocation is more general.
    int* arr = new int[n]; 

    // Read the data elements
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    // Straight Insertion Sort
    // Start from the second element (index 1) as the first element is considered sorted
    for (int i = 1; i < n; ++i) {
        int key = arr[i]; // The element to be inserted into the sorted part
        int j = i - 1;    // Start comparing from the last element of the sorted part

        // Move elements of arr[0...i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key; // Place the key in its correct position

        // Output the array after each pass (after inserting arr[i])
        printArray(arr, n);
    }

    // Deallocate the dynamically allocated memory
    delete[] arr;
    arr = NULL; // Good practice to set pointer to NULL after deletion

    return 0;
}