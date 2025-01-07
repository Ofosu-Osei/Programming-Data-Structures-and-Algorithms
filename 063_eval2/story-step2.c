#include <assert.h>
#include <stdio.h>

#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <word_file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  //Read words file
  catarray_t * catArray = readCWs(argv[1]);

  // Print category array
  printWords(catArray);

  // Free allocated memory
  freeCatArray(catArray);

  return EXIT_SUCCESS;
}
