#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 100
#define HASH_TABLE_SIZE 10000

// Simple hash table implementation
typedef struct {
    char** words;
    int size;
    int capacity;
} Dictionary;

// Hash function
unsigned int hash(const char* word) {
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash_value = hash_value * 31 + word[i];
    }
    return hash_value % HASH_TABLE_SIZE;
}

// Initialize dictionary
Dictionary* create_dictionary() {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));
    dict->capacity = HASH_TABLE_SIZE;
    dict->size = 0;
    dict->words = (char**)malloc(sizeof(char*) * dict->capacity);
    
    for (int i = 0; i < dict->capacity; i++) {
        dict->words[i] = NULL;
    }
    
    return dict;
}

// Add word to dictionary
void add_word(Dictionary* dict, const char* word) {
    unsigned int index = hash(word);
    
    // Simple collision resolution using linear probing
    while (dict->words[index] != NULL) {
        // Word already exists
        if (strcmp(dict->words[index], word) == 0) {
            return;
        }
        
        // Move to next slot
        index = (index + 1) % dict->capacity;
    }
    
    // Add the word
    dict->words[index] = strdup(word);
    dict->size++;
}

// Check if word exists in dictionary
bool contains(Dictionary* dict, const char* word) {
    unsigned int index = hash(word);
    
    while (dict->words[index] != NULL) {
        if (strcmp(dict->words[index], word) == 0) {
            return true;
        }
        
        index = (index + 1) % dict->capacity;
        
        // If we've checked all slots or found an empty slot after the hash
        if (dict->words[index] == NULL) {
            break;
        }
    }
    
    return false;
}

// Free dictionary memory
void free_dictionary(Dictionary* dict) {
    for (int i = 0; i < dict->capacity; i++) {
        if (dict->words[i] != NULL) {
            free(dict->words[i]);
        }
    }
    free(dict->words);
    free(dict);
}

int main() {
    Dictionary* dictionary = create_dictionary();
    
    // Read dictionary file
    FILE* file = fopen("aliceInWonderlandDictionary.txt", "r");
    if (file == NULL) {
        printf("Error opening dictionary file\n");
        return 1;
    }
    
    char buffer[MAX_WORD_LENGTH];
    while (fgets(buffer, MAX_WORD_LENGTH, file) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = 0;
        add_word(dictionary, buffer);
    }
    
    fclose(file);
    
    // Check if words are in the dictionary
    const char* words[] = {"alice", "tacos", "lice", "william", "handsome", "aliceinwonderland"};
    int num_words = sizeof(words) / sizeof(words[0]);
    
    for (int i = 0; i < num_words; i++) {
        if (contains(dictionary, words[i])) {
            printf("%s is in the dictionary.\n", words[i]);
        } else {
            printf("%s is not in the dictionary.\n", words[i]);
        }
    }
    
    free_dictionary(dictionary);
    return 0;
}