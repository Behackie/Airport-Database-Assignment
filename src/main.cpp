#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "../include/Airport.hpp"

static std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n\"");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n\"");
    return s.substr(start, end - start + 1);
}

// some fields have commas inside quotes (e.g. state names), so a plain
// getline(ss, x, ',') breaks them up wrong -- this keeps quoted commas intact
static std::vector<std::string> splitLine(const std::string& line, char delim) {
    std::vector<std::string> fields;
    std::string field;
    bool inQuotes = false;

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == delim && !inQuotes) {
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    fields.push_back(field);
    return fields;
}

void loadAirports0(const std::string& filepath, std::unordered_map<std::string, Airport>& db, std::vector<std::string>& order) {
    std::ifstream file(filepath);
    if (!file.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (firstLine) { firstLine = false; continue; } // skip header row

        std::vector<std::string> f = splitLine(line, ',');
        if (f.size() < 11) continue;

        // columns: code,icao,name,lat,lon,elevation,url,time_zone,city_code,country,city,...
        Airport temp;
        temp.code    = trim(f[0]);
        temp.icao    = trim(f[1]);
        temp.name    = trim(f[2]);
        temp.country = trim(f[9]);
        temp.city    = trim(f[10]);

        if (temp.code.empty()) continue;

        if (db.find(temp.code) != db.end()) {
            // already have this airport from another file, only fill in blanks
            if (!temp.name.empty())    db[temp.code].name = temp.name;
            if (!temp.city.empty())    db[temp.code].city = temp.city;
            if (!temp.country.empty()) db[temp.code].country = temp.country;
            if (!temp.icao.empty())    db[temp.code].icao = temp.icao;
        } else {
            db[temp.code] = temp;
            order.push_back(temp.code);
        }
    }
}

void loadAirports1(const std::string& filepath, std::unordered_map<std::string, Airport>& db, std::vector<std::string>& order) {
    std::ifstream file(filepath);
    if (!file.is_open()) return;

    std::string line;
    bool firstLine = true;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        if (firstLine) { firstLine = false; continue; }

        std::vector<std::string> f = splitLine(line, '\t'); // this file is tab separated
        if (f.size() < 2) continue;

        Airport temp;
        temp.code = trim(f[0]);
        if (temp.code.empty()) continue;

        // CityName column looks like "CITY, STATE, COUNTRY" all in one field
        std::vector<std::string> cityParts = splitLine(f[1], ',');
        if (!cityParts.empty()) {
            temp.city = trim(cityParts.front());
            temp.country = trim(cityParts.back());
        }

        if (db.find(temp.code) != db.end()) {
            if (!temp.city.empty())    db[temp.code].city = temp.city;
            if (!temp.country.empty()) db[temp.code].country = temp.country;
        } else {
            db[temp.code] = temp;
            order.push_back(temp.code);
        }
    }
}

int main() {
    std::unordered_map<std::string, Airport> database;
    std::vector<std::string> airportOrder;

    loadAirports0("data/airports_0.txt", database, airportOrder);
    loadAirports1("data/airports_1.txt", database, airportOrder);

    std::cout << "Welcome to Airport Database Project v0!" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "a: Search" << std::endl;
    std::cout << "b: Print" << std::endl;
    std::cout << "c: List" << std::endl;

    std::string choice;
    std::cin >> choice;

    if (choice == "a") {
        std::cout << "Search option is not currently supported!" << std::endl;
        return 0;
    } else if (choice == "b") {
        std::cout << "Print option is not currently supported!" << std::endl;
        return 0;
    } else if (choice == "c") {
        int index = 1;
        for (const std::string& code : airportOrder) {
            const Airport& a = database[code];
            std::cout << index++ << ". " << a.code << std::endl;
            std::cout << "    Name: " << a.name << std::endl;
            std::cout << "    Country: " << a.country << std::endl;
            std::cout << "    City: " << a.city << std::endl;
        }
    } else {
        std::cout << "Error: Invalid option selected!" << std::endl;
        return 1;
    }

    return 0;
}