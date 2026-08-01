#include <iostream>
#include <fstream>
#include <string>
#include "../include/Airport.hpp"

int main() {
    // 1. Open a pipe to the file
    std::ifstream file("data/test.txt");

    // 2. Safety check: make sure the file exists
    if (!file.is_open()) {
        std::cerr << "Error: Could not open data/test.txt!" << std::endl;
        return 1;
    }

    std::cout << "Successfully opened data/test.txt!\n--- File Contents ---" << std::endl;

    // 3. Read line by line
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    // 4. Close the file stream
    file.close();

    return 0;
}