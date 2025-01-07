#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "planet_util.h"
#include "provided.h"
#include "target.h"

//we are providing main: it uses
//several things you won't learn about
//until later chapters.
//you should NOT need to modify this
int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: \nlaunch-step3 planetfile launchfile\n");
    return EXIT_FAILURE;
  }

  planet_list_t * planets = read_planets(argv[1]);
  launch_list_t * launches = read_launches(argv[2]);
  for (size_t i = 0; i < launches->num_launches; i++) {
    launch_input_t * this_launch = launches->launches[i];
    launch_result_t result = compute_launch_by_info(this_launch, planets);
    report_launch_results(planets, this_launch, result);
  }
  free_planets(planets);
  free_launches(launches);
  return EXIT_SUCCESS;
}
