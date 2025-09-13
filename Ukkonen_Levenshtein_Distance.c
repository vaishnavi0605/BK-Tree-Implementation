#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define NEG_INF -100000
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int abs(int a) {
    if(a < 0) return -a;
    return a;
}

void evaluate(int** f, char* a, char* b, int k, int p) {
    int m = strlen(a);
    int n = strlen(b);
    int k2 = k + m;
    int p2 = p + 1;
    
    int t = f[k2][p2-1] + 1;
    if(k2 > 0) t = MAX(t, f[k2-1][p2-1]);
    if(k2 < m+n) t = MAX(t, f[k2+1][p2-1] + 1);

    while(t < m && t+k < n && t >= 0 && t+k >= 0 && a[t] == b[t+k]) t++;
    if(t > m || t+k > n) f[k2][p2] = NEG_INF;
    else f[k2][p2] = t;

}

int edit_dist(int** f, char* a, char* b) {
    int m = strlen(a);
    int n = strlen(b);
    int p = -1;
    int r = p - MIN(m, n);
    while(f[n][p+1] != m) {
        p++;
        r++;
        if(r <= 0) {
            for(int k = -p; k <= p; k++) {
                evaluate(f, a, b, k, p);
            }
        }
        else {
            for(int k = MAX(-m, -p); k <= -r; k++) {
                evaluate(f, a, b, k, p);
            }
            for(int k = r; k <= MIN(n, p); k++) {
                evaluate(f, a, b, k, p);
            }
        }
    }
    return p;
}

int UK_lev_dist(char* a, char* b) {
    int m = strlen(a);
    int n = strlen(b);
    int diagonals = m + n + 1;
    int cols = MAX(m, n) + 2;

    int** f = (int**)malloc(diagonals * sizeof(int*));
    for(int i = 0; i < diagonals; i++) {
        f[i] = (int*)malloc(cols * sizeof(int));
        int k = i - m;
        for(int j = 0; j < abs(k); j++) {
            f[i][j] = NEG_INF;
        }
        if(k < 0) {
            f[i][abs(k)] = abs(k) - 1;
        }
        else {
            f[i][abs(k)] = -1;
        }
    }
    int result = edit_dist(f, a, b);
    for(int i = 0; i < diagonals; i++) {
        free(f[i]);
    }
    free(f);

    return result;
}
