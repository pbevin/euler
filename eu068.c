#include "euler.h"

static int nodeorder[][3] = {
  { 0, 5, 6 }, { 1, 6, 7}, { 2, 7, 8}, { 3, 8, 9 }, { 4, 9, 5}
};

#define VAL(k) ((k) == '0' ? 10 : (k) - '0')

static int samesum(const char *a) {
  int s1 = VAL(a[0]) + VAL(a[5]) + VAL(a[6]);
  if (VAL(a[1]) + VAL(a[6]) + VAL(a[7]) != s1) return 0;
  if (VAL(a[2]) + VAL(a[7]) + VAL(a[8]) != s1) return 0;
  if (VAL(a[3]) + VAL(a[8]) + VAL(a[9]) != s1) return 0;
  if (VAL(a[4]) + VAL(a[9]) + VAL(a[5]) != s1) return 0;
  return 1;
}

void eu068(char *ans) {
  // Encoding 10 as 0 so we can do string permutations with nextperm()
  char *nval = "9876543210";
  char nodes[11];
  char buf[20];
  ans[0] = 0;

  strcpy(nodes, nval);

  do {
    // For a 16 digit sum, 10 must be in the outer 5 nodes.
    if (index(nodes, '0') >= nodes + 5) continue;
    if (!samesum(nodes)) continue;

    int min = VAL(nodes[0]), mindex = 0;
    for (int i = 1; i < 5; i++) {
      if (VAL(nodes[i]) < min) {
        min = VAL(nodes[i]);
        mindex = i;
      }
    }

    buf[0] = 0;
    int pos = 0;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 3; j++) {
        pos += sprintf(&buf[pos], "%d", VAL(nodes[nodeorder[(i+mindex) % 5][j]]));
      }
    }
    if (strcmp(ans, buf) < 0) {
      printf("%s\n", buf);
      strcpy(ans, buf);
    }
  } while (prevperm(nodes));
}
