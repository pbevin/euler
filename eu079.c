#include "euler.h"

struct node {
  char mark, tempmark;
  char used;
  char children[10];
  char parents[10];
};

void visit(struct node *nodes, int n, char *ans) {
  char buf[2];
  if (nodes[n].tempmark) {
    printf("Not a DAG: already visited %d.\n", n);
    exit(1);
  }
  if (!nodes[n].mark) {
    nodes[n].tempmark = 1;
    for (int m = 0; m < 10; m++) {
      if (nodes[n].children[m]) {
        visit(nodes, m, ans);
      }
    }
    nodes[n].mark = 1;
    nodes[n].tempmark = 0;

    buf[0] = n + '0';
    buf[1] = 0;
    strcat(ans, buf);
  }
}

void eu079(char *ans) {
  char *keylog[] = {
    "319", "680", "180", "690", "129", "620", "762", "689", "762", "318", "368",
    "710", "720", "710", "629", "168", "160", "689", "716", "731", "736", "729",
    "316", "729", "729", "710", "769", "290", "719", "680", "318", "389", "162",
    "289", "162", "718", "729", "319", "790", "680", "890", "362", "319", "760",
    "316", "729", "380", "319", "728", "716"
  };

  struct node nodes[10];

  memset(nodes, 0, sizeof(nodes));

  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 2; j++) {
      int this = digittoint(keylog[i][j]);
      int next = digittoint(keylog[i][j+1]);

      nodes[this].children[next] = 1;
      nodes[next].parents[this] = 1;
      nodes[this].used = nodes[next].used = 1;
    }
  }

  ans[0] = 0;
  int didone;
  do {
    didone = 0;
    for (int i = 0; i < 10; i++) {
      if (nodes[i].used && !nodes[i].mark) {
        visit(nodes, i, ans);
        didone = 1;
        break;
      }
    }
  } while(didone);

  strrev(ans);
}
