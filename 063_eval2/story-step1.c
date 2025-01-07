#include <assert.h>
#include <stdio.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <story file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE * input_story = fopen(argv[1], "r");
  if (input_story == NULL) {
    perror("Failed to open story file");
    return EXIT_FAILURE;
  }

  // Activate  step 1 mode
  isStep1Mode = 1;
  // Create default categories
  catarray_t * categories = readCWs(NULL);
  // Make story for step1
  makeStory(input_story, categories, 0);

  assert(fclose(input_story) == 0);
  freeCatArray(categories);

  return EXIT_SUCCESS;
}
