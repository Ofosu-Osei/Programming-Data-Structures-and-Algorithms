#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "port.hpp"
#include "ship.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <ships_file> <cargo_file>" << std::endl;
    return EXIT_FAILURE;
  }

  std::string shipsFile = argv[1];
  std::string cargoFile = argv[2];
  try {
    Port port;
    port.parseShipsFromFile(shipsFile);
    std::vector<Cargo> cargos = port.parseCargoFromFile(cargoFile);

    // Sort cargo
    std::stable_sort(cargos.begin(), cargos.end(), Cargo::compareCargoByWeight());

    for (size_t i = 0; i < cargos.size(); ++i) {
      Cargo & cargo = cargos[i];
      std::vector<Ship *> eligibleShips = port.findEligibleShips(cargo);

      if (eligibleShips.empty()) {
        std::cout << "No ships can carry the " << cargo.getName() << " from "
                  << cargo.getSource() << " to " << cargo.getDestination() << "\n";
        continue;
      }

      // Port::shipTree st;
      port.resetShipTree();
      for (size_t i = 0; i < eligibleShips.size(); ++i) {
        port.addToShipTree(eligibleShips[i]->getRemainingCapacity(), eligibleShips[i]);
      }

      Ship ** best_fit_ship = port.findBestFitShip(cargo);

      if (best_fit_ship != NULL && *best_fit_ship != NULL) {
        std::string ship_name = (*best_fit_ship)->getName();
        Ship * ship_to_load = port.findShipByName(ship_name);

        ship_to_load->loadCargo(cargo);

        std::cout << "Loading " << cargo.getName() << " onto " << ship_to_load->getName()
                  << " from " << cargo.getSource() << " to " << cargo.getDestination()
                  << " " << ship_to_load->getRemainingCapacity() << " capacity remains"
                  << std::endl;
      }
      else {
        std::cout << "Cannot load " << cargo.getName() << " onto any ship" << std::endl;
      }
    }

    port.printAllShips();
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
