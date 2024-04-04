/** @file */

#ifndef NODE_H
#define NODE_H
/**
 * @brief Enumeration representing the colors used in the red-black tree.
 *
 * Red : Represents the red color
 * Black : Represents the black color
 * DBlack: Represents the double black color
 */
enum Color
{
    Red,
    Black,
    DBlack
};
/**
 * @brief A structure that represents a node in a binary tree.
 *
 * The Node structure represents a node in a binary tree and holds the following data:
 * data: The float value stored in the node.
 * parent: A pointer to the parent node in the tree.
 * left: A pointer to the left child node in the tree.
 * right: A pointer to the right child node in the tree.
 * color: The color of the node.
 */
struct Node
{
    float data;
    Node* parent;
    Node* left;
    Node* right;
    Color color;
};
/**
 * @brief Adds the elements of `args` vector one by one to the red-black tree rooted at `head`.
 *
 * @param head A reference to the root node of the red-black tree.
 * @param args The vector of elements to be added to the tree.
 */
void add(Node*& head, const std::vector<float>& args);
/**
 * @brief Adds the node `node` to the red-black tree rooted at `root`.
 *
 * @param root A reference to the root node of the red-black tree.
 * @param node The node to be added to the tree.
 *
 * @return The root node of the red-black tree after the insertion of `node`.
 */
Node* addtotree(Node*& root, Node*& node);
/**
 * @brief Checks existence of value in the tree
 *
 * @param head Pointer to the head node of the red black tree
 *
 * @param data Float with data to check
 */
bool checkIfPresent(Node*& head, float data);
/**
 * @brief Fixes the red-black tree rooted at `root` after adding a node.
 *
 * @param root A reference to the root node of the red-black tree.
 * @param node The node that was recently added to the tree.
 */
void addfix(Node*& root, Node*& node);
/**
 * @brief Removes nodes with data in `args` from the red-black tree rooted at `head`.
 *
 * @param head A reference to the root node of the red-black tree.
 * @param args The data values of the nodes to be removed from the tree.
 */
void remove(Node*& head, const std::vector<float>& args);
/**
 * @brief Deletes a node with data equal to `value` from the red-black tree rooted at `root`.
 *
 * @param root The root node of the red-black tree.
 * @param value The data value of the node to be deleted.
 *
 * @return The node that was deleted, or `nullptr` if a node with the specified data value was not found.
 */
Node* removefromtree(Node*& root, float value);
/**
 * @brief Function to remove a node from a red-black tree.
 *
 * @param head Pointer to the head node of the red-black tree.
 * @param node Pointer to the node to be removed from the red-black tree.
 */
void removefix(Node*& head, Node*& node);
/**
 * @brief Perform left rotation on a Red-Black Tree.
 *
 * @param head A reference to the head of the Red-Black Tree.
 * @param root A reference to the root node of the subtree to be rotated.
 */
void rotateleft(Node*& head, Node*& root);
/**
 * @brief Perform right rotation on a Red-Black Tree.
 *
 * @param head A reference to the head of the Red-Black Tree.
 * @param root A reference to the root node of the subtree to be rotated.
 */
void rotateright(Node*& head, Node*& root);
/**
 * @brief Finds the node with the minimum value in a Red-Black Tree
 *
 * @param node The root node of the Red-Black Tree.
 *
 * @return The node with the minimum value in the Red-Black Tree.
 */
Node* minValueNode(Node*& node);
/**
 * @brief Prints the tree rooted at the given node in in-order traversal.
 *
 * @param root The root node of the tree to be printed.
 */
void print(Node*& head);
/**
 * @brief Writes the elements of a red black tree to a file
 *
 * @param head Pointer to the head node of the red black tree
 *
 * @param filename String representing the name of the file to be written to
 */
void printfile(Node*& head, const std::string& filename);
/**
 * @brief Updates file with new elements
 *
 * @param head Pointer to the head node of the red black tree
 *
 * @param filename String representing the name of the file to be written to
 */
void updatefile(Node*& head, const std::string& filename);
/**
 * @brief Graphs the elements as red() or black[]
 *
 * @param head Pointer to the head node of the red black tree
 */
void graph(Node*& head);
/**
 * @brief Graphs the elements of a red black tree to a file
 *
 * @param head Pointer to the head node of the red black tree
 *
 * @param filename String representing the name of the file to be written to
 */
void printgraph(Node*& head, const std::string& filename);
/**
 * @brief Updates file with new graph elements
 *
 * @param head Pointer to the head node of the red black tree
 *
 * @param filename String representing the name of the file to be written to
 */
void updategraph(Node*& head, const std::string& filename);

#endif