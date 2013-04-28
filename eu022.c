#include "euler.h"

int readwords(const char *filename, char **words, int maxwords) {
  FILE *fp = fopen(filename, "r");
  if (fp == 0) {
    perror(filename);
    abort();
  }
  static char buf[50000];
  char *p = fgets(buf, sizeof(buf), fp);
  fclose(fp);

  int i = 0;
  for (;;) {
    while (*p == '"') p++;
    words[i++] = p;
    while (*p != '"') p++;
    *p++ = 0;
    if (*p == 0) break;
    p++; /* skip comma */
    if (*p != '"') break;
  }
  return i;
}

int namesort(const void *a, const void *b) {
  return strcmp(* (char * const *) a, * (char * const *) b);
}

void eu022(char *ans) {
  const int maxwords = 8000;
  char *names[maxwords];
  int n = readwords("names.txt", names, maxwords);

  qsort(names, n, sizeof(char *), namesort);

  int total = 0;
  for (int i = 0; i < n; i++) {
    int val = 0;
    for (char *p = names[i]; *p; p++) {
      val += *p - 'A' + 1;
    }
    total += (i+1) * val;
  }

  sprintf(ans, "%d", total);
}
