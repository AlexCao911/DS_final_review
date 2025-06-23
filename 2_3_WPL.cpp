#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cctype> // For std::isupper

//####################################################################################################
// Define the structure for a binary tree node
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Global index to keep track of the current position in the pre-order string
int preIndex;

// Function to build the binary tree from pre-order traversal string
TreeNode* buildTree(const std::string& preOrder) {
    // If the current character is '0' or we've exhausted the string, return nullptr
    if (preIndex >= preOrder.length() || preOrder[preIndex] == '0') {
        preIndex++; // Move past the '0'
        return nullptr;
    }

    // Create a new node with the current character
    TreeNode* newNode = new TreeNode(preOrder[preIndex]);
    preIndex++; // Move to the next character for children

    // Recursively build left and right subtrees
    newNode->left = buildTree(preOrder);
    newNode->right = buildTree(preOrder);

    return newNode;
}
//####################################################################################################

// Function to calculate the Weighted Path Length (WPL)
// Only actual leaf nodes (no children) that are uppercase letters contribute
long long calculateWPL(TreeNode* root, int depth, const std::map<char, int>& leafWeights) {
    if (root == nullptr) {
        return 0;
    }

    // Check if it's an actual leaf node in the tree structure AND its data is an uppercase letter
    if (root->left == nullptr && root->right == nullptr && std::isupper(root->data)) {
        // This is a contributing leaf node
        // Use .at() for safe access, it throws if key not found, but problem implies it will exist.
        return (long long)leafWeights.at(root->data) * depth;
    }

    // If it's an internal node or a non-uppercase leaf, sum WPL from children
    return calculateWPL(root->left, depth + 1, leafWeights) +
           calculateWPL(root->right, depth + 1, leafWeights);
}

// Function to free memory allocated for the tree
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Optimize C++ standard streams for faster I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases

    while (t--) {
        std::string preOrderString;
        std::cin >> preOrderString; // Read the pre-order string

        preIndex = 0; // Reset the global index for each new tree
        TreeNode* root = buildTree(preOrderString); // Build the tree

        int n_leaves_weights;
        std::cin >> n_leaves_weights; // Read number of leaf weights

        std::map<char, int> leafWeightsMap;
        for (int i = 0; i < n_leaves_weights; ++i) {
            // The problem states "权值的顺序和前面输入的大写字母顺序对应"
            // This means we need to find the uppercase letters from the preOrderString
            // and assign weights in that order.
            // A simpler interpretation is that the input gives pairs of (char, weight) if it were a map,
            // but it gives `n` weights that correspond to the uppercase letters *in the order they appear
            // in the pre-order string*.
            // To handle this, we need to iterate through the preOrderString once to find
            // the uppercase letters and then assign the input weights.
            // Let's assume the problem means the order of weights in the input directly maps
            // to the order of *uppercase letters* encountered in the pre-order string.
            // We need a separate pass or modification to `buildTree` to collect uppercase leaf nodes.
            // A simpler way: we'll just read the weights and assume the problem guarantees
            // they are in the correct order based on the uppercase characters encountered when doing WPL.
            // However, the common practice for such problems is that the input 'n' is the number of distinct leaf characters that will have weights.
            // And then the problem implies you should find all uppercase letters in the tree, and then
            // match them to the input weights by some logic.
            // "权值的顺序和前面输入的大写字母顺序对应" implies that if preOrder is "xA00tB00zC00D00",
            // and weights are "7 6 2 3", then A gets 7, B gets 6, C gets 2, D gets 3.
            // This means we need to find the uppercase letters in the pre-order traversal sequence
            // and assign weights to them.

            // The simplest way to achieve this is to scan the preOrderString for uppercase letters
            // and then fill the map with the weights as they are read from input.
            // This requires storing the uppercase characters found in pre-order first.
        }
        
        // Re-read preOrderString to find uppercase characters in order to map weights
        // This is a bit clunky, but ensures order.
        std::vector<char> orderedUppercaseLeaves;
        for (char c : preOrderString) {
            if (std::isupper(c)) {
                orderedUppercaseLeaves.push_back(c);
            }
        }

        // Now, populate the map using the ordered leaves and input weights
        for (int i = 0; i < n_leaves_weights; ++i) {
            int weight;
            std::cin >> weight;
            // Assuming n_leaves_weights matches the count of uppercase letters and order is preserved
            if (i < orderedUppercaseLeaves.size()) {
                 leafWeightsMap[orderedUppercaseLeaves[i]] = weight;
            }
        }


        // Calculate and print the WPL
        long long totalWPL = calculateWPL(root, 0, leafWeightsMap); // Depth of root is 0
        std::cout << totalWPL << std::endl;

        // Free allocated memory
        deleteTree(root);
    }

    return 0;
}