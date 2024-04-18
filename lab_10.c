#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
    struct Trie *nodes[26];
    int isEndOfWord;
    int count;
};

// Function prototypes
void insert(struct Trie *pTrie, char *word);
int numberOfOccurrences(struct Trie *pTrie, char *word);
void deallocateTrie(struct Trie **pTrie);
struct Trie *createTrie();
int readDictionary(char *filename, char **pInWords);


int main(void) {

	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
	}
	deallocateTrie(&pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");

	return 0;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {

    struct Trie *current = pTrie;

    for (int i = 0; i < strlen(word); i++) {//for each letter

        int index = word[i] - 'a';//find alphabet position
        if (!current->nodes[index]) current->nodes[index] = createTrie();//if not filled then fill
        
        current = current->nodes[index];//set next 
    }

    current->isEndOfWord = 1;//set end of word true
    current->count++;//increment
}

// computes the number of occurances of the word
int numberOfOccurrences(struct Trie *pTrie, char *word) {

    struct Trie *current = pTrie;
    for (int i = 0; i < strlen(word); i++) {//for length

        int index = word[i] - 'a';//index in alphabet
        if (!current->nodes[index]) {
            return 0;
        }
        current = current->nodes[index];
    }

    if (current != NULL && current->isEndOfWord) {
        return current->count;
    }

    return 0;
}

// deallocate the trie structure
void deallocateTrie(struct Trie **pTrie) {

    if (*pTrie) {

        for (int i = 0; i < 26; i++) deallocateTrie(&((*pTrie)->nodes[i]));//deallocate each node
        
        free(*pTrie);
        *pTrie = NULL; //pointer is NULL after deallocating
    }

}

// Initializes a trie structure
struct Trie *createTrie() {

    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));

    if (node) {//if successful allocation
        node->isEndOfWord = 0;
        node->count = 0;
        for (int i = 0; i < 26; i++) {
            node->nodes[i] = NULL;
        }
    }

    return node;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords) {

    FILE *file = fopen(filename, "r");//open for reading
    
    int numWords;
    fscanf(file, "%d", &numWords);

    for (int i = 0; i < numWords; i++) {
        pInWords[i] = (char *)malloc(45 * sizeof(char)); //max word length 45
        fscanf(file, "%s", pInWords[i]);
    }

    fclose(file);
    return numWords;
}
