#include <iostream>
#include <vector> // Using vector for convenience, but can be done with raw array

// Function to perform bubble sort and count swaps
long long bubbleSortAndCountSwaps(std::vector<int>& arr) {
    long long swap_count = 0;
    int n = arr.size();
    bool swapped; // Flag to optimize: if no swaps in a pass, array is sorted

    // Outer loop for passes
    for (int i = 0; i < n - 1; ++i) {
        swapped = false; // Reset swap flag for current pass
        // Inner loop for comparisons and swaps in the current pass
        // The largest i elements are already in their correct places at the end
        for (int j = 0; j < n - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are in the wrong order
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swap_count++; // Increment swap count
                swapped = true; // Mark that a swap occurred
            }
        }
        // If no two elements were swapped by inner loop, then break
        // Array is sorted
        if (!swapped) {
            break;
        }
    }
    return swap_count;
}

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    // Loop to handle multiple test cases
    while (std::cin >> n) { 
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }

        long long total_swaps = bubbleSortAndCountSwaps(arr);
        std::cout << total_swaps << std::endl;
    }

    return 0;
}