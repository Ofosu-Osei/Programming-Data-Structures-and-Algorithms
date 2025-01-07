#ifndef __CONTAINERSHIP_H__
#define __CONTAINERSHIP_H__

#include <vector>

#include "ship.hpp"

class ContainerShip : public Ship {
 private:
  unsigned int slots;
  unsigned int used_slots;
  std::set<std::string> hazmat_rules;

 public:
  ContainerShip(const std::string & name,
                const std::string & source,
                const std::string & destination,
                uint64_t capacity,
                const std::string & line);
  Ship * copy() const;
  bool canCarry(const Cargo & cargo) const;
  void loadCargo(const Cargo & cargo);
  void printDetails() const;
};

#endif
