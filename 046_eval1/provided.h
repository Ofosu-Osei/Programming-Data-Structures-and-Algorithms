#ifndef PLANET_IO_H
#define PLANET_IO_H
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_PLANET_NAME_LEN 32
struct planet_tag {
  char name[MAX_PLANET_NAME_LEN];
  double orbital_radius;  //in km
  double year_len;        //in hours
  double init_pos;        //in radians
};

typedef struct planet_tag planet_t;

struct planet_list_tag {
  planet_t ** planets;
  size_t num_planets;
};
typedef struct planet_list_tag planet_list_t;
struct launch_input_tag {
  double time;              //the time in hours of when this launch happens
  char * src;               //name of the source planet
  char * dest;              //name of the destination planet
  double speed;             //the speed of this ship (km/hr)
  uint64_t max_iterations;  //(Step 4) how many steps do we try
  double close_enough;      //(Step 4) distance we consider success
};
typedef struct launch_input_tag launch_input_t;

struct launch_list_tag {
  launch_input_t ** launches;
  size_t num_launches;
};

typedef struct launch_list_tag launch_list_t;
struct point_tag {
  double x;
  double y;
};
typedef struct point_tag point_t;
struct launch_result_tag {
  double theta;     //angle to launch from src planet
  double duration;  //how many hours is flight
};

typedef struct launch_result_tag launch_result_t;

double rad_to_deg(double rad);

planet_list_t * read_planets(const char * fname);
void print_planet_data(planet_t * p);
void print_planet_at(planet_t * p, double time);
void print_all(planet_list_t * list, double time);
void free_planets(planet_list_t * list);
launch_list_t * read_launches(const char * filename);
void free_launches(launch_list_t * launches);
void report_launch_results(planet_list_t * planets,
                           launch_input_t * this_launch,
                           launch_result_t result);
#endif
