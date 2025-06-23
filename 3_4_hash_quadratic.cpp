#include <iostream>
#include <vector>
#include <string> // Required for outputting "NULL"
#include <cmath>  // Not strictly needed as we can calculate square manually, but for general math ops.

// Define a special value to represent an empty slot in the hash table
// Keys are positive integers, so -1 is a safe choice for NULL_VALUE.
const int NULL_VALUE = -1;

// Hash function H(key) = key % 11
int hashFunction(int key) {
    return key % 11;
}

// Function to calculate the quadratic probing offset for a given probe attempt 'k'
// k: probe attempt number (0 for initial hash, 1 for first collision, 2 for second, etc.)
long long getQuadraticProbeOffset(int k) {
    if (k == 0) {
        return 0; // Initial hash, no offset
    }

    // For k > 0, the 'square_root' value for i^2 terms is (k+1)/2 (integer division)
    long long sq_val = (long long)(k + 1) / 2;
    long long offset = sq_val * sq_val;

    // Alternate sign: positive for odd k, negative for even k
    if (k % 2 == 0) { // k is even (2, 4, 6, ...)
        offset = -offset;
    }
    return offset;
}

// Function to insert a key into the hash table using quadratic probing
// Returns the number of comparisons made during insertion
int insertKey(std::vector<int>& hashTable, int key, int m) {
    int comparisons = 0;
    int initial_hash_idx = hashFunction(key);

    // Probe up to 'm' times. If table is full, it might loop indefinitely without this.
    // In theory, for m that is a prime number and load factor < 0.5, a slot is guaranteed.
    for (int k = 0; k < m; ++k) {
        long long offset = getQuadraticProbeOffset(k);
        // Calculate the current index, handling potential negative results from offset
        int current_idx = (initial_hash_idx + offset % m + m) % m;
        
        comparisons++; // Each probe attempt counts as a comparison

        if (hashTable[current_idx] == NULL_VALUE) {
            hashTable[current_idx] = key; // Found an empty slot, insert key
            return comparisons; // Return total comparisons for this insertion
        }
        // If slot is occupied, continue to next probe attempt
    }
    // If the loop completes, it means no empty slot was found for insertion
    // (e.g., table is full, or quadratic probing sequence didn't cover an available slot for non-prime m)
    return comparisons; // Return comparisons even if insertion failed (table full)
}

// Struct to hold the results of a search operation
struct SearchResult {
    int success;      // 0 for unsuccessful, 1 for successful
    int comparisons;  // Total comparisons made during the search
    int position;     // 1-based index if successful, 0 if unsuccessful
};

// Function to search for a key in the hash table using quadratic probing
// Returns a SearchResult struct containing outcome, comparisons, and position
SearchResult searchKey(const std::vector<int>& hashTable, int key, int m) {
    SearchResult result = {0, 0, 0}; // Initialize result as unsuccessful
    int initial_hash_idx = hashFunction(key);

    // Probe up to 'm' times to find the key or determine it's not present
    for (int k = 0; k < m; ++k) {
        long long offset = getQuadraticProbeOffset(k);
        int current_idx = (initial_hash_idx + offset % m + m) % m;
        
        result.comparisons++; // Each probe attempt counts as a comparison

        if (hashTable[current_idx] == NULL_VALUE) {
            // Found an empty slot, means the key is not in the table
            // because if it were, it would have been placed here or earlier.
            return result; // Search unsuccessful
        }
        if (hashTable[current_idx] == key) {
            // Key found!
            result.success = 1;
            result.position = current_idx + 1; // Convert to 1-based index
            return result; // Search successful
        }
        // If hashTable[current_idx] is not NULL_VALUE and not the key, continue probing
    }

    // If the loop completes, it means we have probed all 'm' possible slots
    // and did not find the key (implies table is full and key is not present,
    // or quadratic probing didn't reach the key's location).
    return result; // Search unsuccessful
}

int main() {
    // Optimize C++ standard streams for faster input/output
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t_test_cases;
    std::cin >> t_test_cases; // Read the number of test cases

    while (t_test_cases--) {
        int m_table_length, n_keywords;
        std::cin >> m_table_length >> n_keywords; // Read hash table length and number of keywords

        // Initialize hash table with NULL_VALUE for all slots
        std::vector<int> hashTable(m_table_length, NULL_VALUE);

        // Insert 'n_keywords' into the hash table
        for (int i = 0; i < n_keywords; ++i) {
            int key;
            std::cin >> key;
            insertKey(hashTable, key, m_table_length); // Insert key, comparisons not needed for this output
        }

        // Output the constructed hash table content
        for (int i = 0; i < m_table_length; ++i) {
            if (hashTable[i] == NULL_VALUE) {
                std::cout << "NULL";
            } else {
                std::cout << hashTable[i];
            }
            if (i < m_table_length - 1) {
                std::cout << " "; // Print space between elements
            }
        }
        std::cout << std::endl; // Newline after table output

        int k_searches;
        std::cin >> k_searches; // Read the number of keys to search

        // Perform 'k_searches' and output their results
        for (int i = 0; i < k_searches; ++i) {
            int search_key;
            std::cin >> search_key;
            SearchResult res = searchKey(hashTable, search_key, m_table_length);
            
            std::cout << res.success << " " << res.comparisons;
            if (res.success == 1) {
                std::cout << " " << res.position; // Only print position if search was successful
            }
            std::cout << std::endl; // Newline after each search result
        }
    }

    return 0;
}