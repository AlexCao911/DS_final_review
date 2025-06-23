// store and create

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
        data.reserve(maxLength); // Pre-allocate memory to avoid reallocations later
    }

    // Operation: Create/Initialize the list with given data
    void createList(int n, const std::vector<int>& initialData) {
        // Ensure n does not exceed the maximum length
        if (n > maxLength) {
            actualLength = 0; // If initial data is too large, reset to empty
            // In a more robust implementation, you might throw an error or truncate.
            return;
        }
        actualLength = n;
        // Copy the initial data into the internal vector
        data.assign(initialData.begin(), initialData.end());
    }

    // Display the actual length of the list
    void displayActualLength() const {
        std::cout << actualLength << std::endl;
    }

    // Display the data elements of the list
    void displayData() const {
        for (int i = 0; i < actualLength; ++i) {
            std::cout << data[i];
            if (i < actualLength - 1) { // Add space between elements, but not at the end
                std::cout << " ";
            }
        }
        std::cout << std::endl; // Newline at the end
    }
};

int main() {
    SequentialList myList; // Create an instance of our sequential list

    int n;
    std::cin >> n; // Read the actual length

    // Create a temporary vector to hold the input data
    std::vector<int> initialData(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> initialData[i]; // Read the data elements
    }

    // Call the createList operation to populate our sequential list
    myList.createList(n, initialData);

    // Output the actual length
    myList.displayActualLength();

    // Output the data elements
    myList.displayData();

    return 0;
}