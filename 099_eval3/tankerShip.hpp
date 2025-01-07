#ifndef __TANKER_SHIP_H__
#define __TANKER_SHIP_H__

#include <map>
#include <set>
#include <vector>

#include "ship.hpp"

class TankerShip : public Ship {
  int min_temp;
  int max_temp;
  unsigned int num_tanks;
  unsigned long cap_per_tank;
  std::set<std::string> hazmat_rules;
  std::vector<std::map<std::string, unsigned long> > tank_usage_info;
  unsigned int getNumLoadedTanks() const;

 public:
  TankerShip(const std::string & name,
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
