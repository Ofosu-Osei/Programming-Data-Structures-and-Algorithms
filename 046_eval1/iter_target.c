#include "iter_target.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

launch_result_t solve_launch(const launch_input_t * this_launch,
                             const planet_list_t * planets) {
  //STEP 4: write this function
  launch_result_t best_launch_info, current_launch_info;
  double flight_time, waiting_time, total_time, min_total_time = INFINITY;

  planet_t *src_planet, *dest_planet;
  point_t src_loc, projected_dest_loc, original_dest_loc;

  // Get the source and destination planets info
  if (get_src_and_dest_info(this_launch,
                            planets,
                            &src_planet,
                            &dest_planet,
                            &src_loc,
                            &original_dest_loc) == -1) {
    fprintf(stderr, "Error: Source or Destination planet not found\n");
    exit(EXIT_FAILURE);
  }
  // Set original destination location as  inital projected destination
  projected_dest_loc = original_dest_loc;

  // Iterative refinement loop
  for (size_t i = 0; i < this_launch->max_iterations; i++) {
    // Compute launch based on the current destination location
    current_launch_info = compute_launch(this_launch, src_loc, projected_dest_loc);
    flight_time = current_launch_info.duration;

    // Recalculate the new projected destination location after flight time
    projected_dest_loc = get_location_at(dest_planet, this_launch->time + flight_time);

    // Check if we are close enough to the destination planet
    if (this_launch->close_enough >=
        compute_distance(original_dest_loc, projected_dest_loc)) {
      // No need to wait if we're close enough
      total_time = flight_time;
    }
    else {
      // Get when the destination planet will return to the projected location
      double planet_return_time =
          when_does_planet_return_to(dest_planet, projected_dest_loc, flight_time);
      waiting_time = planet_return_time - flight_time - this_launch->time;

      total_time = flight_time + waiting_time;
    }

    // Check if this is the best solution so far
    if (total_time < min_total_time) {
      min_total_time = total_time;
      best_launch_info = current_launch_info;
      best_launch_info.duration = total_time;
    }

    // If the solution is good enough (no waiting needed), break the loop
    if (waiting_time == 0) {
      break;
    }
  }

  return best_launch_info;
}
