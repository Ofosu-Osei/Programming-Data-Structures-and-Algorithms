#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "planet_util.h"
#include "provided.h"

//this will let qsort sort the strings.  its
//what is in AoP ch10.  You don't need to do anything with it.
int compare_strings(const void * s1vp, const void * s2vp) {
  const char * const * s1ptr = s1vp;
  const char * const * s2ptr = s2vp;
  return strcmp(*s1ptr, *s2ptr);
}

//we are providing main: it uses
//several things you won't learn about
//until later chapters.
//you should NOT need to modify this
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: \nlaunch-step2 planetfile\n");
    return EXIT_FAILURE;
  }

  planet_list_t * planets = read_planets(argv[1]);
  char ** pnames = malloc(planets->num_planets * sizeof(*pnames));
  for (size_t i = 0; i < planets->num_planets; i++) {
    pnames[i] = strdup(planets->planets[i]->name);
  }
  qsort(pnames, planets->num_planets, sizeof(*pnames), compare_strings);
  for (double curr_time = 0; curr_time < 1000; curr_time += 100) {
    for (size_t i = 0; i < planets->num_planets; i++) {
      planet_t * curr_planet = find_planet(planets, pnames[i]);
      print_planet_at(curr_planet, curr_time);
    }
  }
  for (size_t i = 0; i < planets->num_planets; i++) {
    free(pnames[i]);
  }
  free(pnames);
  free_planets(planets);
  return EXIT_SUCCESS;
}
