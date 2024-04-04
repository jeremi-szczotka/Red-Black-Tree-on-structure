/** @file */

#include <iostream>
#include <fstream>
#include <vector>
#include "node.h"
#include "functions.h"

// adds multiple new nodes with values from a vector to a tree
void add(Node*& head, const std::vector<float>& args)
{
    for (int i = 0; i < args.size(); i++)
    {
        if (!checkIfPresent(head, args[i]))
        {
            Node* node = new Node{ args[i], nullptr, nullptr, nullptr, Red };
            head = addtotree(head, node);
            addfix(head, node);
        }
    }
}

// checks if a given number already exist in the tree
bool checkIfPresent(Node*& head, float data)
{
    if (head == nullptr)
        return false;
    if (head->data == data)
        return true;
    return data < head->data ? checkIfPresent(head->left, data) : checkIfPresent(head->right, data);
}

// adds a new node to a tree by recursively navigating to the appropriate location in the tree based on the value of the new node and updating the parent pointers
Node* addtotree(Node*& root, Node*& node)
{
    if (root == nullptr)
        return node;
    if (node->data < root->data)
    {
        root->left = addtotree(root->left, node);
        root->left->parent = root;
    }
    else if (node->data > root->data)
    {
        root->right = addtotree(root->right, node);
        root->right->parent = root;
    }
    return root;
}

