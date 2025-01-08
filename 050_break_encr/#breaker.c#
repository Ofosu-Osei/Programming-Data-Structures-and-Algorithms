#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_LETTERS 26

int findMostFreqLetter(int * freq) {
  int maxIndex = 0;

  for (int i = 1; i < NUM_LETTERS; i++) {
    if (freq[i] > freq[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

int countFreq(FILE * f, int (*findMostFreqLetter)(int *)) {
  int c;
  int freq[NUM_LETTERS] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c) - 'a';
      freq[c]++;
    }
  }
  return findMostFreqLetter(freq);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <encrypted_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Failed to open file");
    return EXIT_FAILURE;
  }

  int mostFregLetter = countFreq(f, findMostFreqLetter);

  // Calculate the key using the formula
  int key = (mostFregLetter - ('e' - 'a') + NUM_LETTERS) % NUM_LETTERS;

  printf("%d\n", key);

  if (fclose(f) != 0) {
    perror("Failed to close file");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
