#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Trie structure
struct Trie {
  int count;
  struct Trie *children[ALPHABET_SIZE];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (pTrie->children[index] == NULL) {
      pTrie->children[index] = malloc(sizeof(struct Trie));
      memset(pTrie->children[index]->children, 0,
             sizeof(pTrie->children[index]->children));
      pTrie->children[index]->count = 0;
    }
    pTrie = pTrie->children[index];
  }
  pTrie->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
  for (int i = 0; i < strlen(word); i++) {
    int index = word[i] - 'a';
    if (pTrie->children[index] == NULL) {
      return 0;
    }
    pTrie = pTrie->children[index];
  }
  return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
  if (pTrie != NULL) {
    for (int i = 0; i < 26; i++) {
      if (pTrie->children[i] != NULL) {
        deallocateTrie(pTrie->children[i]);
      }
    }
    free(pTrie);
  }
  return NULL;
}

// Initializes a trie structure
struct Trie *createTrie() {
  struct Trie *pTrie = malloc(sizeof(struct Trie));
  pTrie->count = 0;
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    pTrie->children[i] = NULL;
  }
  return pTrie;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("Error opening file %s\n", filename);
    return 0;
  }
  int numWords = 0;
  char word[100];
  while (fscanf(file, "%s", word) != EOF) {
    numWords++;
    pInWords[numWords - 1] = malloc(strlen(word) + 1);
    strcpy(pInWords[numWords - 1], word);
  }
  fclose(file);
}

int main(void) {
  char *inWords[256];

  // read the number of the words in the dictionary
  int numWords = readDictionary("dictionary.txt", inWords);
  for (int i = 0; i < numWords; ++i) {
    printf("%s\n", inWords[i]);
  }

  struct Trie *pTrie = createTrie();
  for (int i = 0; i < numWords; i++) {
    insert(pTrie, inWords[i]);
  }
  // parse lineby line, and insert each word to the trie data structure
  char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
  for (int i = 0; i < 5; i++) {
    printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
  }
  pTrie = deallocateTrie(pTrie);
  if (pTrie != NULL)
    printf("There is an error in this program\n");
  return 0;
}
