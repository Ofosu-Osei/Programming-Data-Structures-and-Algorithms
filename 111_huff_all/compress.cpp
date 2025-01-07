#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading

  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter

  //dont forget to lookup 256 for the EOF marker, and write it out.

  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.

  FILE * file = fopen(inFile, "r");
  if (file == NULL) {
    perror("Error openig input file");
    exit(EXIT_FAILURE);
  }

  int c;
  while ((c = fgetc(file)) != EOF) {
    // Find BitString for the char in theMap
    std::map<unsigned, BitString>::const_iterator it = theMap.find(c);
    if (it == theMap.end()) {
      fprintf(stderr, "Input Error: Unknown Character: '%c'\n", c);
      exit(EXIT_FAILURE);
    }

    // Write BitString tooutput file
    bfw.writeBitString(it->second);
  }

  // Write the EOF marker (256) to output file
  std::map<unsigned, BitString>::const_iterator eofIt = theMap.find(256);
  if (eofIt == theMap.end()) {
    fprintf(stderr, "Error: EOF marker (256) not found in encoding map\n");
    exit(EXIT_FAILURE);
  }
  bfw.writeBitString(eofIt->second);

  fclose(file);
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  const char * inFile = argv[1];
  const char * outFile = argv[2];
  uint64_t * counts = readFrequencies(argv[1]);
  assert(counts != NULL);
  Node * tree = buildTree(counts);
  delete[] counts;
  std::map<unsigned, BitString> theMap;
  BitString empty;
  tree->buildMap(empty, theMap);
  writeCompressedOutput(inFile, outFile, theMap);
  delete tree;

  return EXIT_SUCCESS;
}
