/** Main file */
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include "a2ece650.hpp"

bool verbose = false;

void error (const std::string &err_msg){
    std::cerr << "Error: " << err_msg << std::endl;
}

int main(
    // int argc, char** argv
    ) {

    //Checking arguments that were used when running the code
    // for (int i = 0; i < argc; ++i) {
    //     std::string arg = argv[i];
    //     if (arg == "--verbose"|| arg == "-v") {//Check if the verbose flag was indicated
    //         verbose = true; //If it was indicated, set the verbose to true
    //     }
    // }

    // Graph graph;
    Graph graph;

    std::string err_msg;
    char cmd;

    // read from stdin until EOF
    while (!std::cin.eof()) {

        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);

        bool trying = false;
        if (trying) {
            std::cout << "a2 saw" << line << std::endl;
        }


        // vector nums carries the args from parse_line
        std::list<unsigned> nums;

        //list to store shortest path
        std::vector<unsigned> short_path;

        // if nothing was read, go to top of the while to check for eof
        if (line.empty()) {
            continue;
        }
        
        if (parse_line(line, cmd, nums, err_msg)) {
            std::string str;
            switch (cmd) {
            case 'V':
                if (nums.size() == 1){
                    int num = nums.front();
                    
                    graph.set_num_vertices(num);

                    //print input graph    
                    std::cout << "V " << num << std::endl;

                    if (verbose){
                        std::cout << "Num of vertices stored: "<< graph.get_num_vertices() << std::endl;
                    }
                    // int V = graph.get_num_vertices();
                    if (!graph.ini_adjacency_matrix()){
                        err_msg = "Something broke when creating the adjacency matrix";
                        error(err_msg);
                    }
                    break;
                } 
                error("Unexpected arguemtn for V");                
            case 'E':
                // set the edges of the graph. nums is a list: each two consecutive numbers are an edge.
                graph.set_edges(nums);
                
                // print input graph
                str = "E {";
                for (auto i = nums.begin(); i != nums.end(); ++i){
                    str += "<";
                    str += std::to_string(*i);
                    str += ",";
                    i++;
                    str += std::to_string(*i);
                    str += ">,";
                }
                str.pop_back();
                str += "}";
                std::cout << str << std::endl;

                // Call adjacency_matrix
                if (graph.adjacency_matrix(err_msg)){

                } else {
                    error(err_msg);
                }

                
                break;
            case 's': 
                // Call dijkstra. nums contains the source and target. Short_path will return the shortest path.               
                if (graph.dijkstra(nums, short_path, err_msg)){
                    if(print_short_path(short_path)){
                        break;
                    } 
                    error("There was a problem when printing the shortest path");
                    break;
                }
                // else{
                //     error("Something went wrong");
                // }
            default: error(err_msg);
            }
        } else {
            error(err_msg);
        }
    }
}

