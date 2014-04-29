#include "euler.h"

struct permbase {
  long long int signature;
  long long int firstCube;
  int count;
};

#define MAXNB 10000
static struct permbase bs[MAXNB];
static int nbs = 0;

static long long int cube(long long int n) {
  return n * n * n;
}

static int ccmp(const void *a, const void *b) {
  const char *ca = a;
  const char *cb = b;
  return *ca - *cb;
};

static long long int signature(long long int n) {
  static char buf[30], buf2[30];
  long long int ans;

  sprintf(buf, "%lld", n);
  int len = strlen(buf);
  qsort(buf, len, 1, ccmp);
  sprintf(buf2, "%d%s", len, buf);
  sscanf(buf2, "%lld", &ans);
  return ans;
}

void eu062(char *ans) {
  for (long long int i = 100; nbs < MAXNB; i++) {
    long long int sig = signature(cube(i));
    for (int j = 0; j < nbs; j++) {
      if (bs[j].signature == sig) {
        bs[j].count++;
        break;
      }
    }

    struct permbase *p = &bs[nbs++];
    p->signature = sig;
    p->firstCube = i;
    p->count = 1;
  }

  for (int i = 0; i < nbs; i++) {
    if (bs[i].count == 5) {
      sprintf(ans, "%lld", cube(bs[i].firstCube));
      return;
    }
  }
}
