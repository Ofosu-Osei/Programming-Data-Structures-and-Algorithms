#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t inputLen = strlen(inputName);
  const char * ext = ".counts";
  size_t extLen = strlen(ext);

  char * outputName = malloc(inputLen + extLen + 1);

  strcpy(outputName, inputName);
  strcat(outputName, ext);

  return outputName;
}
