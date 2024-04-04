/* @file */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include "node.h"
/**
 * @brief Check if the given file name is valid.
 *
 * @param tempfilename The name of the file to check.
 *
 * @return True if the file name is valid, false otherwise.
 */
bool filenameValidity(const std::string& tempfilename);
/**
 * @brief Checks the validity of a filename format.
 *
 * @param tempfilename The filename to be checked.
 *
 * @return Returns `true` if the filename is valid (ends with ".txt"), `false` otherwise.
 */
bool filenameValidityTxt(const std::string& tempfilename);
/**
 * @brief Processes the command and performs the operation or print out error.
 *
 * @param head A reference to the head of the linked list.
 * @param command The command to be processed.
 * @param args A vector of strings representing the arguments for the command.
 */
void commandErrors(Node*& head, const std::string& command, const std::vector<std::string>& args);
/**
 * @brief Returns the color of the leaf node.
 *
 * @param node A reference to the node in the tree.
 * @return Color of the leaf node.
 */
Color blackLeaf(Node*& node);
/**
 * @brief Sets the color of the node.
 *
 * @param node A reference to the node in the tree.
 * @param color The color to be set for the node.
 */
void setColor(Node*& node, Color color);
/**
 * @brief Delete structure from memory.
 *
 * @param root A reference to the root in the tree.
 */
void deleteTree(Node*& root);

#endif
