#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "../include/Airport.hpp"

// Reads data from CSV files and stores them in memory
void loadAirportData(const std::string& filepath, std::unordered_map<std::string, Airport>& db) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filepath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        Airport airport;

        std::getline(ss, airport.code, ',');
        std::getline(ss, airport.icao, ',');
        std::getline(ss, airport.name, ',');
        std::getline(ss, airport.city, ',');
        std::getline(ss, airport.country, ',');

        // Merge or Insert into map
        if (db.find(airport.code) != db.end()) {
            if (!airport.icao.empty()) db[airport.code].icao = airport.icao;
            if (!airport.name.empty()) db[airport.code].name = airport.name;
            if (!airport.city.empty()) db[airport.code].city = airport.city;
            if (!airport.country.empty()) db[airport.code].country = airport.country;
        } else {
            db[airport.code] = airport;
        }
    }
    file.close();
}

int main() {
    std::unordered_map<std::string, Airport> database;

    // Load airport data
    loadAirportData("data/test.txt", database);

    std::cout << "===========================================\n";
    std::cout << "       AIRPORT DATABASE SYSTEM LOADED      \n";
    std::cout << "===========================================\n\n";

    std::string searchCode;
    while (true) {
        std::cout << "Enter Airport Code to search (or type 'EXIT' to quit): ";
        std::cin >> searchCode;

        if (searchCode == "EXIT" || searchCode == "exit") {
            std::cout << "Exiting system. Goodbye!\n";
            break;
        }

        if (database.find(searchCode) != database.end()) {
            Airport a = database[searchCode];
            std::cout << "\n--- AIRPORT DETAILS ---" << std::endl;
            std::cout << "Code:    " << a.code << std::endl;
            if (!a.icao.empty()) std::cout << "ICAO:    " << a.icao << std::endl;
            std::cout << "Name:    " << a.name << std::endl;
            std::cout << "City:    " << a.city << std::endl;
            std::cout << "Country: " << a.country << std::endl;
            std::cout << "-----------------------\n" << std::endl;
        } else {
            std::cout << "\n[!] Airport code '" << searchCode << "' not found in database.\n" << std::endl;
        }
    }

    return 0;
}