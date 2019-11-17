// based on the example from
// https://stackoverflow.com/questions/13041416/redirect-stdout-of-two-processes-to-another-processs-stdin-in-linux-c

#include <iostream>
#include <signal.h>
#include <string>
// needed to use waitpid
#include <sys/wait.h>
#include <vector>
#include <unistd.h>
#include <string.h>

#include "ece650-a3.hpp"

bool verbose = false;
bool talking = false;

/// Entry point of process rgen
// int proc_rgen(std::string s_value, int n_value, int l_value, int c_value) {
int proc_rgen_string(std::string s_value, std::string n_value, std::string l_value, std::string c_value) {
    // Process rgen reading from driver and writing to a1

    if (verbose){
        for (int i = 0; i < 3; i++)
        {
            std::cout << "[killer]: Hi" << std::endl;
            sleep(0.5);
        }
    }
    if (verbose) {
        std::cout << "[rgen] Initializing rgen" << std::endl;
    }

    char* argv[10];

    // ./rgen -l 6 -s 3 -n 3 -c 10  snlc
    argv[0] = (char*)"rgen";
    
    // const char *cs_value = s_value.c_str();

    argv[1] = (char*)"-s";
    std::string str = s_value;
    char *cs_value = new char[str.length() + 1];
    strcpy(cs_value, str.c_str());
    argv[2] = cs_value;

    argv[3] = (char*)"-n";
    str = n_value;
    char *cn_value = new char[str.length() + 1];
    strcpy(cn_value, str.c_str());
    argv[4] = cn_value;

    argv[5] = (char*)"-l";
    str = l_value;
    char *cl_value = new char[str.length() + 1];
    strcpy(cl_value, str.c_str());
    argv[6] = cl_value;

    argv[7] = (char*)"-c";
    str = c_value;
    char *cc_value = new char[str.length() + 1];
    strcpy(cc_value, str.c_str());
    argv[8] = cc_value;
    // argv[1] = (char*)"-l";
    argv[9] = nullptr;

    // delete [] cs_value;

    // std::vector<char*> args;
    // args.push_back((char*)"./rgen");
    // args.push_back((char*)"-s");
    // args.push_back((char*)s_value);
	// args.push_back((char*)"-n");
    // args.push_back((char*)n_value);
    // args.push_back((char*)"-l");
    // args.push_back((char*)l_value);
    // args.push_back((char*)"-c");
    // args.push_back((char*)c_value);
    // args.push_back(0);
    // if (verbose){
    //     std::cout << "executing: " << args[0] << std::endl;
    // }
	// execv(args[0], &args.front());
    execv("./rgen", argv);
    perror ("Error from arie");

    // while (!std::cin.eof()) {
    //     // read a line of input until EOL and store in a string
    //     std::string line;
    //     std::getline(std::cin, line);
    //     if (line.size () > 0){
    //         std::cout << "[rgen] saw: " << line << std::endl;}
    //     std::cout << "[rgen] testing" << std::endl;
    // }
    // std::cout << "[rgen] saw EOF" << std::endl;
    // sleep(2);
    // if (verbose) {
    //     std::cout << "[rgen] Exiting" << std::endl;
    // }
    return 0;
}

int proc_rgen(int s_value, int n_value, int l_value, int c_value) {
char* rgen_argv[10];

    //Inspired by https://stackoverflow.com/a/3446272.
    //Buffer configuration

    if (talking){
        for (int i = 0; i < 3; i++)
        {
            std::cout << "[killer]: Hi" << std::endl;
            // sleep(0.5);
        }
    }
    if (talking) {
        std::cout << "[rgen] Initializing rgen" << std::endl;
    }

    char sprintf_buffer_s[20];
    char sprintf_buffer_n[20];
    char sprintf_buffer_l[20];
    char sprintf_buffer_c[20];
    s_value = 4;
    sprintf (sprintf_buffer_s, "%d", s_value);
    sprintf (sprintf_buffer_n, "%d", n_value);
    sprintf (sprintf_buffer_l, "%d", l_value);
    sprintf (sprintf_buffer_c, "%d", c_value);
    

    rgen_argv[0] = (char*)"rgen";
    rgen_argv[1] = (char*)"-s";
    rgen_argv[2] = sprintf_buffer_s;
    rgen_argv[3] = (char*)"-n";
    rgen_argv[4] = sprintf_buffer_n;
    rgen_argv[5] = (char*)"-l";
    rgen_argv[6] = sprintf_buffer_l;
    rgen_argv[7] = (char*)"-c";
    rgen_argv[8] = sprintf_buffer_c;
    rgen_argv[9] = nullptr;

    execv("./rgen", rgen_argv);
    perror ("Error from arie");

    // sleep(2);
    if (verbose) {
        std::cout << "[rgen] Exiting" << std::endl;
    }
    return 0;
}

