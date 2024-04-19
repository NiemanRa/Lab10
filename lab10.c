#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int count;
    struct Trie* next[26];
};

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->count = 0;

    // Set each pointer to NULL
    int i;
    for (i = 0; i < 26; i++)
        myTree->next[i] = NULL;

    // Return Pointer to New Root
    return myTree;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i = 0;

    while (i != strlen(word))
    {
        // If next doesn't exist, Create
        int nextIndex = word[i] - 'a';
        if (pTrie->next[nextIndex] == NULL)
        {
            pTrie->next[nextIndex] = createTrie();
            pTrie->next[nextIndex]->count += 1;
        }

        pTrie = pTrie->next[nextIndex];

        i++;
    }

    //pTrie->count = 1;
}

// Computes the number of occurences of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int o = 0; // "o" for "occurence"
    int nextIndex;

    struct Trie* temp;
    temp = pTrie;

    do {
        nextIndex = word[o] - 'a';
        if (temp->next[nextIndex] == NULL)
            return 0;

        temp = temp->next[nextIndex];
        o++;

    } while (o != strlen(word));

    return temp->count;
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    int deAl; // "deAl" for "deallocation"
    for (deAl = 0; deAl < 26; deAl++)
        if (pTrie->next[deAl] != NULL)
            deallocateTrie(pTrie->next[deAl]);

    pTrie = NULL;
    free(pTrie);

    return pTrie;
}

// This function will return number of words in the dictionary, and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* file = fopen(filename, "r");

    if (file == NULL)
        return -1;

    int commands = 0;

    // Read and Insert Each Work
    fscanf(file, "%d\n", &commands);
    char word[100];

    for (int r = 0; r < commands; r++) // "r" for "read"
    {
        fscanf(file, "%s\n", word);
        pInWords[r] = (char*) malloc(sizeof(char*) * strlen(word));
        strcpy(pInWords[r], word);
        printf("Word: %s\n", word);
    }

    return commands;
}

int main(void)
{
	char *inWords[256];
	
	// Read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i = 0; i < numWords; ++i)
	{
		printf("%s\n", inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i = 0; i < numWords; i++)
	{
		insert(pTrie, inWords[i]);
	}

	// Parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i = 0; i < 5; i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
    

	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");

	return 0;
}