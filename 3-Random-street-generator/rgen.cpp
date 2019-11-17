// an example of reading random numbers from /dev/urandom
// https://stackoverflow.com/questions/35726331/c-extracting-random-numbers-from-dev-urandom
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <tuple>
#include <unistd.h>
#include <vector>

#include "rgen.hpp"

bool verbose = false;

bool print_streets(Graph graph){
    int s = graph.lenght_m_streets();
    char name;
    char name2;
    std::tuple<int,int> coordinates;
    std::string create_street;
    for (int i = 0; i < s; i++){
        name2 = i%26 + 97;
        name = std::abs(i-26)%26 +97;
        create_street = "a \"";
        create_street += name;
        create_street += name2;
        create_street += "\"";

        Street current_street = graph.get_street(i);
        int l = current_street.get_num_segments();
        for (int j = 0; j<=l ; j++){
            coordinates = current_street.get_coordinates(j);
            create_street += " ("; 
            create_street += std::to_string(std::get<0>(coordinates));
            create_street += "," ;
            create_street += std::to_string(std::get<1>(coordinates));
            create_street += ")";
        }
        std::cout << create_street << std::endl;
        usleep(5000);
    }
    return 1;
}

bool erase_streets(Graph graph){
    int s = graph.lenght_m_streets();
    char name;
    char name2;
    std::tuple<int,int> coordinates;
    std::string eliminate_street;
    for (int i = 0; i < s; i++){
        name2 = i%26 + 97;
        name = std::abs(i-26)%26 +97;
        eliminate_street = "r \"";
        eliminate_street += name;
        eliminate_street += name2;
        eliminate_street += "\"";
        std::cout << eliminate_street << std::endl;
    }
    return 1;
}

