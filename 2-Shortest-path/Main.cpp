/** Main file */
#pragma once
#include <iostream>
#include <sstream>
#include <vector>

#include "a2ece650.hpp"

bool verbose = true;

int main(int argc, char** argv) {

    // Register reg;
    Graph graph;
    // read from stdin until EOF
    while (!std::cin.eof()) {

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);

        // if nothing was read, go to top of the while to check for eof
        if (line.size() == 0) {
            continue;
        }

        char cmd;
        std::string arg;
        std::string err_msg;
        if (parse_line(line, cmd, arg, err_msg)) {
            switch (cmd) {
            case 'V':
                graph.set_num_vertices(std::stoi(arg));
                if (verbose){
                    std::cout << "Num of vertices stored: "<< graph.get_num_vertices() << std::endl;
                }
                break;
            case 'E':
                // graph.sub(arg);
                break;
            case 's':
                // graph.reset();
                break;
            }
        }
        else {
            std::cout << "Error: " << err_msg << std::endl;
        }
    }
}