// balances a tree after adding a node by checking and adjusting the coloring to maintain the Red-Black tree properties
void addfix(Node*& root, Node*& node)
{
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (node != root && blackLeaf(node) == Red && blackLeaf(node->parent) == Red)
    {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left)
        {
            Node* uncle = grandparent->right;
            if (blackLeaf(uncle) == Red)
            {
                setColor(uncle, Black);
                setColor(parent, Black);
                setColor(grandparent, Red);
                node = grandparent;
            }
            else
            {
                if (node == parent->right)
                {
                    rotateleft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateright(root, grandparent);
                Color parentcolor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = parentcolor;
                node = parent;
            }
        }
        else
        {
            Node* uncle = grandparent->left;
            if (blackLeaf(uncle) == Red)
            {
                setColor(uncle, Black);
                setColor(parent, Black);
                setColor(grandparent, Red);
                node = grandparent;
            }
            else
            {
                if (node == parent->left)
                {
                    rotateright(root, parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateleft(root, grandparent);
                Color parentcolor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = parentcolor;
                node = parent;
            }
        }
    }

    setColor(root, Black);
}

// removes multiple nodes with values from a vector from a tree
void remove(Node*& head, const std::vector<float>& args)
{
    for (int i = 0; i < args.size(); i++)
    {
        Node* node = removefromtree(head, args[i]);
        removefix(head, node);
    }
}

// finds and deletes a node with a given value from a tree
Node* removefromtree(Node*& root, float value)
{
    if (root == nullptr)
        return root;
    if (value < root->data)
        return removefromtree(root->left, value);

    if (value > root->data)
        return removefromtree(root->right, value);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node* temp = minValueNode(root->right);
    root->data = temp->data;
    return removefromtree(root->right, temp->data);
}

// fixes the tree after a node removal by checking the color of the removed node, its sibling and parent, then rotating and coloring the tree to maintain the red-black tree properties
void removefix(Node*& head, Node*& node)
{
    if (node == nullptr)
        return;

    if (node == head)
    {
        head = nullptr;
        return;
    }

    if (blackLeaf(node) == Red || blackLeaf(node->left) == Red || blackLeaf(node->right) == Red)
    {
        Node* child = node->left != nullptr ? node->left : node->right;

        if (node == node->parent->left)
        {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, Black);
            delete (node);
        }
        else
        {
             node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, Black);
            delete (node);
        }
    }
    else
    {
        Node* sibling = nullptr;
        Node* parent = nullptr;
        Node* ptr = node;
        setColor(ptr, DBlack);
        while (ptr != head && blackLeaf(ptr) == DBlack)
        {
            parent = ptr->parent;
            if (ptr == parent->left)
            {
                sibling = parent->right;
                if (blackLeaf(sibling) == Red)
                {
                    setColor(sibling, Black);
                    setColor(parent, Red);
                    rotateleft(head, parent);
                }
                else
                {
                    if (blackLeaf(sibling->left) == Black && blackLeaf(sibling->right) == Black)
                    {
                        setColor(sibling, Red);
                        if (blackLeaf(parent) == Red)
                            setColor(parent, Black);
                        else
                            setColor(parent, DBlack);
                        ptr = parent;
                    }
                    else
                    {
                        if (blackLeaf(sibling->right) == Black)
                        {
                            setColor(sibling->left, Black);
                            setColor(sibling, Red);
                            rotateright(head, sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, Black);
                        setColor(sibling->right, Black);
                        rotateleft(head, parent);
                        break;
                    }
                }
            }
            else
            {
                sibling = parent->left;
                if (blackLeaf(sibling) == Red)
                {
                    setColor(sibling, Black);
                    setColor(parent, Red);
                    rotateright(head, parent);
                }
                else
                {
                    if (blackLeaf(sibling->left) == Black && blackLeaf(sibling->right) == Black)
                    {
                        setColor(sibling, Red);
                        if (blackLeaf(parent) == Red)
                            setColor(parent, Black);
                        else
                            setColor(parent, DBlack);
                        ptr = parent;
                    }
                    else
                    {
                        if (blackLeaf(sibling->left) == Black)
                        {
                            setColor(sibling->right, Black);
                            setColor(sibling, Red);
                            rotateleft(head, sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, Black);
                        setColor(sibling->left, Black);
                        rotateright(head, parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete (node);
        setColor(head, Black);
    }
}

// performs a left rotation on a node in a tree by updating pointers of the parent, child, and grandparent nodes
void rotateleft(Node*& head, Node*& root)
{
    Node* right = root->right;
    root->right = right->left;

    if (root->right != nullptr)
        root->right->parent = root;

    right->parent = root->parent;

    if (root->parent == nullptr)
        head = right;
    else if (root == root->parent->left)
        root->parent->left = right;
    else
        root->parent->right = right;

    right->left = root;
    root->parent = right;
}

// performs a right rotation on a node in a tree by updating pointers of the parent, child, and grandparent nodes
void rotateright(Node*& head, Node*& root)
{
    Node* left = root->left;
    root->left = left->right;

    if (root->left != nullptr)
        root->left->parent = root;

    left->parent = root->parent;

    if (root->parent == nullptr)
        head = left;
    else if (root == root->parent->left)
        root->parent->left = left;
    else
        root->parent->right = left;

    left->right = root;
    root->parent = left;
}

// returns the node with the minimum value in a given red black tree by iteratively going down to the left child of the current node until reaching a node with a null left child
Node* minValueNode(Node*& node)
{
    Node* ptr = node;

    while (ptr->left != nullptr)
        ptr = ptr->left;

    return ptr;
}

// recursive function that traverses the tree rooted at root in-order and appends the node values to a vector data
void treetovector(Node*& root, std::vector<float>* data)
{
    if (root == nullptr)
        return;

    treetovector(root->left, data);
    data->push_back(root->data);
    treetovector(root->right, data);
}

// converts the tree with root node root to a vector of Color objects by visiting the tree in-order, adding each node's color value to the vector color as it goes.
void treetovectorForColor(Node*& root, std::vector<Color>* color)
{
    if (root == nullptr)
        return;

    treetovectorForColor(root->left, color);
    color->push_back(root->color);
    treetovectorForColor(root->right, color);
}

// prints values in ascending order
void print(Node*& root)
{
    if (root == nullptr)
        return;
    print(root->left);
    std::cout << root->data << std::endl;
    print(root->right);
}

// writes values into file
void printfile(Node*& head, const std::string& filename)
{
    std::vector<float> data;
    treetovector(head, &data);
    std::ofstream file;
    file.open(filename);
    for (int i = 0; i < data.size(); i++)
    {
        file << data[i] << std::endl;
    }
    file.close();
}
// updates values in a file
void updatefile(Node*& head, const std::string& filename)
{
    std::vector<float> data;
    treetovector(head, &data);
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file << std::endl;
    for (int i = 0; i < data.size(); i++)
    {
        file << data[i] << std::endl;
    }
    file.close();
}
// graphs [] for black, () for red
void graph(Node*& root)
{
    if (root == nullptr)
        return;
    graph(root->left);
    auto color = blackLeaf(root);
    if (color == Black)
        std::cout << "[" << root->data << "]" << std::endl;
    else
        std::cout << "(" << root->data << ")";
    graph(root->right);
    
}
// graphs into a file
void printgraph(Node*& head, const std::string& filename)
{
    std::vector<float> data;
    std::vector<Color> color;
    treetovector(head, &data);
    treetovectorForColor(head, &color);
    std::ofstream file;
    file.open(filename);
    file << std::endl;
    for (int i = 0; i < data.size(); i++)
    {
        if (color[i] == Black)
            file << "[" << data[i] << "]" << std::endl;
        else
            file << "(" << data[i] << ")" << std::endl;
    }
    file.close();
}
// updates graph in a file
void updategraph(Node*& head, const std::string& filename)
{
    std::vector<float> data;
    std::vector<Color> color;
    treetovector(head, &data);
    treetovectorForColor(head, &color);
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file << std::endl;
    for (int i = 0; i < data.size(); i++)
    {
        if (color[i] == Black)
            file << "[" << data[i] << "]" << std::endl;
        else
            file << "(" << data[i] << ")" << std::endl;
    }
    file.close();
}
