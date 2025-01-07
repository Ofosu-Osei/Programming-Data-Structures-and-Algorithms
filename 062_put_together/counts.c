#include "counts.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * wordCount = malloc(sizeof(*wordCount));
  wordCount->wordStrings = NULL;
  wordCount->length = 0;
  wordCount->unknown = 0;

  return wordCount;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown++;
    return;
  }

  for (int i = 0; i < c->length; i++) {
    if (strcmp(c->wordStrings[i].wordString, name) == 0) {
      c->wordStrings[i].timesSeen++;
      return;
    }
  }

  c->wordStrings = realloc(c->wordStrings, (c->length + 1) * sizeof(*c->wordStrings));
  assert(c->wordStrings != NULL);
  c->wordStrings[c->length].wordString = strdup(name);
  c->wordStrings[c->length].timesSeen = 1;
  c->length++;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    fprintf(
        outFile, "%s: %d\n", c->wordStrings[i].wordString, c->wordStrings[i].timesSeen);
  }

  if (c->unknown > 0) {
    fprintf(outFile, "%s: %d\n", "<unknown>", c->unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->length; i++) {
    free(c->wordStrings[i].wordString);
  }
  free(c->wordStrings);
  free(c);
}
