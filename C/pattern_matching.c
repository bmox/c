// 10. To implement Pattern Matching Technique using Brute Force Algorithm.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int i, j, k, n, m, flag = 0;
    char t[40], p[30];

    printf("Enter text: ");
    scanf("%s", t);

    printf("Enter pattern: ");
    scanf("%s", p);

    n = strlen(t);
    m = strlen(p);

    for (i = 0; i <= n - m; i++) {
        j = 0;
        while (j < m && p[j] == t[j + i]) {
            j++;
        }

        if (j == m) {
            flag = 1;
            k = i + 1;
            break;  // Added break to exit the loop when the pattern is found
        } else {
            flag = 0;
        }
    }

    if (flag == 1) {
        printf("Pattern found at position: %d\n", k);
    } else {
        printf("Pattern not found in text\n");
    }

    return 0;
}

//Output:
// Enter text: ababcababcabc
// Enter pattern: abc
// Pattern found at position: 3

