#ifndef __SHIP_H__
#define __SHIP_H__

#include <stdint.h>

#include <stdexcept>
#include <vector>

#include "cargo.hpp"

// Exception Class to handle input parsing
class ShipParsingException : public std::exception {
  std::string message;

 public:
  ShipParsingException(const std::string & shipName, const std::string & errorDetail) :
      message("Parse Error for ship \"" + shipName + "\": " + errorDetail) {}
  virtual const char * what() const throw() { return message.c_str(); }
  virtual ~ShipParsingException() throw() {}
};

class Ship {
 protected:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t capacity;
  uint64_t used_capacity;
  std::vector<Cargo> loaded_cargo;

 public:
  Ship(const std::string & name,
       const std::string & source,
       const std::string & destination,
       uint64_t capacity) :
      name(name),
      source(source),
      destination(destination),
      capacity(capacity),
      used_capacity(0) {}

  static Ship * createShip(const std::string & line);

  virtual ~Ship() {}
  virtual Ship * copy() const = 0;
  virtual bool canCarry(const Cargo & cargo) const = 0;
  virtual void loadCargo(const Cargo & cargo) = 0;
  virtual void printDetails() const = 0;

  std::string getName() const { return name; }
  std::string getSource() const { return source; }
  std::string getDestination() const { return destination; }
  uint64_t getCapacity() const { return capacity; }
  uint64_t getRemainingCapacity() const { return capacity - used_capacity; }
  // static bool compareShipsByName(Ship * a, Ship * b) {
  //  return a->getName() < b->getName();
  // }
  struct compareShipsByName {
    bool operator()(Ship * a, Ship * b) const { return a->getName() < b->getName(); }
  };
};

#endif
