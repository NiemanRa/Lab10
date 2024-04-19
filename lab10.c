#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{	
    int isaWord; // 0 if not a word, 1 if a word!
    struct trie* next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{
    int i = 0;

    while (i != strlen(word))
    {
        // See if the next place to go exists, if not, create it.
        int nextIndex = word[i] - 'a';
        if (pTrie->next[nextIndex] == NULL)
            pTrie->next[nextIndex] = init();

        pTrie = pTrie->next[nextIndex];

        i++;
    }

    pTrie->isaWord = 1;
}

// Computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    
}

// Deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->isaWord = 0;

    // Set each pointer to NULLL.
    int i;
    for (i = 0; i < 26; i++)
        myTree->next[i] = NULL;

    // Return a pointer to the new root.
    return myTree;
}

// This function will return number of words in the dictionary, and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    struct trie* myDictionary = init();

    char c, r;
    fscanf(filename, "%d", &c);

    // Read in each word and insert it.
    for (r = 0; r < strlen(pInWords); r++) {
        char word[100];
        fscanf(filename, "%s", word);
        insert(myDictionary, word);
        // debug code to trace which word is being processed for large list of words
        // if (i%10000 == 0) printf("%d word is %s\n", i, word);
    }

    free(filename);

    // return SIZE OF TREE;
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