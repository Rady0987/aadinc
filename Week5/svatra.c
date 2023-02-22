#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct dataItem {
    char key[50];
    int data;
} dataItem;

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

unsigned long hOne(char *name, int m) {
    unsigned long hash = 5381;
       for(int i = 0; i < strlen(name); i++) {
            //hash = ((hash << 5) + hash) + name[i]; /* hash * 33 + c */
            hash = hash * 33 + name[i];
        }
        return hash % m;

}

int hTwo(char *name, int m, int j) {
    int i, c;
    i = hOne(name, m);
    c = (hOne(name, m) % (m - 1)) + 1;
    return (i + j * c) % m;
}

int isPrime(int n){ 
	if (n <= 1) 
      return 0; 
	if ((n % 2 == 0) && (n > 2)) 
      return 0; 
	for (int i = 3; i * i <= n; i += 2) { 
		if (n % i == 0)
		   return 0;
	}
	return 1;
}

int nextPrime(int n) {
    bool found = false;
    if(n <= 1)
        return 2;
    if(isPrime(n))
        return n;
    while(!found) {
        n++;
        if(isPrime(n))
            found = true;
    }
    return n;
}

int hashSearch(dataItem *hashTable, char *name, int m) {
    int i = 0, k;
    while(i != m) {
        k = hTwo(name, m, i);
            if(k < 0) {
                printf("i=%d\n", i);
                k = hTwo(name, m, i);
            }
            printf("%d\n", k);
            if(!strcmp(hashTable[k].key, name)) {
                return k;
            }
            i++;
    }
    return -1;
}

void insert(dataItem *hashTable, int m, int km, char *name) {
    int hashKey, j = 1, k;
    bool invariant = false;
    k = hashSearch(hashTable, name, m);
    if(k == -1) {
        while(!invariant) {
            hashKey = hTwo(name, m, j);
           // printf("hashkey = %d\n", hashKey);
            if(!strcmp(hashTable[hashKey].key, "NULL")) {
                strcpy(hashTable[hashKey].key, name);
                hashTable[hashKey].data = km;
                invariant = true;
                //printf("SUCCESS instert\n");
            }
            j++;
        }
    } else {
        hashTable[k].data += km;
    }
}

int main(int argc, char *argv[]) {
    int n, friends, km, k, tableLength, key;
    dataItem *hashTable;
    char name[50];

    //initHash(hashTable, m);

    scanf("%d %d", &n, &friends);

    tableLength = nextPrime(friends);
    hashTable = safeMalloc(tableLength * sizeof(dataItem));

    for(int i = 0; i < tableLength; i++) {
        strcpy(hashTable[i].key, "NUL");
        hashTable[i].data = 0;
    }
    

    for(int i = 0; i < n; i++) {
        scanf("%s %d", name, &km);
        //printf("%d\n", hTwo(name, tableLength, i));
        insert(hashTable, tableLength, km, name);
    }

    // printf("----------------\n");
    // for(int i = 0; i < tableLength; i++) {
    //     printf("%s are %d\n", hashTable[i].key, hashTable[i].data);
    // }

    scanf("%d", &k);
    for(int i = 0; i < k; i++) {
        scanf("%s", name);
        key = hashSearch(hashTable, name, tableLength);
        //printf("%d\n", hashTable[key].data);
    }
    free(hashTable);
    return 0;
}