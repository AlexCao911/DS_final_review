// sentinel sequential search 

#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits (though not strictly needed if we manage vector size)

// Function to perform sentinel sequential search
// Returns the 1-based position if found, 0 if not found
int sentinelSearch(std::vector<int>& arr, int target) {
    int n = arr.size();

    // Edge case: if the array is empty, target cannot be found
    if (n == 0) {
        return 0; // Not found
    }

    // Store the last element to restore it later if needed (optional for this problem,
    // as we're usually reading into a temporary vector for each search)
    // For a persistent array, this is crucial.
    // For this problem, since we can modify a temporary copy or use push_back,
    // we just need an extra space.

    // 1. Create a temporary vector with an extra space for the sentinel.
    // Or, if modifying the original input vector is allowed and it has capacity:
    // This example will use push_back to safely add the sentinel.
    // Make a copy to avoid modifying the original input data structure across searches,
    // if multiple searches are performed on the same logical "queue".
    std::vector<int> temp_arr = arr; // Make a copy
    temp_arr.push_back(target); // Place the sentinel at the end

    int i = 0;
    // 2. Loop without explicit bounds check
    while (temp_arr[i] != target) {
        i++;
    }

    // 3. Check if the found position is the sentinel's position
    if (i == n) { // If i reached the original end of the array (where sentinel was placed)
        return 0; // Not found in the original array
    } else {
        return i + 1; // Found at (i+1)-th position (1-based)
    }
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

    int t;
    std::cin >> t; // Read the number of search queries

    for (int k = 0; k < t; ++k) {
        int target_value;
        std::cin >> target_value; // Read the value to search for

        // Perform the sentinel search
        int position = sentinelSearch(queue_data, target_value);

        // Output the result
        if (position != 0) {
            std::cout << position << std::endl;
        } else {
            std::cout << "error" << std::endl;
        }
    }

    return 0;
}