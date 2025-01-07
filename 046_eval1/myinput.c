#include "myinput.h"

#include <stdio.h>

void parse_planet_info(planet_t * planet, char * line) {
  //STEP 1: Write this

  // Handle NULL pointer
  if (line == NULL) {
    fprintf(stderr, "Could not read line\n");
    exit(EXIT_FAILURE);
  }
  //Set temp for init position in degrees
  double init_pos_deg;
  //Set a buffer to check extra input
  char ext_input[2] = "\0";

  //Parse the input string
  if (sscanf(line,
             "%31[^:]:%lf:%lf:%lf%1s",
             planet->name,
             &planet->orbital_radius,
             &planet->year_len,
             &init_pos_deg,
             ext_input) != 4) {
    fprintf(stderr, "Error: Invalid input in line: %s\n", line);
    exit(EXIT_FAILURE);
  }

  //Check if extra input was given
  if (*ext_input != '\0') {
    fprintf(stderr, "Error: Too many inputs in line: %s\n", line);
    exit(EXIT_FAILURE);
  }

  //Convert initial position from degrees to radians
  planet->init_pos = (init_pos_deg) * (M_PI / 180);
}
