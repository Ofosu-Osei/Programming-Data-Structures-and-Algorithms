#ifndef PLANET_TARGET_H
#define PLANET_TARGET_H
#include <math.h>
#include <stdint.h>

#include "planet_util.h"
#include "provided.h"

launch_result_t compute_launch_by_info(const launch_input_t * this_launch,
                                       const planet_list_t * planets);

double when_does_planet_return_to(const planet_t * planet,
                                  point_t pos,
                                  double start_time);
#endif
