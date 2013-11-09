#include "euler.h"

struct figurate {
  int k;
  int n;
};

static int p(int k, int n) {
  int b = (k-2)*n + 4 - k;
  return n * b / 2;
}

static struct figurate fs[300];
static int nfs = 0;


static struct figurate byPrefix[100][100];
static int bps[100];

static int solve(struct figurate *soln, int n) {
  int ks[9]; // values of k already seen
  memset(ks, 0, sizeof(ks));
  for (int i = 0; i < n; i++) {
    ks[soln[i].k] = 1;
  }

  int prefix = soln[n-1].n % 100;

  if (n == 6) { // Check if cyclic
    int wanted = soln[0].n / 100;
    return (prefix == wanted);
  }

  // Try numbers starting with the given prefix
  for (int i = 0; i < bps[prefix]; i++) {
    struct figurate *fp = &byPrefix[prefix][i];
    if (ks[fp->k]) continue;  // reject if already seen this k
    soln[n].k = fp->k;
    soln[n].n = fp->n;
    if (solve(soln, n + 1)) {
      return 1;
    }
  }

  return 0;
}

void eu061(char *ans) {
  for (int i = 0; i < 100; i++) {
    bps[i] = 0;
  }

  for (int k = 3; k <= 8; k++) {
    int n;
    for (int i = 3; (n = p(k, i)) < 10000; i++) {
      if (n > 1000 && n % 100 >= 10) {
        struct figurate *fp = &fs[nfs++];
        fp->k = k;
        fp->n = n;

        int prefix = n / 100;
        fp = &byPrefix[prefix][bps[prefix]++];
        fp->k = k;
        fp->n = n;
      }
    }
  }

  struct figurate soln[6];
  for (int i = 0; i < nfs; i++) {
    soln[0].k = fs[i].k;
    soln[0].n = fs[i].n;
    int done = solve(soln, 1);
    if (done) {
      int sum = 0;
      for (int j = 0; j < 6; j++) {
        sum += soln[j].n;
      }
      sprintf(ans, "%d", sum);
      return;
    }
  }
}
