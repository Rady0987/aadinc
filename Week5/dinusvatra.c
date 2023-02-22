#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hashItem {
    char* key;
    int value;
} hashItem;
  
typedef struct hashTable {
    hashItem** items;
    int size;
    int count;
} hashTable;

int hash( char *str, int size) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return (int) (hash % size);
}

void freeTable(hashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->items[i] != NULL) {
            free(table->items[i]->key);
            free(table->items[i]);
        }
    }
    free(table->items);
    free(table);
}

hashItem* initItem(char* key, int value) {
    hashItem* item = (hashItem*)malloc(sizeof(hashItem));
    item->key = (char*)malloc(strlen(key) + 1);
    strcpy(item->key, key);
    item->value = value;
    return item;
}
 
hashTable* initTable(int size) {
    hashTable* table = (hashTable*)malloc(sizeof(hashTable));
    table->size = size+2;
    table->items = (hashItem**)calloc(table->size, sizeof(hashItem*));
    for (int i = 0; i < table->size; i++) {
        table->items[i] = NULL;
    }
    return table;
}

void insertHashTable(hashTable* table, char* key, int value) { // fills the first availible spot
    int try = hash(key,table->size);
    for (int i = 0; i < table->size; i++) { // we know we will find a place because the array is big enough
        try =  (try + i) % table->size;
        if (table->items[try] == NULL) {
            table->items[try] = initItem(key, value);
            return;
        } else if (strcmp(table->items[try]->key, key) == 0) {
            table->items[try]->value += value;
            return;
        }
    }
}
 
int searchHashTable(hashTable* table, char* key) {
    int try = hash(key,table->size);
    for (int i = 0; i < table->size; i++) {
        try =  (try + i) % table->size;
        if (table->items[try] != NULL && strcmp(table->items[try]->key, key) == 0 ) {
            return table->items[try]->value;
        }
    }
    return -1;
}
 
void printResult(hashTable* table, char* key) {
    int result = searchHashTable(table, key);
    if (result != -1) {
        printf("%d\n", result);
    } else {
        printf("0\n");
    }
}
 
int main(int argc, char *argv[]) {
    int nrJourneys, nrFriends, distance;
    char name[55];
    scanf("%d %d", &nrJourneys, &nrFriends);
    hashTable* hTable = initTable(nrFriends);

    for(int i = 0; i < nrJourneys; i++){
        scanf("%s %d", &name, &distance);
        insertHashTable(hTable, name, distance);
    }

    scanf("%d", &nrFriends);
    for(int i = 0; i < nrFriends; i++){
        scanf("%s", &name);
        printResult(hTable, name);
    }

    freeTable(hTable);
    return 0;
}