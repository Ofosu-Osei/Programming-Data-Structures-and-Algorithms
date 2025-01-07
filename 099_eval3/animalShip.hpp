#ifndef __ANIMAL_SHIP_H__
#define __ANIMAL_SHIP_H__

#include "ship.hpp"

class AnimalShip : public Ship {
 private:
  unsigned int small_enough;
  bool has_roamer;

 public:
  AnimalShip(const std::string & name,
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
