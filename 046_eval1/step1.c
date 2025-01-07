#include <stdio.h>
#include <stdlib.h>

#include "provided.h"

//we are providing main: it uses
//several things you won't learn about
//until later chapters.
//you should NOT need to modify this
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: \nlaunch-step1 planetfile\n");
    return EXIT_FAILURE;
  }
  planet_list_t * planets = read_planets(argv[1]);
  for (size_t i = 0; i < planets->num_planets; i++) {
    print_planet_data(planets->planets[i]);
  }
  free_planets(planets);
  return EXIT_SUCCESS;
}
