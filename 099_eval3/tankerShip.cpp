#include "tankerShip.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"

TankerShip::TankerShip(const std::string & name,
                       const std::string & source,
                       const std::string & destination,
                       uint64_t capacity,
                       const std::string & line) :
    Ship(name, source, destination, capacity), min_temp(0), max_temp(0), num_tanks(0) {
  std::istringstream iss(line);
  std::string token;
  std::getline(iss, token, ',');

  std::getline(iss, token, ',');
  std::istringstream(token) >> min_temp;

  std::getline(iss, token, ',');
  std::istringstream(token) >> max_temp;

  std::getline(iss, token, ',');
  std::istringstream(token) >> num_tanks;

  if (num_tanks == 0) {
    throw ShipParsingException(name, "Number of tanks must be greater than zero.");
  }

  if (capacity % num_tanks != 0) {
    throw ShipParsingException(name,
                               "Total capacity must be a multiple of number of tanks.");
  }
  cap_per_tank = capacity / num_tanks;
  tank_usage_info.resize(num_tanks);
  for (size_t i = 0; i < tank_usage_info.size(); ++i) {
    tank_usage_info[i] = std::map<std::string, unsigned long>();
  }

  while (std::getline(iss, token, ',')) {
    hazmat_rules.insert(token);
  }
}

// Implementation of pure virtual functions
Ship * TankerShip::copy() const {
  return new TankerShip(*this);
}

bool TankerShip::canCarry(const Cargo & cargo) const {
  // Check route
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  // Ensure  cargo is either liquid or gas
  if (!cargo.hasProperty("liquid") && !cargo.hasProperty("gas")) {
    return false;
  }

  // Chaeck for enough capacity and tanks
  if (used_capacity + cargo.getWeight() > capacity) {
    return false;
  }

  // Check if temp range falls within ship's requirements
  try {
    int min_req = cargo.getPropertyValue("mintemp");
    if (min_req > max_temp) {
      return false;
    }
  }
  catch (const std::string & e) {
    // Do nothing here
  }

  try {
    int max_req = cargo.getPropertyValue("maxtemp");
    if (max_req < min_temp) {
      return false;
    }
  }
  catch (const std::string & e) {
    // Do nothing here
  }

  // Filter hazardous material properties from cargo properties
  std::set<std::string> cargo_hazmat;
  for (std::set<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      cargo_hazmat.insert(it->substr(10));
    }
  }

  // Check cargo for hazmat rules compliance
  if (!std::includes(hazmat_rules.begin(),
                     hazmat_rules.end(),
                     cargo_hazmat.begin(),
                     cargo_hazmat.end())) {
    return false;
  }

  unsigned long weight_left = cargo.getWeight();
  for (size_t i = 0; i < tank_usage_info.size() && weight_left > 0; ++i) {
    if (tank_usage_info[i].empty() || tank_usage_info[i].count(cargo.getName())) {
      unsigned long tank_cap_left =
          cap_per_tank -
          (tank_usage_info[i].empty() ? 0 : tank_usage_info[i].at(cargo.getName()));
      weight_left -= std::min(weight_left, tank_cap_left);
    }
  }

  return weight_left == 0;

  return true;
}

void TankerShip::loadCargo(const Cargo & cargo) {
  if (!canCarry(cargo)) {
    throw std::runtime_error("Cargo (" + cargo.getName() +
                             ") cannot be loaded onto ship: " + name);
  }

  unsigned long weight_left = cargo.getWeight();

  for (size_t i = 0; i < tank_usage_info.size() && weight_left > 0; ++i) {
    std::map<std::string, unsigned long>::iterator it = tank_usage_info[i].begin();

    // Fill partially filled tanks of the same cargo type
    if (tank_usage_info[i].count(cargo.getName()) > 0 &&
        tank_usage_info[i].at(cargo.getName()) < cap_per_tank) {
      unsigned long tank_cap_left = cap_per_tank - it->second;
      unsigned long weight_loaded = std::min(weight_left, tank_cap_left);
      it->second += weight_loaded;
      weight_left -= weight_loaded;
      used_capacity += weight_loaded;
    }
    // Allocate new tanks for remaining weight
    else if (tank_usage_info[i].empty()) {
      unsigned long weight_loaded = std::min(weight_left, cap_per_tank);
      tank_usage_info[i][cargo.getName()] = weight_loaded;
      weight_left -= weight_loaded;
      used_capacity += weight_loaded;
    }
  }

  loaded_cargo.push_back(cargo);
}

unsigned int TankerShip::getNumLoadedTanks() const {
  unsigned int count = 0;
  for (size_t i = 0; i < tank_usage_info.size(); ++i) {
    if (!tank_usage_info[i].empty()) {
      count++;
    }
  }
  return count;
}

void TankerShip::printDetails() const {
  std::cout << "The Tanker Ship " << name << "(" << used_capacity << "/" << capacity
            << ") is carrying : \n";

  for (size_t i = 0; i < loaded_cargo.size(); ++i) {
    std::cout << "  " << loaded_cargo[i].getName() << "(" << loaded_cargo[i].getWeight()
              << ")\n";
  }
  std::cout << "  " << getNumLoadedTanks() << " / " << num_tanks << " tanks used\n";
}
