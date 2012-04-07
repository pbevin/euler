#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>

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

/*
 * Find the smallest number divisible by all integers
 * from 1 to 20.
 *
 * Each integer in the range contributes a factor.
 * Primes contribute themselves. Powers of primes
 * (p^n) contribute the prime (p).  Other composite
 * numbers contribute nothing.  The answer is the
 * product of all the factors.
 *
 * For n=20, the product fits into 32 bits, but I've
 * used a 64-bit type to allow n>20.
 */
void
eu005(char *ans) {
  int n = 20;
  int i, j;
  uint64_t product = 1;
  int *factors = malloc(n * sizeof(int));

  for(i = 2; i < n; i++) {
    int factor = i;
    for (j = 2; j < i; j++) {
      if (factor % factors[j] == 0)
	factor /= factors[j];
    }
    product *= factor;
    factors[i] = factor;
  }
  free(factors);

  sprintf(ans, "%" PRIu64, product);
}

void eu006(char *ans) {
  int n = 100;
  int sum_of_squares = n * (n+1) * (2*n+1) / 6;
  int sum = n * (n+1) / 2;
  int square_of_sums = sum * sum;

  sprintf(ans, "%d", square_of_sums - sum_of_squares);
}

int
is_prime(int n) {
  int i;
  if (n % 2 == 0) return 0;
  for (i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}

/*
 * Find the 10,001st prime.
 *
 * We start at n=2, then check 6k+-1 for primality
 * until we reach n=10001.
 */
void
eu007(char *ans) {
  int n, p;

  n = 2; /* 2 and 3 are primes and we start at 5 */
  p = 5;
  for (;;) {
    if (is_prime(p)) {
      n += 1;
      if (n == 10001) break;
    }
    // p is either 6k-1 or 6k+1;
    // if it's 6k-1, we add 2 to get a 6k+1
    // if it's 6k+1, we add 4 to get a 6k-1
    if ((p + 1) % 6 == 0) {
      p += 2;
    } else {
      p += 4;
    }
  }

  sprintf(ans, "%d", p);
}

#define todigit(ch) ((ch) - '0')

void
eu008(char *ans) {
  const char buf[] = "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
  int max = 0, i;

  for (i = 0; buf[i+4]; i++) {
    int prod = todigit(buf[i]) * todigit(buf[i+1]) * todigit(buf[i+2]) * todigit(buf[i+3]) * todigit(buf[i+4]);
    if (prod > max) {
      max = prod;
    }
  }

  sprintf(ans, "%d", max);
}

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

void eu010(char *ans) {
  const int N = 2000000;
  uint64_t sum = 0;
  char sieve[N];

  gensieve(sieve, N);

  for (int i = 2; i < N; i++) {
    if (!sieve[i]) sum += i;
  }

  sprintf(ans, "%" PRIu64, sum);
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
  { "004", &eu004, "906609" },
  { "005", &eu005, "232792560" },
  { "006", &eu006, "25164150" },
  { "007", &eu007, "104743" },
  { "008", &eu008, "40824" },
  { "009", &eu009, "31875000" },
  { "010", &eu010, "142913828922" },
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
