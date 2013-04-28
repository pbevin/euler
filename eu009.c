#include "euler.h"

void
eu009(char *ans) {
  for (int a = 1; a < 999; a++) {
    for (int b = a; b < 999; b++) {
      int c = 1000 - a - b;
      if (a * a + b * b == c * c) {
        sprintf(ans, "%d", a * b * c);
        return;
      }
    }
  }
  sprintf(ans, "not found");
}
