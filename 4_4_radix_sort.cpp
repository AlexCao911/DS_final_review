#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>

/**
 * @brief Prints the elements of a vector, separated by spaces, followed by a newline.
 *
 * @param arr The vector of integers to print.
 */
void print_vector(const std::vector<int>& arr) {
    if (arr.empty()) {
        std::cout << "\n";
        return;
    }
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : " ");
    }
    std::cout << "\n";
}

/**
 * @brief Performs Radix Sort on a vector of integers and prints the state at each pass.
 *
 * This function implements the LSD (Least Significant Digit) Radix Sort.
 * It handles negative numbers by shifting all values to be non-negative during the sort.
 * The state of the buckets and the collected array are printed after each pass as per the problem requirements.
 *
 * @param arr The vector of integers to be sorted.
 * @param n The number of elements in the vector.
 */
void radix_sort(std::vector<int>& arr, int n) {
    // Step 1: Handle negative numbers.
    // Find the minimum value in the array.
    int min_val = *std::min_element(arr.begin(), arr.end());
    int offset = 0;

    // If there's a negative number, calculate the offset needed to make all numbers non-negative.
    if (min_val < 0) {
        offset = -min_val;
        // Apply the offset to all elements.
        for (int& val : arr) {
            val += offset;
        }
    }

    // Step 2: Find the maximum element to determine the number of passes.
    int max_val = *std::max_element(arr.begin(), arr.end());
    // The number of passes is equal to the number of digits in the largest number.
    int num_passes = (max_val == 0) ? 1 : static_cast<int>(floor(log10(max_val))) + 1;

    long long exp = 1; // Use long long for exp to avoid overflow with large numbers.

    // Step 3: Iterate for each digit position (pass).
    for (int i = 0; i < num_passes; ++i) {
        // Create 10 buckets (for digits 0-9).
        std::vector<std::vector<int>> buckets(10);

        // a) Distribution Pass: Place numbers into buckets based on the current digit.
        for (int val : arr) {
            int digit = (val / exp) % 10;
            buckets[digit].push_back(val);
        }

        // Print the state of the buckets after distribution.
        for (int j = 0; j < 10; ++j) {
            std::cout << j << ":";
            if (buckets[j].empty()) {
                std::cout << "NULL\n";
            } else {
                std::cout << "->";
                for (int val : buckets[j]) {
                    std::cout << val << "->";
                }
                std::cout << "^\n";
            }
        }

        // b) Collection Pass: Re-collect numbers from buckets back into the array.
        int index = 0;
        for (int j = 0; j < 10; ++j) {
            for (int val : buckets[j]) {
                arr[index++] = val;
            }
        }

        // Print the state of the array after collection.
        print_vector(arr);

        // Move to the next significant digit.
        exp *= 10;
    }

    // Step 4: If an offset was applied, subtract it to restore the original values.
    if (offset > 0) {
        for (int& val : arr) {
            val -= offset;
        }
        // Print the final, true sorted array.
        print_vector(arr);
    }
}

/**
 * @brief Main function to handle test cases.
 */
int main() {
    // Optimize standard I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    bool is_first_case = true;

    while (t--) {
        // Print a blank line to separate test cases, as per requirements.
        if (!is_first_case) {
            std::cout << "\n";
        }
        is_first_case = false;

        int n;
        std::cin >> n;
        std::vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> arr[i];
        }

        // Perform radix sort only if the array is not empty.
        if (n > 0) {
            radix_sort(arr, n);
        }
    }

    return 0;
}