/// Entry point of process assignment1
int proc_a1(void) {
    // Process a1 reading from rgen and writing to a2
    // while (!std::cin.eof()) {
    //     // read a line of input until EOL and store in a string
    //     std::string line;
    //     std::getline(std::cin, line);
    //     if (line.size () > 0){
    //         if (verbose){
    //             std::cout << "[a1] saw: " << line << std::endl;
    //         }
    //     }
    // }
    if (talking){
        std::cout << "[a1] Initializing" << std::endl;
    }

    char* argv_a1[2];
    argv_a1[0] = (char*)"ece650-a1.py";
    argv_a1[1] = nullptr;


    execv("./ece650-a1.py", argv_a1);
    perror ("Error from arie");

    if (verbose){
        std::cout << "[a1] Exiting" << std::endl;
    }
    return 0;
}

/// Entry point of process assignment2
int proc_a2(void) {
    // Process a2 reading from a1 and printing to std_out
    // while (!std::cin.eof()) {
    //     // read a line of input until EOL and store in a string
    //     std::string line;
    //     std::getline(std::cin, line);
    //     if (line.size () > 0){
    //         if (verbose) {
    //             std::cout << "[a2] saw: " << line << std::endl;
    //         }
    //     }
    // }
    if (verbose){
        std::cout << "[a2] initializing" << std::endl;
    }
    char* argv_a2[2];
    argv_a2[0] = (char*)"ece650-a2";
    argv_a2[1] = nullptr;

    execv("./ece650-a2", argv_a2);
    perror ("Error from arie");
    if (verbose){
        std::cout << "[a2] saw EOF" << std::endl;
    }

    return 0;
}

int proc_killer(std::vector<pid_t> &kids) {
    // Process rgen reading from driver and writing to a1
    if (talking){
        for (int i = 0; i < 3; i++)
        {
            std::cout << "[killer]: Hi" << std::endl;
            // sleep(0.5);
        }
    }
    while (!std::cin.eof()) {
        // read a line of input until EOL and store in a string
        std::string line;
        std::getline(std::cin, line);
        std::cout << line << std::endl;

        if (line.empty()) {
            continue;
        }
        if (talking){
            if (line.size () > 0){
                std::cout << "[killer] saw: " << line << std::endl;
            }
        }
    }
    // std::cout << "[rgen] saw EOF" << std::endl;
    // sleep(2);
    
    // send kill signal to all children
    sleep(3);
    for (pid_t k : kids) {
        int status;
        kill (k, SIGTERM);
        waitpid(k, &status, 0);
        if (talking){
            std::cout << "[killer] Killed " << k << std::endl;
        }
    }
    if (verbose){
        std::cout << "[killer] Exiting" << std::endl;
    }
    return 0;
}

