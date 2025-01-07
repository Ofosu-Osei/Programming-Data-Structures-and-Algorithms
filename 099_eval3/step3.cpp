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
    std::cerr << "Usage: " << argv[0] << " <ships file> <cargo file>\n";
    return EXIT_FAILURE;
  }

  try {
    Port port;
    // Parse the input files for ship and cargo
    port.parseShipsFromFile(argv[1]);
    std::vector<Cargo> cargoList = port.parseCargoFromFile(argv[2]);

    for (size_t i = 0; i < cargoList.size(); ++i) {
      const Cargo & cargo = cargoList[i];
      std::vector<Ship *> eligibleShips = port.findEligibleShips(cargo);

      // Print eligible ships
      if (eligibleShips.empty()) {
        std::cout << "No ships can carry the " << cargo.getName() << " from "
                  << cargo.getSource() << " to " << cargo.getDestination() << "\n";
      }
      else {
        std::cout << eligibleShips.size() << " ships can carry the " << cargo.getName()
                  << " from " << cargo.getSource() << " to " << cargo.getDestination()
                  << "\n";

        for (size_t j = 0; j < eligibleShips.size(); ++j) {
          std::cout << "  " << eligibleShips[j]->getName() << "\n";
        }

        // Load cargo onto the first eligible ship
        eligibleShips[0]->loadCargo(cargo);

        std::cout << "  **Loading the cargo onto " << eligibleShips[0]->getName()
                  << "**\n";
      }
    }

    // Print summary of ships and their cargo
    port.printAllShips();
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
