#include "animalShip.hpp"

#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

#include "ship.hpp"

// Constructor for AnimalShip
AnimalShip::AnimalShip(const std::string & name,
                       const std::string & source,
                       const std::string & destination,
                       uint64_t capacity,
                       const std::string & line) :
    Ship(name, source, destination, capacity), has_roamer(false) {
  std::istringstream iss(line);
  std::string type;
  std::getline(iss, type, ',');

  iss >> small_enough;
  if (iss.fail()) {
    throw ShipParsingException(name, "Invalid small enough threshold.");
  }
}

// Implementation of pure virtual methods
Ship * AnimalShip::copy() const {
  return new AnimalShip(*this);
}

bool AnimalShip::canCarry(const Cargo & cargo) const {
  // Check route
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  // Handle animal cargo
  if (cargo.hasProperty("animal")) {
    if (cargo.hasProperty("roamer")) {
      // Check if no other roamer is loaded
      if (has_roamer) {
        return false;
      }
    }
    // return true if cargo is an animall and other checks pass
    return (used_capacity + cargo.getWeight() <= capacity);
  }

  // Handle non-animal cargo
  // And must not be liquid or gas
  if (cargo.hasProperty("liquid") || cargo.hasProperty("gas")) {
    return false;
  }

  for (std::set<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      return false;
    }
  }
  // Check threshold compliance
  if (cargo.getWeight() > small_enough) {
    return false;
  }

  // Check remaining capacity
  return used_capacity + cargo.getWeight() <= capacity;
}

void AnimalShip::loadCargo(const Cargo & cargo) {
  if (!canCarry(cargo)) {
    throw std::runtime_error("Cargo (" + cargo.getName() +
                             ") cannot be loaded onto ship: " + name);
  }

  // Update state of Ship
  used_capacity += cargo.getWeight();
  loaded_cargo.push_back(cargo);

  // Check and set roamer flag
  if (cargo.hasProperty("roamer")) {
    has_roamer = true;
  }
}

void AnimalShip::printDetails() const {
  std::cout << "The Animals Ship " << name << "(" << used_capacity << "/" << capacity
            << ") is carrying : \n";
  for (size_t i = 0; i < loaded_cargo.size(); ++i) {
    std::cout << "  " << loaded_cargo[i].getName() << "(" << loaded_cargo[i].getWeight()
              << ")\n";
  }
  if (has_roamer) {
    std::cout << "  has a roamer\n";
  }
  else {
    std::cout << "  does not have a roamer\n";
  }
}
