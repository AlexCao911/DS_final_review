// store and query 

#include <iostream>
#include <vector> // Using std::vector as the underlying array

class SequentialList {
private:
    std::vector<int> data;       // The array to store elements
    int actualLength;            // Current number of elements
    const int maxLength = 1000;  // Maximum capacity of the list

public:
    // Constructor to initialize the list
    SequentialList() : actualLength(0) {
        data.reserve(maxLength); // Pre-allocate memory for efficiency
    }

    // Operation: Create/Initialize the list with given data
    void createList(int n, const std::vector<int>& initialData) {
        if (n > maxLength) {
            actualLength = 0; // If initial data exceeds max length, create an empty list
            return;
        }
        actualLength = n;
        data.assign(initialData.begin(), initialData.end()); // Copy initial data
    }

//#############################################################################################
    // Operation: Find an element at a given position (1-based)
    // Returns the element if found, or a special value/flag for error.
    // For this problem, we'll return a boolean for success and pass the value by reference.
    bool findElement(int position, int& foundValue) const {
        // Check if the position is valid (1-based, within actual length)
        if (position < 1 || position > actualLength) {
            return false; // Lookup failed (position out of bounds)
        }
        foundValue = data[position - 1]; // Access the element (0-based index)
        return true; // Lookup successful
    }
//#############################################################################################

    // Display the current state of the list -> print the length and elements 
    void displayList() const {
        std::cout << actualLength << " ";
        for (int i = 0; i < actualLength; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    SequentialList myList; // Create an instance of our sequential list

    int n;
    std::cin >> n; // Read the actual length

    std::vector<int> initialData(n); // define the length
    for (int i = 0; i < n; ++i) {
        std::cin >> initialData[i]; // Read the data elements
    }

    myList.createList(n, initialData); // Populate the list
    myList.displayList(); // Output after creation

    int lookupPos1;
    std::cin >> lookupPos1; // Read the first position to look up
    int foundVal1;
    if (myList.findElement(lookupPos1, foundVal1)) {
        std::cout << foundVal1 << std::endl; // Output found value if successful
    } else {
        std::cout << "error" << std::endl; // Output error if lookup fails
    }

    int lookupPos2;
    std::cin >> lookupPos2; // Read the second position to look up
    int foundVal2;
    if (myList.findElement(lookupPos2, foundVal2)) {
        std::cout << foundVal2 << std::endl; // Output found value if successful
    } else {
        std::cout << "error" << std::endl; // Output error if lookup fails
    }

    return 0;
}