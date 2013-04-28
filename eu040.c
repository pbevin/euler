#include "euler.h"

/*
 * Find the 1, 10, 100, 1000, 10000, 100000 and millionth
 * digits of 123456789101112131415...
 *
 * Starting at place 1, each group of N digits takes up
 * 9N*10^(N-1) places:
 *  1: 9 places
 *  2: 180 places
 *  3: 2700 places
 *  4: 36000 places
 *  5: 450000 places
 *  6: 5400000 places
 *
 * The d[] array contains the cumulative start of each
 * length sequence: 1, 10, 190, ..., and the s[] array
 * contains the start number in the group: 1, 10, 100,
 * 1000, ...
 */
void eu040(char *ans) {
  int places[] = { 1,10,100,1000,10000,100000,1000000, 0 };
  int d[8];
  int s[8];
  int t = 1;
  int p10 = 1;

  int product = 1;

  for (int i = 1; i < 8; i++) {
    d[i] = t;
    s[i] = p10;
    t += 9 * i * p10;
    p10 *= 10;
  }

  for (int i = 0; places[i]; i++) {
    char buf[10];
    int p = places[i];
    int j = 1;
    while (d[j+1] < p) j++;
    /* Now divide the distance from d[j] to p
     * by the length of each number in the group
     * to get the number we're inside.  The variable
     * vd is the number of digits into that number.
     * For example, the 100th digit is 90 digits into
     * the 2-digit group, so it's the 45th number of
     * that group, so v = 10+45 = 55.  Since 90%2 = 0,
     * it's the first digit of 55.
     */
    int v = s[j] + (p - d[j]) / j;
    int vd = (p - d[j]) % j;
    sprintf(buf, "%d", v);
    int digit = buf[vd] - '0';

    product *= digit;
  }

  sprintf(ans, "%d", product);
}
