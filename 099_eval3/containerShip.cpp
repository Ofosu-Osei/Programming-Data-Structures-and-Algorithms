
#include "containerShip.hpp"

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "ship.hpp"

// Constructor for ContainerShip
ContainerShip::ContainerShip(const std::string & name,
                             const std::string & source,
                             const std::string & destination,
                             uint64_t capacity,
                             const std::string & line) :
    Ship(name, source, destination, capacity), slots(0), used_slots(0) {
  std::istringstream iss(line);
  std::string token;

  // Parse type_info for slots and hazardous material capabilities
  std::getline(iss, token, ',');

  iss >> slots;
  if (iss.fail()) {
    throw ShipParsingException(name, "Invalid or missing slots value.");
  }

  while (std::getline(iss, token, ',')) {
    hazmat_rules.insert(token);
  }
}

// Implementation of pure virtual methods
Ship * ContainerShip::copy() const {
  return new ContainerShip(*this);
}

bool ContainerShip::canCarry(const Cargo & cargo) const {
  // Check route
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  // Ensure cargo has a container property
  if (!cargo.hasProperty("container")) {
    return false;
  }

  // Check for enough capacity and slots
  if (used_capacity + cargo.getWeight() > capacity || used_slots >= slots) {
    return false;
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

  return true;
}

void ContainerShip::loadCargo(const Cargo & cargo) {
  if (!canCarry(cargo)) {
    throw std::runtime_error("Cargo (" + cargo.getName() +
                             ")  cannot be loaded onto ship: " + name);
  }
  used_capacity += cargo.getWeight();
  used_slots += 1;
  loaded_cargo.push_back(cargo);
}

void ContainerShip::printDetails() const {
  std::cout << "The Container Ship " << name << "(" << used_capacity << "/" << capacity
            << ") is carrying : \n";
  // Print loaded cargo
  for (size_t i = 0; i < loaded_cargo.size(); ++i) {
    std::cout << "  " << loaded_cargo[i].getName() << "(" << loaded_cargo[i].getWeight()
              << ")\n";
  }
  std::cout << "  (" << slots - used_slots << ")"
            << " slots remain\n";
}
