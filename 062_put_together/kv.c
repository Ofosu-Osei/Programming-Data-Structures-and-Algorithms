#include "kv.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static kvpair_t getKVLine(const char * line) {
  kvpair_t pair;
  // Get the position of first occurrence '=' in line
  char * delimeter = strchr(line, '=');

  if (delimeter == NULL) {
    fprintf(stderr, "Error: Invalid input format: %s", line);
    exit(EXIT_FAILURE);
  }
  // Extract key value pair from line
  pair.key = strndup(line, delimeter - line);
  pair.value = strdup(delimeter + 1);

  // Check for new line at the end of value
  char * newline = strchr(pair.value, '\n');
  if (newline != NULL) {
    *newline = '\0';
  }
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL;
  }

  kvarray_t * results = malloc(sizeof(*results));
  results->kvpairs = NULL;
  results->length = 0;
  char * line = NULL;
  size_t sz = 0;

  while (getline(&line, &sz, f) >= 0) {
    kvpair_t pair = getKVLine(line);
    results->kvpairs =
        realloc(results->kvpairs, (results->length + 1) * sizeof(*results->kvpairs));
    results->kvpairs[results->length] = pair;
    results->length++;
  }
  free(line);
  assert(fclose(f) == 0);

  return results;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  if (pairs == NULL) {
    return;
  }
  for (size_t i = 0; i < pairs->length; i++) {
    free(pairs->kvpairs[i].key);
    free(pairs->kvpairs[i].value);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i].key, pairs->kvpairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->length; i++) {
    if (strcmp(pairs->kvpairs[i].key, key) == 0) {
      return pairs->kvpairs[i].value;
    }
  }
  return NULL;
}
