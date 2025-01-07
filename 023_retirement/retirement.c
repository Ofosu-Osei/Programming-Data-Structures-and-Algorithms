#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

//Function to calculate and print balance
double calcBalance(double balance, double rate, double contribution, int age) {
  printf("Age %3d month %2d you have $%.2f\n", age / 12, age % 12, balance);
  return balance * (1 + rate) + contribution;
}

//Function to process retirement phase
void processing_phase(int * age, double * balance, retire_info phase) {
  for (int i = 0; i < phase.months; i++) {
    *balance = calcBalance(
        *balance, phase.rate_of_return, phase.contribution, *age);  //update balance
    (*age)++;                                                       //update age
  }
}

//Function to calculate retirement plan
void retirement(int startAge,           //in months
                double initial,         //initial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired

  double balance = initial;
  int age = startAge;

  //process working phase
  processing_phase(&age, &balance, working);

  // process retired phase
  processing_phase(&age, &balance, retired);
}

int main(void) {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
