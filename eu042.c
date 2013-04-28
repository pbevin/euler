#include "euler.h"

int istriangle(int num) {
  int i = 1;
  while (num > 0) {
    num -= i;
    i++;
  }
  return (num == 0);
}

/* How many triangle words in words.txt? */
void eu042(char *ans) {
  const int maxwords = 2000;
  char *words[maxwords];
  int count = 0;

  int n = readwords("words.txt", words, maxwords);

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 0; words[i][j]; j++) {
      int ch = words[i][j] - 'A' + 1;
      sum += ch;
    }

    if (istriangle(sum)) {
      count++;
    }
  }

  sprintf(ans, "%d", count);
}
