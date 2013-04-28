#include "euler.h"

void eu018(char *ans) {
  const int N = 15;
  char data[] = "\
75 \
95 64 \
17 47 82 \
18 35 87 10 \
20 04 82 47 65 \
19 01 23 75 03 34 \
88 02 77 73 07 63 67 \
99 65 04 28 06 16 70 92 \
41 41 26 56 83 40 80 70 33 \
41 48 72 33 47 32 37 16 94 29 \
53 71 44 65 25 43 91 52 97 51 14 \
70 11 33 28 77 73 17 78 39 68 17 57 \
91 71 52 38 17 14 91 43 58 50 27 29 48 \
63 66 04 68 89 53 67 30 73 16 69 87 40 31 \
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";
  int n = 0;
  int *maxima = malloc(N*sizeof(int));
  int *row = malloc(N*sizeof(int));

  memset(maxima, 0, sizeof(maxima));
  for (int i = 0; i < N; i++) {
    int *newmax = malloc(N*sizeof(int));
    memset(newmax, 0, sizeof(newmax));
    memset(row, 0, sizeof(row));
    for (int j = 0; j <= i; j++) {
      row[j] = atoi(data + 3 * n);
      n++;
    }
    newmax[0] = maxima[0] + row[0];
    for (int j = 0; j < i; j++) {
      newmax[j + 1] = max(maxima[j], maxima[j+1]) + row[j + 1];
    }
    if (i > 0) {
      newmax[i] = maxima[i-1] + row[i];
    }
    free(maxima);
    maxima = newmax;
  }

  int best = 0;
  for (int i = 0; i < N; i++) {
    if (maxima[i] > best) best = maxima[i];
  }
  if (best > 0) {
    sprintf(ans, "%d", best);
  }
  free(maxima);
  free(row);
}
