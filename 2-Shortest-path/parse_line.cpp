#pragma once
#include <iostream>
#include <sstream>
#include <string>

#include "a2ece650.hpp"
bool verbose1 = true;

std::string replace_substring (std::string str, std::string to_find, std::string to_replace) {
    // From https://stackoverflow.com/a/4643526
    size_t index = 0;
    int size_to_find = to_find.length();

    while (true) {
        // Locating the substring to replace

        index = str.find(to_find, index);
        if (index == std::string::npos) {

            break;
        }
        // Replacing the "," for space
        str.replace(index, size_to_find, to_replace);
        //Advance the index forward
        index++;
    }
    return str;
}

bool parse_line (const std::string &line,
                 char &cmd, std::string &arg, std::string &err_msg) {

    std::istringstream input(line);

    // remove whitespace
    std::ws(input);

    // Check for empty command
    if (input.eof()) {
        err_msg = "Empty command";
        return false;
    }

    // Read first caracter = command
    char ch;
    input >> ch;

    if (input.fail()) {
        err_msg = "Failed to read input";
        return false;
    }

    // Command = 'V'
    if (ch == 'V') {
        // remove whitespace
        std::ws(input);
        int num;
        input >> num;
        if (input.fail()) {
            err_msg = "Missing or bad argument for V";
            return false;
        }
        ws(input);
        if (!input.eof()) {
            err_msg = "Unexpected argument for V";
            return false;
        }
        cmd = ch;
        arg = std::to_string(num);
        if (verbose1){
            std::cout << "\nYour character: " << cmd << "\nYour arguments: " << arg << std::endl;
        }
        return true;
    }
    // Command = 'E'
    else if (ch == 'E') {
        // remove whitespace
        std::ws(input);
        std::string vertices;
        input >> vertices;
        if (input.fail()) {
            err_msg = "Missing or bad argument for E";
            return false;
        }
        ws(input);
        if (!input.eof()) {
            err_msg = "Unexpected argument for E";
            return false;
        }
        cmd = ch;
        arg = vertices;
        arg = replace_substring(arg, ",", " ");
        arg = replace_substring(arg, "<", " ");
        arg = replace_substring(arg, ">", " ");
        if (verbose1){
            std::cout << "\nYour character: " << cmd << "\nYour arguments: " << arg << std::endl;
        }
        return true;
    }
    // Command = 's'
    else if (ch == 's') {
        // remove whitespace
        // std::ws(input);
        int vert;
        // 
        input >> vert;

        if (input.fail()) {
            err_msg = "Missing or bad argument for s";
            return false;
        }

        std::string vertices = std::to_string(vert);
        

        input >> vert;
        
        if (input.fail()) {
            err_msg = "Missing or bad argument for s";
            return false;
        }
        vertices.append(" ");
        vertices.append(std::to_string(vert));
        ws(input);
        if (!input.eof()) {
            err_msg = "Unexpected argument for s";
            return false;
        }
        cmd = ch;
        arg = vertices;

        if (verbose1){
            std::cout << "\nYour character: " << cmd << "\nYour arguments: " << arg << std::endl;
        }
        return true;
    }
    else {
        err_msg = "Unknown command";
        return false;
    }

}