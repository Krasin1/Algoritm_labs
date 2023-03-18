#include <limits.h>
#include <string.h>
#include <iostream>

#define NO_OF_CHARS 256

// A utility function to get maximum of two integers
int max(int a, int b) { return (a > b) ? a : b; }

// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic(char* str, int size, int badchar[NO_OF_CHARS]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++) badchar[i] = -1;

    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++) badchar[(int)str[i]] = i;
}

void search(char* txt, char* pat) {
    int m = (int)strlen(pat);
    int n = (int)strlen(txt);

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;  // s is shift of the pattern with respect to text
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j]) j--;

        if (j < 0) {
            // std::cout << "Found at index = " << s << '\n';
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        } else
            s += max(1, j - badchar[txt[s + j]]);
    }
}

#define d 20
 
void rabinKarp(char pattern[], char text[], int q = 13) {
    int m = (int)strlen(pattern);
    int n = (int)strlen(text);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
 
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;
 
    // Calculate hash value for pattern and text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }
 
    // Find the match
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
 
            // if (j == m)
            //     std::cout << "Pattern is found at position: " << i + 1 << '\n';
        }
 
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
 
            if (t < 0)
                t = (t + q);
        }
    }
}
