#include "euler.h"

void eu033(char *ans) {
  int a, b;
  int num = 1, den = 1;

  for (a = 10; a < 99; a++) {
    for (b = a+1; b < 99; b++) {
      if (a % 10 == b / 10) {
        float d = (float)a / (float)b;
        float e = (float)(a/10) / (float)(b%10);
        if (d == e) {
          num *= a/10;
          den *= b%10;
        }
      }
    }
  }

  int g = gcd(num, den);
  sprintf(ans, "%d", den / g);
}

