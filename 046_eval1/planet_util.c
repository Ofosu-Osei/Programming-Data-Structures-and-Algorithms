#include "planet_util.h"

#include <stdio.h>
#include <string.h>

#include "provided.h"

point_t get_location_at(const planet_t * p, double time) {
  // Step 2: WRITE THIS
  point_t location;
  //Set angle for planet in its orbit
  double angle = p->init_pos + 2 * M_PI * (time / p->year_len);
  //Keep the angle in the desired range
  angle = fmod(angle, 2 * M_PI);

  //Get the location of the planet
  location.x = p->orbital_radius * cos(angle);
  location.y = p->orbital_radius * sin(angle);

  return location;
}

planet_t * find_planet(const planet_list_t * lst, const char * name) {
  //Step 2: WRITE THIS
  if (lst == NULL || name == NULL || *name == '\0') {
    fprintf(stderr, "Error: Invalid input(s)\n");
    exit(EXIT_FAILURE);
  }
  // Iterate the list of planetsand compare names to find planet
  for (size_t i = 0; i < lst->num_planets; i++) {
    if (strncmp(lst->planets[i]->name, name, 31) == 0) {
      return lst->planets[i];
    }
  }
  return NULL;
}
