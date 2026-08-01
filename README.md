# Airport Database Project v0

## Overview
Parses two airport data files and merges them (matched by airport code) into
a single in-memory database, then lists all airports on request.

## Files
- src/main.cpp - program logic
- include/Airport.hpp - Airport data structure
- data/airports_0.txt - comma-separated file with code, icao, name, coordinates, country, city, etc.
- data/airports_1.txt - tab-separated file with code and a combined city/state/country field
- build.bat - compiles the project

## How to compile
Requires g++ with C++17 support (MinGW on Windows).

From the project root:
    .\build.bat

This runs:
    g++ -std=c++17 src/main.cpp -o AirportDatabaseApp.exe

## How to run
    .\AirportDatabaseApp.exe

Make sure data/airports_0.txt and data/airports_1.txt exist relative to
where you run the executable from.

## Usage
On launch, choose one of:
- a - Search (not yet implemented)
- b - Print (not yet implemented)
- c - List all airports in the database

Any other input is treated as an error and the program exits immediately.

## Known limitations
- Some airport codes only appear in airports_1.txt, which has no name/ICAO
  column, so those entries will have a blank Name field.
- Country codes from airports_0.txt are 2-letter ISO codes (e.g. EG),
  not full country names.
