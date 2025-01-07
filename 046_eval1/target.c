#include "target.h"

#include <stdio.h>

//Helper function to normalize  angle
static double normalize_angle(double angle) {
  while (angle < 0) {
    angle += 2 * M_PI;
  }
  while (angle >= 2 * M_PI) {
    angle -= 2 * M_PI;
  }

  return angle;
}

//Helper Function to compute distance between two planets
double compute_distance(point_t src_loc, point_t dest_loc) {
  double distance;
  //Get the distance between planets
  double d_x = dest_loc.x - src_loc.x;
  double d_y = dest_loc.y - src_loc.y;

  return distance = sqrt((d_x * d_x) + (d_y * d_y));
}
//Helper Function to configure source and destination planets info
int get_src_and_dest_info(const launch_input_t * this_launch,
                          const planet_list_t * planets,
                          planet_t ** src_planet,
                          planet_t ** dest_planet,
                          point_t * src_loc,
                          point_t * dest_loc) {
  //Get source and destination planets
  *src_planet = find_planet(planets, this_launch->src);
  *dest_planet = find_planet(planets, this_launch->dest);

  if (*src_planet == NULL || *dest_planet == NULL) {
    return -1;
  }

  //Get the locations of both planets at launch-time
  *src_loc = get_location_at(*src_planet, this_launch->time);
  *dest_loc = get_location_at(*dest_planet, this_launch->time);

  return 0;
}

launch_result_t compute_launch(const launch_input_t * this_launch,
                               point_t src_loc,
                               point_t dest_loc) {
  launch_result_t launch_by_info;

  //Get distance between planets
  double distance = compute_distance(src_loc, dest_loc);

  //Get duration of trip
  launch_by_info.duration = distance / this_launch->speed;

  //Get launch angle
  // Compute the angle to launch the ship
  double angle = atan2(dest_loc.y - src_loc.y, dest_loc.x - src_loc.x);

  launch_by_info.theta = normalize_angle(angle);

  return launch_by_info;
}

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets) {
  //STEP 3: Write this
  planet_t * src_planet;
  planet_t * dest_planet;
  point_t src_loc;
  point_t dest_loc;

  //Configure source and destination planets info
  if (get_src_and_dest_info(
          this_launch, planets, &src_planet, &dest_planet, &src_loc, &dest_loc) == -1) {
    fprintf(stderr, "Error: Source or Destination planet not found\n");
    exit(EXIT_FAILURE);
  }

  return compute_launch(this_launch, src_loc, dest_loc);
}

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time) {
  //STEP 3: Write this

  // Get target angle from position
  double target_angle = normalize_angle(atan2(pos.y, pos.x));

  // Set angular velocity of the planet (radians per hour)
  double ang_vel = 2 * M_PI / planet->year_len;

  // Set the current angle of planet at start time
  double curr_angle = planet->init_pos + ang_vel * start_time;
  //Keep the current angle in the desired range
  curr_angle = normalize_angle(curr_angle);

  // Get distance between current angle and target angle
  double ang_diff = normalize_angle(target_angle - curr_angle);

  // Get time to reach target angle
  double time_to_target = ang_diff / ang_vel;

  return start_time + time_to_target;
}
