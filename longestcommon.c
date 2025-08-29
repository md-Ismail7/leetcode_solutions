#include <string.h>
#include <stdlib.h>

static inline int max(int a, int b) { return a > b ? a : b; }

int longestCommonSubsequence(char* text1, char* text2) {
    int n = (int)strlen(text1);
    int m = (int)strlen(text2);
    if (n == 0 || m == 0) return 0;

    // We'll make 'm' the shorter string to save memory
    if (m > n) {
        // swap pointers and lengths
        char *tmpS = text1; text1 = text2; text2 = tmpS;
        int  tmpL = n;      n = m;        m = tmpL;
    }

    int *prev = (int*)calloc(m + 1, sizeof(int));
    int *cur  = (int*)calloc(m + 1, sizeof(int));
    if (!prev || !cur) { free(prev); free(cur); return 0; }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                cur[j] = prev[j - 1] + 1;
            } else {
                cur[j] = max(prev[j], cur[j - 1]);
            }
        }
        // roll rows
        int *tmp = prev; prev = cur; cur = tmp;
        // zero out cur for next iteration (optional but tidy)
        memset(cur, 0, (m + 1) * sizeof(int));
    }

    int ans = prev[m];
    free(prev);
    free(cur);
    return ans;
}
