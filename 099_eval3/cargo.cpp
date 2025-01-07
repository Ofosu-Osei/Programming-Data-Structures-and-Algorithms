#include "cargo.hpp"

#include <set>
#include <sstream>
#include <stdexcept>
#include <string>

Cargo::Cargo(const std::string & line) :
    name(), source(), destination(), weight(0), properties() {
  std::istringstream iss(line);
  std::getline(iss, name, ',');
  if (name.empty()) {
    throw std::runtime_error("Invalid or missing cargo name");
  }

  std::getline(iss, source, ',');
  if (source.empty()) {
    throw std::runtime_error("Invalid or missing source location");
  }

  std::getline(iss, destination, ',');
  if (destination.empty()) {
    throw std::runtime_error("Invalid or missing destination location");
  }

  iss >> weight;
  if (iss.fail() || weight <= 0) {
    throw std::runtime_error("Invalid cargo weight");
  }

  std::string prop;
  while (std::getline(iss, prop, ',')) {
    properties.insert(prop);
  }
}

// Cargo method to confirm if Cargo has a specific property
bool Cargo::hasProperty(const std::string & property) const {
  return properties.find(property) != properties.end();
}

// Cargo method to get value from properties using key
int Cargo::getPropertyValue(const std::string & key) const {
  for (std::set<std::string>::const_iterator it = properties.begin();
       it != properties.end();
       ++it) {
    size_t pos = it->find('=');
    // Check for matches
    if (pos != std::string::npos) {
      std::string prop_key = it->substr(0, pos);

      if (prop_key == key) {
        std::istringstream value_stream(it->substr(pos + 1));
        int found_value = 0;

        if (value_stream >> found_value) {
          return found_value;
        }
      }
    }
    // Key without value
    else if (*it == key) {
      return 0;
    }
  }
  // If the property is not found
  throw std::string("Property '" + key + "' not found in" + name + " properties.");
}