int main (int argc, char **argv) {
    Graph graph;

    int permitted_tries = 24;

    int sint_value = 10;
    int nint_value = 5;
    int lint_value = 5; /// have to ensure it is between 5 and the input
    int cint_value = 20;

    bool sflag = 0;
    bool nflag = 0;
    bool lflag = 0;
    bool cflag = 0;
    std::string svalue;
    std::string nvalue;
    std::string lvalue;
    std::string cvalue;
    // int index;
    int c;

    opterr = 0;

    // Parsing command line arguments
    // expected options are '-s', '-n', '-l' and '-c value'. All are optional
    while ((c = getopt (argc, argv, "s:n:l:c:")) != -1)
        switch (c)
        {
        case 's':
            sflag = true;
            svalue = optarg;
            sint_value = atoi(svalue.c_str());
            break;
        case 'n':
            nflag = true;
            nvalue = optarg;
            nint_value = atoi(nvalue.c_str());
            break;
        case 'l':
            lflag = true;
            lvalue = optarg;
            lint_value = atoi(lvalue.c_str());
            break;
        case 'c':
            cflag = true;
            cvalue = optarg;
            cint_value = atoi(cvalue.c_str());
            break;
        case '?':
                std::cerr << "Error: unknown command line option: " << optopt << std::endl;
            return 1;
        default:
            return 0;
        }
    if (verbose){
        std::cout << "sflag=" << sflag << " svalue " << svalue << " " << "sint_value=" << sint_value << std::endl
                << "nflag=" << nflag << " nvalue " << nvalue << " " << "nint_value=" << nint_value << std::endl
                << "lflag=" << lflag << " lvalue " << lvalue << " " << "lint_value=" << lint_value << std::endl
                << "cflag=" << cflag << " cvalue " << cvalue << " " << "cint_value=" << cint_value << std::endl;
    }

    // checking command line arguments within range
    if( sint_value < 2){std::cerr << "Error: command line argument -s needs to be >= 2 " << std::endl;   exit(0);}
    if( nint_value < 1){std::cerr << "Error: command line argument -n needs to be >= 1 " << std::endl;   exit(0);}
    if( lint_value < 5){std::cerr << "Error: command line argument -l needs to be >= 5 " << std::endl;   exit(0);}
    if( cint_value < 1){std::cerr << "Error: command line argument -c needs to be >= 1 " << std::endl;   exit(0);}

    sint_value = sint_value-1;
    nint_value = nint_value;
    lint_value = lint_value-4; /// have to ensure it is between 5 and the input
    cint_value = cint_value;

    // open /dev/urandom to read
    std::ifstream urandom("/dev/urandom");

    // check that it did not fail
    if (urandom.fail()) {
        std::cerr << "Error: cannot open /dev/urandom\n";
        return 1;
    }

    int num_segments = nint_value;
    int coordinatex = cint_value;
    int coordinatey = cint_value;
    std::tuple<int,int> prev_coordinates = std::make_tuple(coordinatex, coordinatey);
    std::tuple<int,int> coordinates = std::make_tuple(coordinatex, coordinatey);

    int tries = 0;
    int tries_coord = 0;

    std::tuple<bool,bool> o;

    char name;
    char name2;

    /* How to generate random numbers in a range? We can use modulo
    http://www.math.uaa.alaska.edu/~afkjm/csce211/fall2018/handouts/RandomFunctions.pdf
    */
//    while(1){
    while (!std::cin.eof()) {
    // int n;
    // while(std::cin >> n){
        // // read a line of input until EOL and store in a string
        // std::string line;
        // std::getline(std::cin, line);

        //         // if nothing was read, go to top of the while to check for eof
        // if (line.empty()) {
        // }

        /* cast to see the numeric value of the character and get within range*/
        // random number_streets
        tries = 0;
        tries_coord = 0;
        erase_streets(graph);
        graph.reset_graph();
        char ch = 's';
        // Have to use read() method for low-level reading
        urandom.read(&ch, 1);    
        int num_streets = (unsigned int)ch%sint_value + 2;

        int inter = 0;
        if (verbose){
            std::cout << "number_streets: " << num_streets << std::endl;
        }

        for (int i = 0 ; i < num_streets ; i++){
            name2 = i%26 + 97;
            name = std::abs(i-26)%26 +97;

            tries_coord = 0;

            if (verbose) {
                std::cout << "\nStreet " << name << name2 << ":" << std::endl;
            }
            
            Street current_street = Street();
            // random num_segments
            ch = 'n';
            urandom.read(&ch, 1);
            num_segments = (unsigned int)ch%nint_value + 1;

            if (i !=0) {
                int t = graph.get_num_streets();
                for (int i = 0; i < t; i++){
                    if (graph.get_street(i).get_num_segments() == 1 && num_segments == 1 && nint_value > 1){
                        if (verbose){
                            std::cout << "Increasing num_segments " << num_segments;
                        }
                        num_segments = num_segments + 1;
                    }
                }
            }

            current_street.set_num_segments(num_segments);

            if (verbose){
                std::cout << "n_segments: " << num_segments << std::endl;
            }
            // Creating first coordinate
            //random coordinate
            ch = 'c';
            urandom.read(&ch, 1);
            coordinatex = (int)ch%cint_value + 1;

            ch = 'c';
            urandom.read(&ch, 1);
            coordinatey = (int)ch%cint_value + 1;

            // if (coordinatex < cint_value/2 && coordinatey < cint_value/2){
            //     coordinatex = coordinatex * 2;
            // }
            // else if (coordinatex > cint_value/2 && coordinatey > cint_value/2){
            //     coordinatex = coordinatex/2;
            // }

            prev_coordinates = std::make_tuple(coordinatex, coordinatey);

            if (verbose){
                std::cout << "First coord:" << std::get<0>(prev_coordinates) << "," << std::get<1>(prev_coordinates) << std::endl;
            }

            current_street.set_coordinates(prev_coordinates);


            // start in 1 because we already created one
            for (int j = 1; j <= num_segments; j ++){
                if (verbose){
                    std::cout << "creating segment: " << j <<std::endl;
                }

                //random coordinate
                ch = 'c';
                urandom.read(&ch, 1);
                coordinatex = (int)ch%cint_value + 1;

                ch = 'c';
                urandom.read(&ch, 1);
                coordinatey = (int)ch%cint_value + 1;

                coordinates = std::make_tuple(coordinatex, coordinatey);

                o = graph.test_overlap(prev_coordinates, coordinates, i);

                // Testing
                if (current_street.test_non_zero(coordinates) && current_street.test_self_inter(coordinates) && std::get<0>(o)){
                    if (verbose) {
                        std::cout << "inter: " << std::get<1>(o) << std::endl;
                    }
                    bool t = (inter > 0);
                    if (i == num_streets-1 && j == num_segments && !t){
                        if (verbose) {
                            std::cout << "inter last: " << std::get<1>(o) << std::endl;
                        }
                        if (std::get<1>(o) > 0) {
                            current_street.set_coordinates(coordinates);
                            prev_coordinates = coordinates;
                            inter = inter + std::get<1>(o);
                        }
                        else {
                            j--;
                            tries++;
                            tries_coord++;
                            if (verbose){
                                std::cout << "tries last segment: " << tries << " with tries_segment: " << tries_coord << std::endl;
                            }
                            if (tries > permitted_tries){

                                std::cerr << "Error: failed to generate valid input for "<< tries << " simultaneous attempts. (last segment)" << std::endl;;
                                // break;
                                    exit(0);
                            }
                            
                            // if (tries_coord > 5){
                            //     if (verbose) {
                            //         std::cout << "poping last coordinate. size before: " << current_street.get_num_stored_coordinates();
                            //     }
                            //     tries_coord = 0;
                            //     current_street.pop_last_coordinates();
                            //     if (verbose) {
                            //         std::cout << " size after: " << current_street.get_num_stored_coordinates() << std::endl;
                            //     }
                            //     j--;
                            //     if (j>=0) {
                            //         prev_coordinates = current_street.get_coordinates(j);
                            //     }
                            //     else {
                            //         ch = 'c';
                            //         urandom.read(&ch, 1);
                            //         coordinatex = (int)ch%cint_value + 1;

                            //         ch = 'c';
                            //         urandom.read(&ch, 1);
                            //         coordinatey = (int)ch%cint_value + 1;

                            //         prev_coordinates = std::make_tuple(coordinatex, coordinatey);
                            //         current_street.set_coordinates(prev_coordinates);
                            //         j++;
                            //     }
                            //     if (verbose){
                            //         std::cout << "POPING last coordinate from street\ttries_coord:" << tries_coord << std::endl;
                            //         // bool trying = true;
                            //         // if (trying) {
                            //         //     print_streets(graph);
                            //         //     exit(0);                                        
                            //         // }
                            //     }
                                
                            // }
                        }
                    }
                    else{
                        inter = inter + std::get<1>(o);
                        current_street.set_coordinates(coordinates);
                        prev_coordinates = coordinates;
                    }
                }
                else {
                    j--;
                    tries++;
                    tries_coord++;
                    if (verbose){
                        std::cout << "tries: " << tries << std::endl;
                    }
                    if (tries > permitted_tries){
                        std::cerr << "Error: failed to generate valid input for "<< tries << " simultaneous attempts." << std::endl;
                        // break;
                        exit(0);
                    }
                }
            }
            // if (tries > 24){
            //     break;
            // }

            graph.set_street(current_street);        

        }
        // if (tries > 24){
        //     break;
        // }

        print_streets(graph);
        std::cout<< "g" << std::endl;


        //random waiting seconds
        ch = 'l';
        urandom.read(&ch, 1);
        int wait_sec = (unsigned int)ch%lint_value + 5;

        if (verbose){

            // std::cout << "num_segments: " << num_segments << std::endl;
            std::cout << "wait_sec: " << wait_sec << std::endl;
            // std::cout << "coordinate: " << coordinate << std::endl;
        }
        sleep(wait_sec);
    }

        // // read another 8-bit value
        // urandom.read(&ch, 1);
        // std::cout << "Random character: " << (unsigned int)ch << "\n";

        // // read a random unsigned int
        // unsigned int num = 42;
        // urandom.read((char*)&num, sizeof(int));
        // std::cout << "Random character: " << num << "\n";


    // close random stream
    urandom.close();
    return 0;
}
