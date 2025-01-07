#include "rand_story.h"

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Initialize mode for step 1
int isStep1Mode = 0;

// Helper function to validate placeholders
int getPlaceholders(const char * line) {
  const char * curr = line;

  while ((curr = strchr(curr, '_')) != NULL) {
    const char * end = strchr(curr + 1, '_');
    if (end == NULL) {
      return -1;  // Error case
    }
    curr = end + 1;
  }
  return 0;
}

// Helper function to strip new line
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

//Helper function to initialize a struct data type for usedwords
void initUsedWords(category_t * usedWords) {
  usedWords->name = strdup("usedWords");
  usedWords->words = NULL;
  usedWords->n_words = 0;
}

//Helper function to add used words
void addUsedWord(category_t * usedWords, const char * word) {
  usedWords->words =
      realloc(usedWords->words, (usedWords->n_words + 1) * sizeof(*usedWords->words));
  assert(usedWords->words != NULL);
  usedWords->words[usedWords->n_words] = strdup(word);
  assert(usedWords->words[usedWords->n_words] != NULL);
  usedWords->n_words++;
}

//Helper function to get used words from previouslu used words
const char * getUsedWord(category_t * usedWords, size_t index) {
  if (index > 0 && index <= usedWords->n_words) {
    return usedWords->words[usedWords->n_words - index];
  }
  else {
    fprintf(stderr, "Reference Error: Invalid word reference: %zu\n", index);
    exit(EXIT_FAILURE);
  }
}

//Helper function to free created  usedWords
void freeUsedWords(category_t * usedWords) {
  for (size_t i = 0; i < usedWords->n_words; i++) {
    free(usedWords->words[i]);
  }
  free(usedWords->words);
  free(usedWords->name);
}

// Helper function to check if a string is a positive number
int isPositiveNum(const char * str) {
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (!isdigit(str[i])) {
      return -1;
    }
  }
  return atoi(str);
}

// Helper function to get or create categories
category_t * getCategory(catarray_t * categories, const char * cat_name) {
  for (size_t i = 0; i < categories->n; i++) {
    if (strcmp(categories->arr[i].name, cat_name) == 0) {
      return &categories->arr[i];
    }
  }
  categories->arr =
      realloc(categories->arr, (categories->n + 1) * sizeof(*categories->arr));
  assert(categories->arr != NULL);
  category_t * new_cat = &categories->arr[categories->n];
  new_cat->name = strdup(cat_name);
  new_cat->words = NULL;
  new_cat->n_words = 0;
  categories->n++;

  return new_cat;
}

