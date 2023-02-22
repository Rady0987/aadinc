#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define min(a, b) (a < b ? a : b)
#define max(a, b) (a > b ? a : b)
#define M 713357

typedef struct SvatraNode {
		char name[51];
    int kilometers;
    struct SvatraNode *next;
} SvatraNode;

void *safeMalloc(long int n) {
	void *a = malloc(n);
	if (a == NULL) {
		fprintf(stderr, "Fatal error: safeMalloc(%ld) failed.\n", n);
		exit(EXIT_FAILURE);
	}
	return a;
}

void insertAtHead(SvatraNode **head, char newName[], int newKilometers) {
	SvatraNode *newNode = safeMalloc(sizeof(SvatraNode));
	
	strcpy(newNode->name, newName);
	newNode->kilometers = newKilometers;	
	newNode->next = *head;
	
	*head = newNode;
}

SvatraNode *search(SvatraNode *head, char name[]) {
	SvatraNode *current = head;
	
	if (current == NULL) return NULL;
	
	while (current != NULL) {
		if (!strcmp(current->name, name)) return current;		
		current = current->next;
	}
	
	return current;
}

int hash(char s[], int len) {
	int result = 0;
	
	for (int i=0; i<len; i++) {
		result = (result*256 + (int)s[i]) % M;
	}
	
	return result;
}

void updateKilometerCount(SvatraNode **hashTable, char name[], int len, int kilometers) {
	int hashedIndex = hash(name, len);
	
	SvatraNode *node = search(hashTable[hashedIndex], name);
	
	if (node != NULL) node->kilometers += kilometers;
	else insertAtHead(&(hashTable[hashedIndex]), name, kilometers);
}

int getKilometerCount(SvatraNode **hashTable, char name[], int len) {
	int hashedIndex = hash(name, len);
	SvatraNode *node = search(hashTable[hashedIndex], name);
	
	if (node == NULL) return 0;
	else return node->kilometers;
}

void freeLinkedList(SvatraNode *node) {
	SvatraNode *temp;
	
	while (node != NULL) {
		temp = node;
		node = node->next;
		free(temp);
	}
}

void freeHashTable(SvatraNode **hashTable, int size) {
	for (int i=0; i<size; i++) if (hashTable[i] != NULL) freeLinkedList(hashTable[i]);
	free(hashTable);
}

int main(int argc, char *argv[]) {
	int n, p;
	scanf("%d %d", &n, &p);
	
	char s[51];
	int c;
	
	SvatraNode **hashTable = safeMalloc(M*sizeof(SvatraNode *));
	for (int i=0; i<M; i++) hashTable[i] = NULL;
	
	for (int i=0; i<n; i++) {
		scanf("%s %d", &s, &c);
		updateKilometerCount(hashTable, s, strlen(s), c);
	}
	
	int m;
	scanf("%d", &m);
	
	for (int i=0; i<m; i++) {
		scanf("%s", &s);
		printf("%d\n", getKilometerCount(hashTable, s, strlen(s)));
	}
	
	freeHashTable(hashTable, M);
	
	return 0;
}
