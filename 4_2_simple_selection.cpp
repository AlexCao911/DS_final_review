#include <iostream> // Only allowed header

// Function to print the array elements separated by spaces, followed by a newline
void printArray(int arr[], int n) {
    for (int k = 0; k < n; ++k) {
        std::cout << arr[k];
        if (k < n - 1) {
            std::cout << " "; // Print space between numbers
        }
    }
    std::cout << std::endl; // Newline at the end of the line
}

// Simple Selection Sort function
void simpleSelectionSort(int arr[], int n) {
    // Outer loop: Iterate from the first element to the second-to-last
    // (the last element will automatically be in place after n-1 passes)
    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i; // Assume the current element is the minimum

        // Inner loop: Find the index of the minimum element in the unsorted part
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j; // Update minIndex if a smaller element is found
            }
        }

        // If the minimum element is not at the current position 'i', swap them
        if (minIndex != i) {
            // Manual swap (as std::swap is from <algorithm>)
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
        
        // Output the array after each pass (after placing the minimum element)
        printArray(arr, n);
    }
}

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases

    while (t--) {
        int n;
        std::cin >> n; // Read the number of data elements for the current test case

        // Dynamically allocate an array to store the data
        int* arr = new int[n];

        // Read the data elements into the array
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }

        // Perform simple selection sort
        simpleSelectionSort(arr, n);

        // Deallocate the dynamically allocated memory
        delete[] arr;
        arr = NULL; // Good practice to nullify the pointer after deletion

        // Print an empty line to separate output of different test cases,
        // unless it's the very last test case.
        if (t > 0) {
            std::cout << std::endl; 
        }
    }

    return 0;
}