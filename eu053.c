#include "euler.h"

/*
 * How many values nCr are are 1,000,000+ for n<=100?
 * We use the Pascal's Triangle method of generating nCr,
 * but max out the entries at a million.
 */
void eu053(char *ans) {
  const int N = 102;
  const int MAX = 1000000;
  int *row1 = malloc(N*sizeof(int));
  int *row2 = malloc(N*sizeof(int));
  int count = 0;

  row1[0] = 1;
  row1[1] = 0;
  for (int i = 1; i < 101; i++) {
    row2[0] = 1;
    for (int j = 0; j < i; j++) {
      int cell = row1[j] + row1[j+1];
      if (cell >= MAX) {
        count++;
        cell = MAX;
      }
      row2[j+1] = cell;
    }
    row2[i+1] = 0;

    int *t = row1;
    row1 = row2;
    row2 = t;
  }

  sprintf(ans, "%d", count);

  free(row1);
  free(row2);
}
