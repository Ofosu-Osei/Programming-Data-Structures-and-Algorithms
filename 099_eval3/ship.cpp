#include "ship.hpp"

#include <sstream>
#include <stdexcept>

#include "animalShip.hpp"
#include "containerShip.hpp"
#include "tankerShip.hpp"

// Definition of createShip function
Ship * Ship::createShip(const std::string & line) {
  std::istringstream iss(line);
  std::string ship_name, type_info, source, destination;
  unsigned long capacity;

  // Parse ship name
  std::getline(iss, ship_name, ':');
  if (ship_name.empty()) {
    throw ShipParsingException("Unknown", "Missing ship name.");
  }

  // Parse the type information
  std::getline(iss, type_info, ':');
  if (type_info.empty()) {
    throw ShipParsingException(ship_name, "Missing type information.");
  }

  // Parse source, destination, and capacity (common fields)
  std::getline(iss, source, ':');
  if (source.empty()) {
    throw ShipParsingException(ship_name, "Missing source.");
  }

  std::getline(iss, destination, ':');
  if (destination.empty()) {
    throw ShipParsingException(ship_name, "Missing destination.");
  }
  if (!(iss >> capacity)) {
    throw ShipParsingException(ship_name, "Invalid or missing capacity.");
  }

  // Create specific ship types
  if (type_info.find("Container") == 0) {
    return new ContainerShip(ship_name, source, destination, capacity, type_info);
  }
  else if (type_info.find("Tanker") == 0) {
    return new TankerShip(ship_name, source, destination, capacity, type_info);
  }
  else if (type_info.find("Animals") == 0) {
    return new AnimalShip(ship_name, source, destination, capacity, type_info);
  }

  throw ShipParsingException("Unknown", "Unsupported ship type: " + type_info);
}
