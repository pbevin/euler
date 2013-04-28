#include "euler.h"

int num3(char *num, int a) {
  return (num[a] - '0') * 100 + (num[a+1] - '0') * 10 + (num[a+2] - '0');
}

void eu043(char *ans) {
  char num[20];
  long long int sum = 0;

  strcpy(num, "0123456789");

  while (nextperm(num)) {
    if (num3(num, 1) % 2 == 0 &&
        num3(num, 2) % 3 == 0 &&
        num3(num, 3) % 5 == 0 &&
        num3(num, 4) % 7 == 0 &&
        num3(num, 5) % 11 == 0 &&
        num3(num, 6) % 13 == 0 &&
        num3(num, 7) % 17 == 0) {
      sum += atoll(num);
    }
  }

  sprintf(ans, "%lld", sum);
}
