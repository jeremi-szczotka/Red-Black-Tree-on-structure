/** @file */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "node.h"
#include "functions.h"


int main(int argc, char* argv[])
{

    Node* head = nullptr;
    std::string filename = "";
    // checks if the -i option is present
    for (int i = 0; i < argc; ++i)
    {
        std::string tempArg = argv[i];
        if (tempArg == "-i")
        {
            if (filenameValidity(argv[i + 1]))
                filename = argv[i + 1];
        }
        else if (tempArg.rfind("-i", 0) == 0)
        {
            if (filenameValidity(tempArg.substr(3)))
                filename = tempArg.substr(3);
        }
    }
    // writes everything that can be done
    if (filename == "")
    {
        std::cout << "Black Red Tree" << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "Load commands from file:" << std::endl;
        std::cout << "  file <filename>" << std::endl;
        std::cout << "  *for testing: file test.txt" << std::endl;
        std::cout << "Add values to tree:" << std::endl;
        std::cout << "  add <num1> <num2> ... <numN>" << std::endl;
        std::cout << "Remove values from tree:" << std::endl;
        std::cout << "  remove <num1> <num2> ... <numN>" << std::endl;
        std::cout << "Print here:" << std::endl;
        std::cout << "   print" << std::endl;
        std::cout << "Print to file:" << std::endl;
        std::cout << "  print <filename>" << std::endl;
        std::cout << "Update file with values:" << std::endl;
        std::cout << "  print + <filename>" << std::endl;
        std::cout << "Print graph here:" << std::endl;
        std::cout << "  graph" << std::endl;
        std::cout << "Print graph to file:" << std::endl;
        std::cout << "  graph <filename>" << std::endl;
        std::cout << "Update file with new graph:" << std::endl;
        std::cout << "  graph + <filename>" << std::endl;
        std::cout << "Exit" << std::endl;
        std::cout << "  exit" << std::endl;

        std::string line;
        // checks if the line starts with file, if yes it checks the validity of the file. If the line is "exit", it breaks the loop, otherwise it extracts the command and its arguments,
        // ignoring comments starting with % symbol, and passes them to the commandErrors function
        while (true)
        {
            getline(std::cin, line);
            if (line.substr(0, 4) == "file")
            {
                if (line.length() >= 10 && filenameValidity(line.substr(5)))
                {
                    filename = line.substr(5);
                    break;
                }
                else
                {
                    std::cout << "Invalid file name." << std::endl;
                }
            }
            else if (line == "exit")
                break;
            else
            {
                std::stringstream ss(line);
                std::string command;
                std::vector<std::string> args;
                std::string temp;
                bool beforecomment = true;
                ss >> temp;
                if (temp.substr(0, 1) != "%")
                {
                    command = temp.substr(0, temp.find("%"));
                    if (temp.find("%") != std::string::npos)
                        beforecomment = false;
                }

                while (ss >> temp && beforecomment)
                {
                    if (temp.find("%") != std::string::npos)
                    {
                        int startcomment = temp.find("%");
                        if (startcomment > 0)
                            args.push_back(temp.substr(0, startcomment));
                        break;
                    }
                    args.push_back(temp);
                }

                commandErrors(head, command, args);
            }
        }
    }
    // extracts the command and its arguments, and passes them to the commandErrors function until the end of file is reached, while ignoring comments starting with % symbol
    if (filename != "")
    {

        std::ifstream file(filename);
        std::string line;
        while (getline(file, line))
        {
            std::stringstream ss(line);
            std::string command;
            std::vector<std::string> args;
            std::string temp;
            bool beforecomment = true;

            ss >> temp;
            if (temp.substr(0, 1) != "%")
            {
                command = temp.substr(0, temp.find("%"));
                if (temp.find("%") != std::string::npos)
                    beforecomment = false;
            }

            while (ss >> temp && beforecomment)
            {
                if (temp.find("%") != std::string::npos)
                {
                    int startcomment = temp.find("%");
                    if (startcomment > 0)
                        args.push_back(temp.substr(0, startcomment));
                    break;
                }
                args.push_back(temp);
            }

            commandErrors(head, command, args);
        }
        file.close();
    }
    deleteTree(head);
    return 0;
}