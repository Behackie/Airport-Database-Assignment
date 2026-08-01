#ifndef AIRPORT_HPP
#define AIRPORT_HPP

#include <string>

// Blueprint for a single airport record
struct Airport {
    std::string code;       // IATA code (e.g., "ACC")
    std::string icao;       // ICAO code (e.g., "DGAA")
    std::string name;       // Airport name
    std::string country;    // Country code/name
    std::string city;       // City name
};

#endif