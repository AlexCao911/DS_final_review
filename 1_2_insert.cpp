// store and insert 

#include <iostream>
#include <vector>

class SequentialList {
private:
    std::vector<int> data;
    int actualLength;
    const int maxLength = 1000;

public:
    // Constructor to create the list
    SequentialList() : actualLength(0) {
        data.reserve(maxLength); // Pre-allocate memory to avoid frequent reallocations
    }

    // Operation: Create/Initialize the list with given data
    void createList(int n, const std::vector<int>& initialData) {
        if (n > maxLength) {
            // In a real-world scenario, you might throw an exception or handle this more robustly.
            // For this problem, we'll assume valid initial 'n'.
            actualLength = 0; // Reset if initial data exceeds max length
            return;
        }
        actualLength = n;
        data.assign(initialData.begin(), initialData.end()); // Copy initial data
    }

//#############################################################################################
    // Operation: Insert an element at a given position (1-based)
    bool insertElement(int position, int value) {
        // Check for invalid position or if the list is full
        if (position < 1 || position > actualLength + 1 || actualLength >= maxLength) {
            return false; // Insertion failed
        }

        // Shift elements to the right to make space for the new element
        // Start from the end and move towards the insertion point
        for (int i = actualLength; i >= position; --i) {
            data[i] = data[i - 1];
        }

        // Insert the new element
        data[position - 1] = value;
        actualLength++; // Increment actual length
        return true;    // Insertion successful
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

    int insertPos1, insertVal1;
    std::cin >> insertPos1 >> insertVal1;
    if (myList.insertElement(insertPos1, insertVal1)) {
        myList.displayList(); // Output after first successful insertion
    } else {
        std::cout << "error " << std::endl; // Output if first insertion fails
    }

    int insertPos2, insertVal2;
    std::cin >> insertPos2 >> insertVal2;
    if (myList.insertElement(insertPos2, insertVal2)) {
        myList.displayList(); // Output after second successful insertion
    } else {
        std::cout << "error " << std::endl; // Output if second insertion fails
    }

    return 0;
}
 