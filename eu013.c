#include "euler.h"

void
readnum(char *num, FILE *fp) {
  char buf[100];
  int k = 0;
  char *p = fgets(buf, 100, fp);
  if (p != 0) {
    for (int j = strlen(p) - 1; j >= 0; j--) {
      num[k] = p[j] - '0';
      k++;
    }
  }
  while (k < 100) num[k++] = 0;
}

void add(char *dst, char *src, int n) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    int d = dst[i] + src[i] + c;
    dst[i] = d % 10;
    c = d / 10;
  }
}

void mul1(char *dst, int a, int n) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    int d = dst[i] * a + c;
    dst[i] = d % 10;
    c = d / 10;
  }
}


void eu013(char *ans) {
  FILE *fp = fopen("eu013.txt", "r");
  char sum[100];
  char num[100];

  memset(sum, 0, 100);

  for (int i = 0; i < 100; i++) {
    readnum(num, fp);
    add(sum, num, 100);
  }

  fclose(fp);

  for (int i = 99; i >= 0; i--) {
    if (sum[i] > 0) {
      for (int j = 0; j < 10; j++) {
        ans[j] = sum[i-j] + '0';
      }
      ans[10] = 0;
      return;
    }
  }
}
