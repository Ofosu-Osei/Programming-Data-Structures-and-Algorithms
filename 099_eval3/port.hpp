#ifndef __PORT_H__
#define __PORT_H__
#include <stdint.h>

#include <map>
#include <vector>

#include "avlmultimap03.hpp"
#include "cargo.hpp"
#include "ship.hpp"

typedef AVLMultiMap<uint64_t, Ship *, std::less<uint64_t>, Ship::compareShipsByName>
    shipTree;
class Port {
 private:
  std::vector<Ship *> ships;
  shipTree st;

 public:
  Port();
  ~Port();                             // Destructor
  Port(const Port & rhs);              // Copy constructor
  Port & operator=(const Port & rhs);  // Copy assignment operator
  void swap(Port & rhs);

  void addShip(Ship * ship);
  void addToShipTree(uint64_t remainingCapacity, Ship * ship);
  void resetShipTree();
  void parseShipsFromFile(const std::string & filename);
  std::map<std::string, unsigned long> computeCapacities() const;
  void printRouteCapacity(const std::map<std::string, unsigned long> & route_tot_cap);
  std::vector<Cargo> parseCargoFromFile(const std::string & filename);
  std::vector<Ship *> findEligibleShips(const Cargo & cargo);
  Ship * findShipByName(const std::string & name);
  Ship ** findBestFitShip(const Cargo & cargo);
  void printAllShips();
  const std::vector<Ship *> & getShips() const { return ships; }
  void cleanupShips();
};
#endif