int main (int argc, char **argv) {

    // if (verbose){
    //         // Print command line arguments that were used to start the program
    //     std::cout << "Called with " << argc << " arguments\n";
    //     for (int i = 1; i < argc; ++i){
    //         std::cout << "Arg " << i << " is " << argv[i] << "\n";
    //         std::cout << "Arg " << i << " is " << typeid(argv[i]).name() << "\n";
    //     }
    // }
    bool sflag = 0;
    bool nflag = 0;
    bool lflag = 0;
    bool cflag = 0;
    std::string svalue;
    std::string nvalue;
    std::string lvalue;
    std::string cvalue;
    int sint_value = 10;
    int nint_value = 5;
    int lint_value = 5;
    int cint_value = 20;
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
                std::cerr << "Error: unknown or incomplete command line option: " << optopt << std::endl;
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
    if( sint_value < 2){std::cerr << "Error: the command line argument -s needs to be >= 2 " << std::endl;   exit(0);}
    if( nint_value < 1){std::cerr << "Error: the command line argument -n needs to be >= 1 " << std::endl;   exit(0);}
    if( lint_value < 5){std::cerr << "Error: the command line argument -l needs to be >= 5 " << std::endl;   exit(0);}
    if( cint_value < 1){std::cerr << "Error: the command line argument -c needs to be >= 1 " << std::endl;   exit(0);}

    // To check if there were more arguments
    // if (optind < argc) {
    //     std::cout << "Found positional arguments\n";
    //     for (index = optind; index < argc; index++)
    //         std::cout << "Non-option argument: " << argv[index] << "\n";
    // }

    std::vector<pid_t> kids;
    // create a pipe
    int rgen_to_a1[2];
    pipe(rgen_to_a1);

    // create a pipe
    int a1_killer_to_a2[2];
    pipe(a1_killer_to_a2);

    // // create a pipe
    // int killer_to_a2[2];
    // pipe(killer_to_a2);

    // Child to run rgen
    pid_t child_pid_rgen;
    child_pid_rgen = fork ();
    if (child_pid_rgen == 0)
    {
        // redirect stdout to the pipe
        dup2(rgen_to_a1[1], STDOUT_FILENO);
        close(rgen_to_a1[0]);
        close(rgen_to_a1[1]);     // Close this too!

        close(a1_killer_to_a2[0]);
        close(a1_killer_to_a2[1]);

        // start process rgen
        // return proc_rgen_string(svalue, nvalue, lvalue, cvalue);
        return proc_rgen(sint_value, nint_value, lint_value, cint_value);
    }
    else if (child_pid_rgen < 0) {
        std::cerr << "Error: could not fork rgen\n";
        return 1;
    }
    if (verbose){
        std::cout << "[Driver]: created " << child_pid_rgen << " rgen" << std::endl;
    }
    kids.push_back(child_pid_rgen);

    // Child to run a1
    pid_t child_pid;
    child_pid = fork();
    if (child_pid == 0)
    {
        // redirect stdin from the pipe
        dup2(rgen_to_a1[0], STDIN_FILENO);
        close(rgen_to_a1[1]);
        close(rgen_to_a1[0]);

        // redirect stdout to the pipe of a2
        dup2(a1_killer_to_a2[1], STDOUT_FILENO);
        close(a1_killer_to_a2[0]);
        close(a1_killer_to_a2[1]);     // Close this too!

        // trying
        // std::cout << "V 15" << std::endl;
        // std::cout<< "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}" << std::endl;

        // start process a1
        return proc_a1();
    }
    else if (child_pid < 0) {
        std::cerr << "Error: could not fork a1\n";
        return 1;
    }

    if (verbose){
        std::cout << "[Driver]: created " << child_pid << " a1" << std::endl;
    }
    kids.push_back(child_pid);
    child_pid = 0;

    
    // // Child to run a2
    // child_pid = fork();
    // if (child_pid == 0)
    // {
    //     close(rgen_to_a1[0]);
    //     close(rgen_to_a1[1]);

    //     // redirect stdin from the pipe
    //     dup2(a1_killer_to_a2[0], STDIN_FILENO);
    //     close(a1_killer_to_a2[1]);
    //     close(a1_killer_to_a2[0]);
    //     return proc_a2();
    // }
    // else if (child_pid < 0) {
    //     std::cerr << "Error: could not fork Killer\n";
    //     return 1;
    // }
    // if (verbose){
    //     std::cout << "[Driver]: created " << child_pid << " Killer" << std::endl;
    // }
    // kids.push_back(child_pid);
    // child_pid = 0;

    //Child to run Killer
    child_pid = fork();
    if (child_pid == 0)
    {
        // close rgen_to_a1
        close(rgen_to_a1[0]);
        close(rgen_to_a1[1]);

        // close a1_to_a2
        dup2(a1_killer_to_a2[1], STDOUT_FILENO);
        close(a1_killer_to_a2[0]);
        close(a1_killer_to_a2[1]);

        // trying
        // usleep(5000);
        // std::cout << "created pipe from Killer" << std::endl;
        // usleep(5000);

        // // redirect stdout to the pipe
        // dup2(killer_to_a2[1], STDOUT_FILENO);
        // close(killer_to_a2[0]);
        // close(killer_to_a2[1]);     // Close this too!

        // start process killer
        // proc_killer(kids);


        while (!std::cin.eof()) {
            // read a line of input until EOL and store in a string
            std::string line;
            std::getline(std::cin, line);
            std::cout << line << std::endl;

            if (line.empty()) {
                continue;
            }
            if (talking){
                if (line.size () > 0){
                    std::cout << "[killer] saw: " << line << std::endl;
                }
            }
        }
        // std::cout << "[rgen] saw EOF" << std::endl;
        // sleep(2);
        
        // send kill signal to all children
        sleep(3);
        for (pid_t k : kids) {
            int status;
            kill (k, SIGTERM);
            waitpid(k, &status, 0);
            if (talking){
                std::cout << "[killer] Killed " << k << std::endl;
            }
        }


    }
    else if (child_pid < 0) {
        std::cerr << "Error: could not fork Killer\n";
        return 1;
    }
    if (verbose){
        std::cout << "[Driver]: created " << child_pid << " Killer" << std::endl;
    }
    kids.push_back(child_pid);
    child_pid = 0;

    close(rgen_to_a1[0]);
    close(rgen_to_a1[1]);

    // redirect stdin from the pipe
    dup2(a1_killer_to_a2[0], STDIN_FILENO);
    close(a1_killer_to_a2[1]);
    close(a1_killer_to_a2[0]);
    return proc_a2();

    // }
    // return 0;
    return 0;
}
