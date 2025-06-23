#include <iostream>
#include <string>
#include <vector>

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

// Function for In-order Traversal (Left -> Root -> Right)
void inOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    inOrderTraversal(root->left);
    std::cout << root->data;
    inOrderTraversal(root->right);
}

// Function for Post-order Traversal (Left -> Right -> Root)
void postOrderTraversal(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    std::cout << root->data;
}

// Function to free memory allocated for the tree (optional, but good practice)
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    std::ios_base::sync_with_stdio(false); // Optimize C++ standard streams
    std::cin.tie(NULL); // Untie cin from cout

    int t;
    std::cin >> t; // Read the number of test cases

    std::string preOrderString;
    while (t--) {
        std::cin >> preOrderString; // Read the pre-order string for each tree

        preIndex = 0; // Reset the global index for each new tree
        TreeNode* root = buildTree(preOrderString); // Build the tree

        // Perform and print In-order Traversal
        inOrderTraversal(root);
        std::cout << std::endl;

        // Perform and print Post-order Traversal
        postOrderTraversal(root);
        std::cout << std::endl;

        // Free allocated memory for the tree
        deleteTree(root);
    }

    return 0;
}