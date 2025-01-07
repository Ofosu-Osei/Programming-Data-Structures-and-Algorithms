#include <assert.h>
#include <stdio.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <word_file> <story_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Get categories and words input file
  catarray_t * categories = readCWs(argv[1]);

  FILE * input_story = fopen(argv[2], "r");
  if (input_story == NULL) {
    perror("Error opening story file");
    return EXIT_FAILURE;
  }

  // Make  story for step3
  makeStory(input_story, categories, 0);

  assert(fclose(input_story) == 0);
  freeCatArray(categories);

  return EXIT_SUCCESS;
}
