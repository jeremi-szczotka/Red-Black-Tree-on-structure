/** @file */

#include <fstream>
#include <sstream>
#include "functions.h"

// checks if file is opening without troubles and format is .txt
bool filenameValidity(const std::string& tempfilename)
{
    if (tempfilename.length() > 0 && tempfilename.substr(tempfilename.length() - 4) == ".txt")
    {
        std::ifstream file(tempfilename);
        if (file.good())
        {
            file.close();
            return true;
        }
        else
        {
            file.close();
            return false;
        }
    }
    else
        return false;
}

// checks if format is ok
bool filenameValidityTxt(const std::string& tempfilename)
{
    if (tempfilename.length() > 0 && tempfilename.substr(tempfilename.length() - 4) == ".txt")
    {
        return true;
    }
    else
        return false;
}
// checks if data is correct, else prints out error
void commandErrors(Node*& head, const std::string& command, const std::vector<std::string>& args)
{
    // checks if add works
    if (command == "add")
    {
        std::vector<float> numbers;
        for (int i = 0; i < args.size(); i++)
        {
            try
            {
                float temp = std::stof(args[i]);
                std::stringstream ss;
                ss << temp;
                std::string tempstr = ss.str();
                if (args[i] == tempstr)
                    numbers.push_back(temp);
            }
            catch (std::invalid_argument)
            {
            }
        }
        if (numbers.size() > 0)
        {
            add(head, numbers);
        }
        else
            std::cout << "# Invalid arguments for add command" << std::endl;
    }
    // checks if remove works
    else if (command == "remove")
    {
        std::vector<float> numbers;
        for (int i = 0; i < args.size(); i++)
        {
            try
            {
                float temp = std::stof(args[i]);
                std::stringstream ss;
                ss << temp;
                std::string tempstr = ss.str();
                if (args[i] == tempstr)
                    numbers.push_back(temp);
            }
            catch (std::invalid_argument)
            {
            }
        }
        if (numbers.size() > 0)
            remove(head, numbers);
        else
            std::cout << "# Invalid arguments for remove command" << std::endl;
    }
    // checks if print works(with update)
    else if (command == "print")
    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        if (args.size() == 2 && args[0] == "+")
        {
            if (filenameValidityTxt(args[1]))
                updatefile(head, args[1]);
            else
            {
                std::cout << "# Invalid arguments for print command" << std::endl;
                print(head);
            }
        }
        else if (args.size() == 1)
        {

            if (filenameValidityTxt(args[0]))
                printfile(head, args[0]);
            else
            {
                std::cout << "# Invalid arguments for print command" << std::endl;
                print(head);
            }
        }
        else
        {
            print(head);
        }
    }
    // checks if graph works(with update)
    else if (command == "graph")
    {
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        if (args.size() == 2 && args[0] == "+")
        {
            if (filenameValidityTxt(args[1]))
            {
                updategraph(head, args[1]);
            }
            else
            {
                std::cout << "# Invalid arguments for graph command" << std::endl;
            }
        }
        else if (args.size() == 1)
        {
            if (filenameValidityTxt(args[0]))
            {
                printgraph(head, args[0]);
            }
            else
            {
                std::cout << "# Invalid arguments for graph command" << std::endl;
            }
        }
        else
        {
            graph(head);
        }
    }
}

// returns the color black for a leaf node or the stored color of the node
Color blackLeaf(Node*& node)
{
    if (node == nullptr)
        return Black;

    return node->color;
}

// sets the color of a node
void setColor(Node*& node, Color color)
{
    if (node == nullptr)
        return;

    node->color = color;
}

// removes tree from memory
void deleteTree(Node*& root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = nullptr;
    }
}