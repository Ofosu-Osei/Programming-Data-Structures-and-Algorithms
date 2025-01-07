#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stddef.h>
#include <stdio.h>

#include "provided.h"

//any functions you want your main to use
extern int isStep1Mode;
void makeStory(FILE * input_story, catarray_t * categories, int reused_word_flag);
catarray_t * readCWs(const char * fname);
void freeCatArray(catarray_t * cats);
#endif
