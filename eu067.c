#include "euler.h"

void eu067(char *ans) {
  const int N = 100;

  int a[N], b[N];

  memset(a, 0, sizeof(a));
  memset(b, 0, sizeof(b));

  FILE *fp = fopen("triangle.txt", "r");
  if (fp == 0) {
    perror("triangle.txt");
    exit(1);
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      int v;
      int rc = fscanf(fp, "%d", &v);
      if (rc == 0) break;
      if (j == 0) {
        b[j] = a[0] + v;
      } else if (j == i) {
        b[j] = a[j-1] + v;
      } else {
        b[j] = max(a[j-1], a[j]) + v;
      }
    }
    memcpy(a, b, sizeof(b));
  }

  int max = 0;
  for (int i = 0; i < N; i++) {
    if (a[i] > max) {
      max = a[i];
    }
  }
  sprintf(ans, "%d", max);
}
