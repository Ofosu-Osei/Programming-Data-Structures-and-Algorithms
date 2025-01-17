#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAT_SIZE 10

void rotateMatrix90(char matrix[MAT_SIZE][MAT_SIZE]) {
  char matrixCopy[MAT_SIZE][MAT_SIZE];
  for (int j = 0; j < MAT_SIZE; j++) {
    for (int i = MAT_SIZE - 1, k = 0; i >= 0; i--, k++) {
      matrixCopy[j][k] = matrix[i][j];
    }
  }
  memcpy(matrix, matrixCopy, MAT_SIZE * MAT_SIZE);
}

int main(int argc, char ** argv) {
  // Check for correct usage
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Open file for reading
  FILE * f = fopen(argv[1], "r");
  // Check if file is null
  if (f == NULL) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char matrix[MAT_SIZE][MAT_SIZE];
  char line[MAT_SIZE + 2];

  //Read and validate each line of the matrix from the file
  for (int i = 0; i < MAT_SIZE; i++) {
    // Validate if lines are less than expected (10)
    if (!fgets(line, sizeof(line), f)) {
      fprintf(stderr, "Error: Less that 10 lined in file\n");
      fclose(f);
      return EXIT_FAILURE;
    }

    //Validate if a line is too long
    if (strchr(line, '\n') == NULL) {
      fprintf(stderr, "Error: line %d is too long\n", i + 1);
      fclose(f);
      return EXIT_FAILURE;
    }

    //Copy character to the matrix, excluding the newline char
    for (int j = 0; j < MAT_SIZE; j++) {
      matrix[i][j] = line[j];
    }
  }
  // Check for extra lines after reading the expected 10 lines
  if (fgets(line, sizeof(line), f) != NULL) {
    fprintf(stderr, "Error: More that 10 lines in file\n");
    fclose(f);
    return EXIT_FAILURE;
  }

  fclose(f);

  rotateMatrix90(matrix);

  //Print the Matrix
  for (int i = 0; i < MAT_SIZE; i++) {
    for (int j = 0; j < MAT_SIZE; j++) {
      putchar(matrix[i][j]);
    }
    putchar('\n');
  }

  return EXIT_SUCCESS;
}
