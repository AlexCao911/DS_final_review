// hash linear search

#include <iostream>
#include <vector>
#include <string>
#include <map> // Not strictly needed, but useful for understanding logic

const int NULL_VALUE = -99999; // A distinct value to represent an empty slot

// Hash function
int hashFunction(int key) {
    return key % 11;
}

// Function to insert a key into the hash table
// Returns the number of comparisons
int insertKey(std::vector<int>& hashTable, int key, int m) {
    int comparisons = 0;
    int initial_idx = hashFunction(key);
    int idx = initial_idx;

    do {
        comparisons++; // Each probe is a comparison
        if (hashTable[idx] == NULL_VALUE) {
            hashTable[idx] = key;
            return comparisons;
        }
        idx = (idx + 1) % m;
    } while (idx != initial_idx); // Loop until we've tried all slots or found an empty one

    // If we reach here, it means the table is full and key couldn't be inserted
    // This scenario should ideally be handled for a robust hash table,
    // but based on problem constraints, inputs might guarantee space.
    return comparisons; // Return comparisons even if insert fails (full table)
}

// Function to search for a key in the hash table
// Returns a pair: {success (1/0), comparisons, position (1-based, or 0 if not found)}
struct SearchResult {
    int success;      // 0 for fail, 1 for success
    int comparisons;
    int position;     // 1-based index if successful, 0 if not found
};

SearchResult searchKey(const std::vector<int>& hashTable, int key, int m) {
    SearchResult result = {0, 0, 0};
    int initial_idx = hashFunction(key);
    int idx = initial_idx;

    do {
        result.comparisons++; // Each probe is a comparison
        if (hashTable[idx] == NULL_VALUE) {
            // Found an empty slot before finding the key, so key is not in table
            return result; // Search unsuccessful
        }
        if (hashTable[idx] == key) {
            // Key found
            result.success = 1;
            result.position = idx + 1; // Convert to 1-based
            return result; // Search successful
        }
        idx = (idx + 1) % m;
    } while (idx != initial_idx); // Loop until we've tried all slots or found the key/empty slot

    // If loop completes, it means we've probed all 'm' slots and didn't find the key
    // (This implies the table is full and key is not present)
    return result; // Search unsuccessful
}


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Number of test cases

    while (t--) {
        int m, n;
        std::cin >> m >> n; // Hash table length, number of keywords

        std::vector<int> hashTable(m, NULL_VALUE); // Initialize hash table with NULL_VALUE

        // Insert n keywords
        for (int i = 0; i < n; ++i) {
            int key;
            std::cin >> key;
            insertKey(hashTable, key, m); // We don't need to capture insert comparisons for output here
        }

        // Output constructed hash table
        for (int i = 0; i < m; ++i) {
            if (hashTable[i] == NULL_VALUE) {
                std::cout << "NULL";
            } else {
                std::cout << hashTable[i];
            }
            if (i < m - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;

        int k;
        std::cin >> k; // Number of keys to search

        // Search for k keywords
        for (int i = 0; i < k; ++i) {
            int search_key;
            std::cin >> search_key;
            SearchResult res = searchKey(hashTable, search_key, m);
            std::cout << res.success << " " << res.comparisons;
            if (res.success == 1) {
                std::cout << " " << res.position;
            }
            std::cout << std::endl;
        }
    }

    return 0;
}