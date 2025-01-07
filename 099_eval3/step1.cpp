#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "port.hpp"
#include "ship.hpp"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input file>\n";
    return EXIT_FAILURE;
  }
  try {
    Port port;
    // Parse the input file
    port.parseShipsFromFile(argv[1]);

    // Print computed route capacities
    port.printRouteCapacity(port.computeCapacities());
  }
  catch (const ShipParsingException & e) {
    std::cerr << "Input Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
