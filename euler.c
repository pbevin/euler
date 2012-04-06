#include <stdio.h>
#include <memory.h>

void
eu001(char *ans) {
  int t = 0, i;

  for (i = 0; i < 1000; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      t += i;
    }
  }

  sprintf(ans, "%d", t);
}

void
eu002(char *ans) {
  long long t = 0;
  int n, n1, n2;

  n1 = 1;
  n2 = 1;

  while ((n = n1 + n2) < 4000000) {
    n2 = n1;
    n1 = n;
    if (n % 2 == 0) {
      t += n;
    }
  }

  sprintf(ans, "%lld", t);
}

/*
 * Mark elements of sieve according to whether they
 * are prime or composite, up to position n.  Primes
 * are marked with 0, composites with 1.
 */
void
gensieve(char *sieve, int n) {
  int i, j;

  memset(sieve, 0, n);

  for (i = 2; i < n; i++) {
    if (sieve[i] == 0) {
      for (j = i + i; j < n; j += i) {
	sieve[j] = 1;
      }
    }
  }
}


/* Find the largest prime factor of 600851475143.
 * We generate primes up to sqrt(num) ~= 775146
 * and then test each one for divisibility.
 */
void
eu003(char *ans) {
  long long num = 600851475143;
  char sieve[775146];
  int i;

  gensieve(sieve, sizeof(sieve));
  for (i = 775143; i > 2; i -= 2) {
    if (sieve[i] == 0 && num % i == 0) {
      sprintf(ans, "%d", i);
      return;
    }
  }
}

int
is_palindrome(int n) {
  char buf[100];
  int i;
  int len;
  len = sprintf(buf, "%d", n);
  
  for (i = 0; i < len/2; i++) {
    if (buf[i] != buf[len-i-1]) return 0;
  }
  return 1;
}

/* Find the largest palindrome that is the product
 * of two 3-digit numbers
 */
void
eu004(char *ans) {
  int largest = 0;
  int i, j;

  for (i = 100; i < 1000; i++) {
    for (j = i; j < 1000; j++) {
      int product = i * j;
      if (product > largest && is_palindrome(product)) {
	largest = product;
      }
    }
  }

  sprintf(ans, "%d", largest);
}

typedef void (solver)(char *ans);
struct puzzle {
  const char *name;
  solver *fn;
  const char *ans;
};

struct puzzle puzzles[] = {
  { "001", &eu001, "233168" },
  { "002", &eu002, "4613732" },
  { "003", &eu003, "6857" },
  { "004", &eu004, "906609" }
};

#define NPUZZLES (sizeof puzzles / sizeof(puzzles[0]))

#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define RED "\e[31m"
#define RESET "\e[39m"

int
main(int argc, char *argv[]) {
  int i;
  char ansbuf[1024];

  for (i = 0; i < NPUZZLES; i++) {
    struct puzzle *puz = &puzzles[i];

    memset(ansbuf, 0, sizeof(ansbuf));
    (puz->fn)(ansbuf);

    if (puz->ans == 0) {
      printf("%sXX %s%s: %s\n", YELLOW, puz->name, RESET, ansbuf);
    } else if (strcmp(ansbuf, puz->ans) == 0) {
      printf("%sOK %s%s: %s\n", GREEN, puz->name, RESET, puz->ans);
    } else {
      printf("%sNO %s%s: %s (ans: %s)\n", RED, puz->name, RESET, ansbuf, puz->ans);
    }
  }
  return 0;
}
