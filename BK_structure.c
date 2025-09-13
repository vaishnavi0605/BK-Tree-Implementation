//Ashutosh Rajput
//2023CSB1289
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <time.h>

//As of now we are restricting the child nodes to 15

//creating structure of node in BK Tree
struct Node
{
    int length;
    char *word;
    struct Node **children;
    int numChildren;
};

//function to create a new node
struct Node* createNode(char *word)
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->length = strlen(word);
    newNode->word = strdup(word);
    newNode->numChildren = 15;
    newNode->children = (struct Node**)malloc(sizeof(struct Node*) * newNode->numChildren);
    for(int i = 0; i < newNode->numChildren; i++)
    {
        newNode->children[i] = NULL;
    }
    return newNode;
}

//function to create a BK tree
struct Node* createBKTree(char *word)
{
    struct Node *root = createNode(word);
    return root;
}



//function to insert a new node in BK tree
void insertNode(struct Node *root,  char *word)
{
    struct Node *currentNode = root;
    int distance = 0;
    while(currentNode != NULL)
    {
        distance = UK_lev_dist(currentNode->word, word);
        if(currentNode->children[distance] == NULL)
        {
            currentNode->children[distance] = createNode(word);
            break;
        }
        else
        {
            currentNode = currentNode->children[distance];
        }
    }
}

void depth_traverse(struct Node *root)
{
    if(root == NULL)
    {
        return;
    }
    for(int i = 0; i < root->numChildren; i++)
    {
        depth_traverse(root->children[i]);
    }
    printf("%s\n", root->word);
}

//function for searching a word in BK tree
void searchBKTree(struct Node *root, char *word, int tolerance, char ***results, int *result_count) {
    if (root == NULL) return;

    int distance = UK_lev_dist(root->word, word);
    if (distance <= tolerance) {
        int index = distance;  // Index based on Levenshtein distance
        if (result_count[index] < 15) 
        {  // Assuming max 15 results per distance
            results[index][result_count[index]] = root->word;
            result_count[index]++;
        }
    }

    // Search in the range of distance - tolerance to distance + tolerance subtrees
    for (int i = fmax(0, distance - tolerance); i <= distance + tolerance && i < root->numChildren; i++) {
        searchBKTree(root->children[i], word, tolerance, results, result_count);
    }
}

void search_preprocessor(struct Node *root) {
    char word[100];
    int tolerance;
    char **results[15];  // Array of 15 arrays for different distances
    int result_count[15] = {0};

    printf("Enter the word to search: ");
    scanf("%s", word);

    printf("Enter the tolerance: ");
    scanf("%d", &tolerance);

    for (int i = 0; i < 15; i++) {
        results[i] = (char **)malloc(15 * sizeof(char *));
    }

    searchBKTree(root, word, tolerance, results, result_count);

    // Return the first non-empty array of results
    for (int i = 0; i < 15; i++) {
        if (result_count[i] > 0) {
            printf("Words within distance %d of '%s':\n", i, word);
            for (int j = 0; j < result_count[i]; j++) {
                printf("  %s\n", results[i][j]);
            }
            // Free memory after use
            for (int k = 0; k < 15; k++) {
                free(results[k]);
            }
            return;
        }
    }

    printf("No words found within the given tolerance.\n");
    // Free memory even if no results are found
    for (int k = 0; k < 15; k++) {
        free(results[k]);
    }

    //ask to insert the word in the dictionary
    printf("Do you want to insert the word in the dictionary? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y') {
        insertNode(root, word);
        //open the txt file and insert the word in the dictionary in new line
        FILE *fp = fopen("dictionary.txt", "a");
        fprintf(fp, "%s\n", word);
        fclose(fp);
        printf("Word inserted successfully.\n");
    }
}

void autoCompleteBKTree(struct Node *root, const char *prefix, char ***results, int *result_count) {
    if (root == NULL) return;

    // Check if the current word starts with the prefix
    if (strncmp(root->word, prefix, strlen(prefix)) == 0) {
        (*result_count)++;
        *results = (char **)realloc(*results, (*result_count) * sizeof(char *));
        (*results)[(*result_count) - 1] = strdup(root->word);
    }

    // Search in all children
    for (int i = 0; i < root->numChildren; i++) {
        autoCompleteBKTree(root->children[i], prefix, results, result_count);
    }
}


void auto_complete_preprocessor(struct Node *root) 
{
    char prefix[100];
    char **results = NULL;
    int result_count = 0;

    // Get the prefix from the user
    printf("Enter the prefix to search: ");
    scanf("%s", prefix);

    // Call the autoCompleteBKTree function
    autoCompleteBKTree(root, prefix, &results, &result_count);

    // Print the suggested words
    if (result_count == 0) {
        printf("No words found with the prefix '%s'.\n", prefix);
    } else 
    {
        printf("Words with prefix '%s':\n", prefix);
        for (int i = 0; i < result_count; i++) 
        {
            printf("  %s\n", results[i]);
            free(results[i]);  // Free each word after use
        }
    }
}






int main() {

    struct Node *root = dic_loader("dictionary.txt");
    
    //depth_traverse(root);

    //ask user whether to search or use auto complete using a swith case based on choice also give choice to exit and repaeat this untill user wants to exit
    char choice;
    do
    {
        printf("Enter s to search a word, a to auto complete, e to exit: ");
        scanf("%c", &choice);
        switch (choice)
        {
        case 's':
            search_preprocessor(root);
            break;
        case 'a':
            auto_complete_preprocessor(root);
            break;
        case 'e':
            printf("Exiting...\n");
            break;
        }
    } while (choice != 'e');

}
