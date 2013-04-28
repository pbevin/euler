#include "euler.h"

/*
 * Find an arithmetic progression of 3 primes
 * that are anagrams in base 10 (other than
 * 1487, 4817, 8147).
 */
int anagram(int a, int b) {
  int digcount[10];
  for (int i = 0; i < 10; i++) digcount[i] = 0;
  while (a > 0) {
    int da = a % 10; a /= 10; digcount[da]++;
    int db = b % 10; b /= 10; digcount[db]--;
  }
  for (int i = 0; i < 10; i++) {
    if (digcount[i] != 0) return 0;
  }
  return 1;
}
void eu049(char *ans) {
  char sieve[10000];
  gensieve(sieve, 10000);

  for (int a = 1488; a < 10000; a++) {
    if (sieve[a]) continue;
    for (int b = a+1; b < 10000; b++) {
      if (sieve[b]) continue;
      if (!anagram(a, b)) continue;
      int c = b + (b-a);
      if (c > 10000 || sieve[c]) continue;
      if (!anagram(b, c)) continue;
      sprintf(ans, "%d%d%d", a, b, c);
      return;
    }
  }
}
