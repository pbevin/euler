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

int prod4(int a[20][20], int di, int dj) {
  int max = 0;
  int si = di < 0 ? 3 : 0;
  for (int i = si; i < 20 && i + 3*di < 20; i++) {
    for (int j = 0; j + 3*dj < 20; j++) {
      int prod = a[i][j] * a[i+di][j+dj] * a[i+di*2][j+dj*2] * a[i+di*3][j+dj*3];
      if (prod > max) max = prod;
    }
  }
  return max;
}

void eu011(char *ans) {
  const char *grid[] = {
    "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08",
    "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00",
    "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65",
    "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91",
    "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80",
    "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50",
    "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70",
    "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21",
    "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72",
    "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95",
    "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92",
    "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57",
    "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58",
    "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40",
    "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66",
    "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69",
    "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36",
    "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16",
    "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54",
    "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48"
  };
  int a[20][20];

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      sscanf(grid[i] + 3 * j, "%d", &a[i][j]);
    }
  }

  int p1 = prod4(a, 0, 1); // vertical
  int p2 = prod4(a, 1, 0); // horizontal
  int p3 = prod4(a, 1, 1); // vertical down-right
  int p4 = prod4(a, -1, 1); // vertical up-right
  
  int p = p1;
  if (p2 > p) p = p2;
  if (p3 > p) p = p3;
  if (p4 > p) p = p4;

  sprintf(ans, "%d", p);
}

/* Count the divisors of n.  We use the trick that
 * divisors are symmetric: if d is a divisor, then
 * so is n/d, so we only have to count up to the
 * square root of n.
 */
int divisors(int n) {
  int count = 0, i;
  for (i = 1; i * i < n; i++) {
    if (n % i == 0) count += 2;
  }
  /* If n is a square, then sqrt(n) is a divisor
   * that has no pair. */
  if (i * i == n) count += 1;
  return count;
}

void eu012(char *ans) {
  int n = 0;
  
  for (int i = 1; ; i++) {
    int ndiv;
    n += i;
    ndiv = divisors(n);
    if (ndiv > 500) {
      sprintf(ans, "%d", n);
      return;
    }
  }
}

void
readnum(char *num, FILE *fp) {
  char buf[100];
  int k = 0;
  char *p = fgets(buf, 100, fp);
  if (p != 0) {
    for (int j = strlen(p) - 1; j >= 0; j--) {
      num[k] = p[j] - '0';
      k++;
    }
  }
  while (k < 100) num[k++] = 0;
}

void add(char *dst, char *src, int n) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    int d = dst[i] + src[i] + c;
    dst[i] = d % 10;
    c = d / 10;
  }
}

void eu013(char *ans) {
  FILE *fp = fopen("eu013.txt", "r");
  char sum[100];
  char num[100];

  memset(sum, 0, 100);

  for (int i = 0; i < 100; i++) {
    readnum(num, fp);
    add(sum, num, 100);
  }

  fclose(fp);

  for (int i = 99; i >= 0; i--) {
    if (sum[i] > 0) {
      for (int j = 0; j < 10; j++) {
	ans[j] = sum[i-j] + '0';
      }
      ans[10] = 0;
      return;
    }
  }
}

int
collatz(long long n, int *a, int max) {
  if (n == 1) {
    return 1;
  } else if (n < max && a[n] > 0) {
    return a[n];
  } else {
    long long next;
    int c;
    if (n % 2 == 0) {
      next = n / 2;
    } else {
      next = 3 * n + 1;
    }
    c = collatz(next, a, max);
    if (n < max)
      a[n] = c + 1;
    return c + 1;
  }
}


void eu014(char *ans) {
  const int N = 1000000;
  int a[N];
  int max = 0, nmax;

  memset(a, 0, sizeof(a));

  for (int i = 2; i < N; i++) {
    int count = collatz(i, a, N);
    if (count > max) {
      max = count;
      nmax = i;
    }
  }

  sprintf(ans, "%d", nmax);
}

/*
 * The answer in general is (2n)choose(n).
 * In our case, it's (40! / 20!20!)
 * We can calculate it using Pascal's Triangle.
 */
void eu015(char *ans) {
  const int N = 20;
  long long a[N*2+2][N*2+2];

  memset(a, 0, sizeof(a));
  a[0][0] = 1;
  a[0][1] = 0;
  for (int i = 1; i < N*2+2; i++) {
    a[i][0] = 1;
    for (int j = 1; j < i; j++) {
      a[i][j] = a[i-1][j-1] + a[i-1][j];
    }
    a[i][i+1] = 0;
  }
  sprintf(ans, "%lld", a[41][20]);
}

void eu016(char *ans) {
  const int N = 1000;
  char num[N];
  int i, t;
  
  memset(num, 0, N);
  num[0] = 1;

  for (i = 0; i < N; i++) {
    add(num, num, N);
  }

  for (t = 0, i = 0; i < N; i++) {
    t += num[i];
  }

  sprintf(ans, "%d", t);
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
  { "011", &eu011, "70600674" },
  { "012", &eu012, "76576500" },
  { "013", &eu013, "5537376230" },
  { "014", &eu014, "837799" },
  { "015", &eu015, "137846528820" },
  { "016", &eu016, "1366" },
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
