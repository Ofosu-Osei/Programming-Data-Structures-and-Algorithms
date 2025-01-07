#include "port.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "ship.hpp"

Port::Port() : ships(), st() {
}
//Destructor
Port::~Port() {
  cleanupShips();
}
// Function to add a ship
void Port::addShip(Ship * ship) {
  ships.push_back(ship);
}
// Swap function
void Port::swap(Port & rhs) {
  std::swap(ships, rhs.ships);
  std::swap(st, rhs.st);
}
// Copy constructor
Port::Port(const Port & rhs) : ships(), st(rhs.st) {
  for (size_t i = 0; i < rhs.ships.size(); ++i) {
    ships.push_back(rhs.ships[i]->copy());
  }
}
// Copy assignment operator
Port & Port::operator=(const Port & rhs) {
  if (this != &rhs) {
    Port temp(rhs);
    swap(temp);
  }
  return *this;
}

// Function to load ships from file
void Port::parseShipsFromFile(const std::string & filename) {
  std::ifstream inputFile(filename.c_str());
  std::vector<Ship *> ships;
  std::set<std::string> shipNames;
  std::string line;

  if (!inputFile) {
    throw std::runtime_error("Input Error: Failed to open ship file " + filename);
  }

  while (std::getline(inputFile, line)) {
    Ship * ship = NULL;

    try {
      ship = Ship::createShip(line);

      // Handle duplicate ship names
      if (shipNames.insert(ship->getName()).second == false) {
        throw std::runtime_error("Parse Error: Duplicate ship name found: " +
                                 ship->getName());
      }
      addShip(ship);
    }
    catch (const std::exception & e) {
      delete ship;
      throw;
    }
  }
}

// Function to find a ship by name
Ship * Port::findShipByName(const std::string & name) {
  for (size_t i = 0; i < ships.size(); ++i) {
    if (ships[i]->getName() == name) {
      return ships[i];
    }
  }
  return NULL;
}

// Function to compute capacities on each route
std::map<std::string, unsigned long> Port::computeCapacities() const {
  std::map<std::string, unsigned long> route_tot_cap;

  for (size_t i = 0; i < ships.size(); ++i) {
    const Ship * ship = ships[i];
    std::string route = "(" + ship->getSource() + " -> " + ship->getDestination() + ")";
    route_tot_cap[route] += ship->getCapacity();
  }

  return route_tot_cap;
}

// Function to print the computed capacities
void Port::printRouteCapacity(
    const std::map<std::string, unsigned long> & route_tot_cap) {
  for (std::map<std::string, unsigned long>::const_iterator it = route_tot_cap.begin();
       it != route_tot_cap.end();
       ++it) {
    std::cout << it->first << " has total capacity " << it->second << std::endl;
  }
}

// Function to parse cargo from the input file
std::vector<Cargo> Port::parseCargoFromFile(const std::string & filename) {
  std::ifstream inputFile(filename.c_str());
  std::vector<Cargo> cargoList;
  std::string line;

  if (!inputFile) {
    throw std::runtime_error("Input Error: Failed to open file " + filename);
  }

  while (std::getline(inputFile, line)) {
    try {
      cargoList.push_back(Cargo(line));
    }
    catch (const std::exception & e) {
      std::cerr << "Error parsing cargo: " << e.what() << " (line: " << line << ")"
                << std::endl;
      throw;
    }
  }

  return cargoList;
}

// Function to find eligible ships
std::vector<Ship *> Port::findEligibleShips(const Cargo & cargo) {
  std::vector<Ship *> eligibleShips;

  for (size_t i = 0; i < ships.size(); ++i) {
    if (ships[i]->canCarry(cargo)) {
      eligibleShips.push_back(ships[i]);
    }
  }

  // Sort ships alphabetically by name
  std::sort(eligibleShips.begin(), eligibleShips.end(), Ship::compareShipsByName());

  return eligibleShips;
}

void Port::addToShipTree(uint64_t remainingCapacity, Ship * ship) {
  st.add(remainingCapacity, ship);
}

void Port::resetShipTree() {
  st = shipTree();
}

Ship ** Port::findBestFitShip(const Cargo & cargo) {
  return st.findBestFit(cargo.getWeight());
}

// Function to print summary of Ships
void Port::printAllShips() {
  std::cout << "---Done Loading---Here are the ships---\n";
  for (size_t i = 0; i < ships.size(); ++i) {
    ships[i]->printDetails();
  }
}

// Cleanup function
void Port::cleanupShips() {
  for (size_t i = 0; i < ships.size(); ++i) {
    delete ships[i];
  }
  ships.clear();
}
