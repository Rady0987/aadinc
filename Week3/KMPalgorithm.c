#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void *safeMalloc(int n) {
	void *p = malloc(n);
	if(p == NULL) {
		printf("Error: malloc(%d) failed. Out of memory?\n", n);
		exit(EXIT_FAILURE);
	}
	return p;
}

int *computePi(char *str) {
    int length = strlen(str);
    int *pi = safeMalloc(length);
    int j = 0;
    pi[0] = 0;
    for (int i = 1; i < length;) {
        if (str[i] == str[j]) {
            pi[i] = j + 1;
            i++;
            j++;
        } else {
            if (j != 0) {
                j = pi[j - 1];
            } else {
                pi[i] = 0;
                i++;
            }
        }
    }
    return pi;
}

bool KMPalgorithm(char *str, char *pattern) {
    int *pi;
    int i = 0, j = 0;

    pi = computePi(pattern);

    while (i < strlen(str) && j < strlen(pattern)) {
        if(str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            if(j != 0) {
                j = pi[j - 1];
            } else {
                i++;
            }
        }
    }

    if(j == strlen(pattern)) 
        return true;

    return false;
}

int main(int argc, char *argv[]) {
    char str[7] = "tartans";
    char str1[10] = "abaaabbabb";

    //printf("%d\n", KMPalgorithm(str1, "abas"));

    char test[11] = "abracadabra";
    int *pi = computePi(test);
    for(int i = 0; i < 11; i++) {
        printf("%d, ", pi[i]);
    }

    printf("\n");
    free(pi);
    return 0;
}