// Helper function to read category-words input
catarray_t * readCWs(const char * fname) {
  catarray_t * results = malloc(sizeof(*results));
  results->arr = NULL;
  results->n = 0;

  if (fname == NULL) {
    return results;
  }

  FILE * f = fopen(fname, "r");
  if (fname == NULL) {
    perror("Failed to open words file");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t len = 0;

  while (getline(&line, &len, f) != -1) {
    stripNewline(line);
    char * delimeter = strchr(line, ':');
    if (delimeter == NULL) {
      fprintf(stderr, "Input Error: Invalid input format: %s\n", line);
      exit(EXIT_FAILURE);
    }
    // Replace colon with a string terminator
    *delimeter = '\0';
    const char * cat_name = line;
    const char * word = delimeter + 1;
    //Get category name
    category_t * category = getCategory(results, cat_name);
    // Add the word to the category
    category->words =
        realloc(category->words, (category->n_words + 1) * sizeof(*category->words));
    assert(category->words != NULL);
    category->words[category->n_words] = strdup(word);
    category->n_words++;
  }
  free(line);
  assert(fclose(f) == 0);

  return results;
}

// Helper function to free all categories and words
void freeCatArray(catarray_t * cats) {
  for (size_t i = 0; i < cats->n; i++) {
    free(cats->arr[i].name);
    for (size_t j = 0; j < cats->arr[i].n_words; j++) {
      free(cats->arr[i].words[j]);
    }
    free(cats->arr[i].words);
  }
  free(cats->arr);
  free(cats);
}

// Helper Function to remove used word from category array
void removeUsedWord(catarray_t * categories, const char * cat_name, const char * word) {
  category_t * found_category = NULL;
  // Search for the category in the array
  for (size_t i = 0; i < categories->n && !found_category; i++) {
    if (strcmp(categories->arr[i].name, cat_name) == 0) {
      found_category = &categories->arr[i];
    }
  }
  // printf("After search cat\n");
  if (found_category == NULL) {
    fprintf(stderr, "Used Words Error: Category %s not found.\n", cat_name);
    exit(EXIT_FAILURE);
  }

  // search the found category to locate the used word
  ssize_t found_index = -1;
  for (size_t i = 0; i < found_category->n_words && found_index < 0; i++) {
    if (strcmp(found_category->words[i], word) == 0) {
      found_index = i;
    }
  }
  //  printf("After locating word index: %zi\n", found_index);

  if (found_index < 0) {
    fprintf(
        stderr, "Used Words Error: Word %s not found in category %s.\n", word, cat_name);
    exit(EXIT_FAILURE);
  }

  // Get used word pointer to free it later
  char * used_word = found_category->words[found_index];

  //Adjust the remaining words after the found index
  for (size_t i = found_index; i < found_category->n_words - 1; i++) {
    found_category->words[i] = found_category->words[i + 1];
  }

  // Reduce the number of words by one
  found_category->n_words--;
  // Resize the words list in found_category appropriately
  found_category->words = realloc(
      found_category->words, found_category->n_words * sizeof(*found_category->words));
  // Now free the used memory block
  free(used_word);
}

// Helper function to replace a placeholder
const char * replacePlaceholder(const char * start,
                                const char * end,
                                catarray_t * categories,
                                category_t * usedWords,
                                int reused_word_flag) {
  // Get placeholder type
  char * placeholder = strndup(start + 1, end - start - 1);
  assert(placeholder != NULL);

  const char * replacement = NULL;

  // Check if step1  mode is activated
  if (isStep1Mode) {
    replacement = strdup(chooseWord(placeholder, NULL));
  }
  else {
    int index = isPositiveNum(placeholder);
    // Check if placeholder is a positive number
    // for previously used word
    if (index > 0) {
      // Use a previously used word
      replacement = strdup(getUsedWord(usedWords, index));
    }
    else {
      // Choose word from the category
      replacement = strdup(chooseWord(placeholder, categories));
      if (replacement == NULL) {
        fprintf(stderr, "Choose Word Error: Invalid category name: %s\n", placeholder);
        exit(EXIT_FAILURE);
      }
      else {
        // Remove used word if indicated
        if (reused_word_flag == 1) {
          removeUsedWord(categories, placeholder, replacement);
        }
      }
    }
    // Save chosen word to the usedWords category
    addUsedWord(usedWords, replacement);
  }
  free(placeholder);
  return replacement;
}

// Helper function to replace all placeholders
char * replacePlaceholders(const char * line,
                           catarray_t * categories,
                           category_t * used_words,
                           int reused_word_flag) {
  size_t result_len = 0;
  size_t line_len = strlen(line);
  char * result = malloc(line_len + 1);
  assert(result != NULL);
  const char * line_char = line;

  while (*line_char != '\0') {
    if (*line_char == '_') {
      const char * end = strchr(line_char + 1, '_');

      // Get the replacement word
      const char * replacement =
          replacePlaceholder(line_char, end, categories, used_words, reused_word_flag);
      size_t replacement_len = strlen(replacement);

      result = realloc(result, result_len + replacement_len + 1);
      assert(result != NULL);
      strcpy(result + result_len, replacement);
      result_len += replacement_len;

      // Move past the placeholder
      line_char = end + 1;
      free((char *)replacement);
    }
    else {
      // Copy regular characters
      result = realloc(result, result_len + 2);
      assert(result != NULL);
      result[result_len++] = *line_char++;
      result[result_len] = '\0';
    }
  }
  return result;
}

// Helper function to print processed story
void printStory(char ** lines,
                size_t count,
                catarray_t * categories,
                int reused_word_flag) {
  category_t used_words;
  initUsedWords(&used_words);

  for (size_t i = 0; i < count; i++) {
    char * processed_line =
        replacePlaceholders(lines[i], categories, &used_words, reused_word_flag);
    printf("%s", processed_line);
    free(processed_line);
  }
  freeUsedWords(&used_words);
}

// Helper function to free lines
void freeLines(char ** lines, size_t line_count) {
  for (size_t i = 0; i < line_count; i++) {
    free(lines[i]);
  }
  free(lines);
}

// Main function to make a random story out of the input story file and category-words file
void makeStory(FILE * input_story, catarray_t * categories, int reused_word_flag) {
  char ** lines = malloc(sizeof(*lines));
  assert(lines != NULL);
  char * line = NULL;
  size_t len = 0;
  size_t line_count = 0;

  while (getline(&line, &len, input_story) != -1) {
    lines = realloc(lines, (line_count + 1) * sizeof(*lines));
    if (getPlaceholders(line) == -1) {
      fprintf(stderr, "Placeholder Error: Mismathed placeholder.\n");
      exit(EXIT_FAILURE);
    }
    lines[line_count] = line;
    line_count++;
    line = NULL;
  }
  free(line);
  printStory(lines, line_count, categories, reused_word_flag);
  freeLines(lines, line_count);
}
