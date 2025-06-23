// store and delete

#include <iostream>
#include <vector>
#include <limits> // Required for numeric_limits


class SequentialList {
private:
    std::vector<int> data;
    int actualLength;
    const int maxLength = 1000;

public:
    // Constructor to create the list
    SequentialList() : actualLength(0) {
        data.reserve(maxLength); // Pre-allocate memory
    }

    // Operation: Create/Initialize the list with given data
    void createList(int n, const std::vector<int>& initialData) {
        if (n > maxLength) {
            // This case should ideally be handled before calling createList,
            // or the list should resize if that's a desired feature.
            // For this problem, we'll assume n <= maxLength initially.
            return;
        }
        actualLength = n;
        data.assign(initialData.begin(), initialData.end());
    }

//#############################################################################################
    // Operation: Delete an element at a given position (1-based)
    bool deleteElement(int position) {
        if (position < 1 || position > actualLength) {
            return false; // Deletion failed (position out of bounds)
        }

        // Shift elements to the left
        for (int i = position - 1; i < actualLength - 1; ++i) {
            data[i] = data[i + 1];
        }
        actualLength--;
        // Optionally resize the vector if it's much larger than actualLength
        // data.resize(actualLength); // Not strictly necessary for functionality, but good for memory
        return true; // Deletion successful
    }
//#############################################################################################

    // Display the current state of the list
    void displayList() const {
        std::cout << actualLength << " ";
        for (int i = 0; i < actualLength; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    SequentialList myList;

    int n;
    std::cin >> n;

    std::vector<int> initialData(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> initialData[i];
    }

    myList.createList(n, initialData);
    myList.displayList(); // Output after creation

    int deletePos1;
    std::cin >> deletePos1;
    if (myList.deleteElement(deletePos1)) {
        myList.displayList(); // Output after first successful deletion
    } else {
        std::cout << "error " << std::endl; // Output if first deletion fails
    }

    int deletePos2;
    std::cin >> deletePos2;
    if (myList.deleteElement(deletePos2)) {
        myList.displayList(); // Output after second successful deletion
    } else {
        std::cout << "error " << std::endl; // Output if second deletion fails
    }

    return 0;
}