#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// This function will read lines from a FILE stream into an array of strings.
char ** readData(FILE * stream, size_t * count) {
  char ** lines = NULL;
  char * line = NULL;
  size_t sz = 0;
  *count = 0;

  // Reads until EOF
  while (getline(&line, &sz, stream) >= 0) {
    // Dynamically grows the array.
    lines = realloc(lines, (*count + 1) * sizeof(*lines));
    // Store new line and increments count.
    lines[(*count)++] = line;
    // Reset line pointter so getline will allocate new memory.
    line = NULL;
  }

  // Free the last allocated line (after EOF).
  free(line);

  return lines;
}

// This function prints the array of sorted strings.
void printData(char ** data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    printf("%s", data[i]);
  }
}

// This function frees the memory allocated for the array of strings.
void freeData(char ** data, size_t count) {
  for (size_t i = 0; i < count; i++) {
    free(data[i]);  // Frees each individual string.
  }
  // Frees the array of pointers
  free(data);
}

// This function acts as the execution pipeline. Handles reading, sorting
// printing and freeing data for a given input stream.
void processStream(FILE * stream) {
  size_t n = 0;
  char ** data = readData(stream, &n);
  sortData(data, n);
  printData(data, n);
  freeData(data, n);
}

// The main entry point to the program
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    // No file arguements: read from stdin.
    processStream(stdin);
  }
  else {
    // Process each file provided as command-line arguement.
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      // Check if f is NULL
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      // Process the opened file.
      processStream(f);

      //Attemptto close file
      if (fclose(f) != 0) {
        fprintf(stderr, "Could not close file\n");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
