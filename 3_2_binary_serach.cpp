// binary search

#include <iostream>
#include <vector>
#include <algorithm> // For std::sort, though not strictly needed if input is guaranteed sorted

// Function to perform binary search
// Returns the 1-based position if found, 0 if not found
int binarySearch(const std::vector<int>& arr, int target) {
    int n = arr.size();
    if (n == 0) {
        return 0; // Not found in an empty array
    }

    int low = 0;
    int high = n - 1;

    while (low <= high) {
        // Calculate mid-point to prevent potential integer overflow for very large low/high
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid + 1; // Found, return 1-based position
        } else if (arr[mid] < target) {
            low = mid + 1; // Target is in the right half
        } else { // arr[mid] > target
            high = mid - 1; // Target is in the left half
        }
    }

    return 0; // Target not found
}

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of elements in the queue

    std::vector<int> queue_data(n); // Create a vector to store queue data
    for (int i = 0; i < n; ++i) {
        std::cin >> queue_data[i]; // Read queue elements
    }

    // IMPORTANT: Binary search requires sorted data.
    // The problem implies the input is already sorted based on the sample.
    // If not guaranteed sorted, you would uncomment the line below:
    // std::sort(queue_data.begin(), queue_data.end());

    int t;
    std::cin >> t; // Read the number of search queries

    for (int k = 0; k < t; ++k) {
        int target_value;
        std::cin >> target_value; // Read the value to search for

        // Perform the binary search
        int position = binarySearch(queue_data, target_value);

        // Output the result
        if (position != 0) {
            std::cout << position << std::endl;
        } else {
            std::cout << "error" << std::endl;
        }
    }

    return 0;
}