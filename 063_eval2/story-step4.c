#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char * argv[]) {
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "Usage: %s [-n] <words_file> <story_file>\n", argv[0]);
    return EXIT_FAILURE;
  }
  int reused_word_flag = 0;
  int ind_words = 1;
  int ind_story = 2;

  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      fprintf(stderr,
              "Reused Word Flag Error: Reused word option flag unknown %s\n",
              argv[1]);
    }
    else {
      reused_word_flag = 1;
      ind_words = 2;
      ind_story = 3;
    }
  }

  // Get categories and words input file
  catarray_t * categories = readCWs(argv[ind_words]);

  FILE * input_story = fopen(argv[ind_story], "r");
  if (input_story == NULL) {
    perror("Error opening story file");
    return EXIT_FAILURE;
  }

  // Make story for step4
  makeStory(input_story, categories, reused_word_flag);

  assert(fclose(input_story) == 0);
  freeCatArray(categories);

  return EXIT_SUCCESS;
}
