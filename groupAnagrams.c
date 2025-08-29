#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// helper: compare chars for qsort
int cmpChar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// helper: sort a string and return a new string
char* sortString(const char* str) {
    int len = strlen(str);
    char* sorted = (char*)malloc((len + 1) * sizeof(char));
    strcpy(sorted, str);
    qsort(sorted, len, sizeof(char), cmpChar);
    return sorted;
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    // Allocate for max possible groups = strsSize (worst case: no anagrams)
    char*** result = (char***)malloc(sizeof(char**) * strsSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * strsSize);
    char** keys = (char**)malloc(sizeof(char*) * strsSize); // store group keys

    int groups = 0;

    for (int i = 0; i < strsSize; i++) {
        char* key = sortString(strs[i]);
        int found = -1;

        // check if this key already exists
        for (int g = 0; g < groups; g++) {
            if (strcmp(keys[g], key) == 0) {
                found = g;
                break;
            }
        }

        if (found == -1) {
            // new group
            keys[groups] = key;
            result[groups] = (char**)malloc(sizeof(char*) * strsSize); // max allocate
            result[groups][0] = strs[i];
            (*returnColumnSizes)[groups] = 1;
            groups++;
        } else {
            // add to existing group
            result[found][(*returnColumnSizes)[found]] = strs[i];
            (*returnColumnSizes)[found] += 1;
            free(key); // free unused key
        }
    }

    *returnSize = groups;
    free(keys);
    return result;
}

