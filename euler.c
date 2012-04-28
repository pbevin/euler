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

  sieve[0] = 1;
  sieve[1] = 1;
  memset(sieve+2, 0, n-2);

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

/* Add up the divisors of n, not counting n itself.
 * Same trick as divisors().
 */
int sumdivisors(int n) {
  int sum = 1, i;
  for (i = 2; i * i < n; i++) {
    if (n % i == 0) sum += i + n/i;
  }
  if (i * i == n) sum += i;
  return sum;
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

void mul1(char *dst, int a, int n) {
  int c = 0;
  for (int i = 0; i < n; i++) {
    int d = dst[i] * a + c;
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

/*
 * Count the letters in 1..1000.
 *
 * 1..9 is "onetwothreefourfivesixseveneightnine" - 36 chars.
 * 10..19 is "teneleventwelvethirteenfourteenfifteensixteenseventeeneighteennineteen"
 *        - 70 chars.
 * 20..29 is ten "twenty"s plus length of 1..9, which is 10*6 + 36 = 96
 * 30..99 is ten "thirtyfortyfiftysixtyseventyeightyninety" plus seven "1..9"s,
 *    which is (40*10) + (7*36) = 652
 * So in total, 1..99 is 36+70+96+652 = 854.
 *
 * For 100..999, each century has "N hundred" plus "N hundred and" * 99 plus the 854
 * of 1..99, which is N*100 + 7 + 10*99 + 854 = N*100 + 1851.
 *
 * So 100..999 is 36*100+1851*9 = 20259
 * and 1000 is "onethousand" = 11
 *
 * so 1..1000 is 854+20259+11 = 21124
 */
void eu017(char *ans) {
  sprintf(ans, "21124");
}

int max(int x, int y) {
  if (x > y)
    return x;
  else
    return y;
}

void eu018(char *ans) {
  const int N = 15;
  char data[] = "\
75 \
95 64 \
17 47 82 \
18 35 87 10 \
20 04 82 47 65 \
19 01 23 75 03 34 \
88 02 77 73 07 63 67 \
99 65 04 28 06 16 70 92 \
41 41 26 56 83 40 80 70 33 \
41 48 72 33 47 32 37 16 94 29 \
53 71 44 65 25 43 91 52 97 51 14 \
70 11 33 28 77 73 17 78 39 68 17 57 \
91 71 52 38 17 14 91 43 58 50 27 29 48 \
63 66 04 68 89 53 67 30 73 16 69 87 40 31 \
04 62 98 27 23 09 70 98 73 93 38 53 60 04 23";
  int n = 0;
  int maxima[N];
  int row[N];

  memset(maxima, 0, sizeof(maxima));
  for (int i = 0; i < N; i++) {
    int newmax[N];
    memset(newmax, 0, sizeof(newmax));
    memset(row, 0, sizeof(row));
    for (int j = 0; j <= i; j++) {
      row[j] = atoi(data + 3 * n);
      n++;
    }
    newmax[0] = maxima[0] + row[0];
    for (int j = 0; j < i; j++) {
      newmax[j + 1] = max(maxima[j], maxima[j+1]) + row[j + 1];
    }
    newmax[i] = maxima[i-1] + row[i];
    memcpy(maxima, newmax, sizeof(maxima));
  }

  int best = 0;
  for (int i = 0; i < N; i++) {
    if (maxima[i] > best) best = maxima[i];
  }
  sprintf(ans, "%d", best);
}

/*
 * Jan 1, 1900 was a Monday
 * Find Sundays on the first of the month from
 * Jan 1, 1901 to
 * Dec 31, 2000
 *
 * We use Sun => 0, Mon => 1, ..., Sat => 7.
 */
int countsun(int *days_in_month, int day, int *newday) {
  // Return the number of Sundays in the year, and
  // modify newday to be the day of the week on Jan 1
  // of the next year.
  int count = 0;
  for (int i = 0; i < 12; i++) {
    if (day == 0) count++;
    day += days_in_month[i];
    day %= 7;
  }
  *newday = day;
  return count;
}

void eu019(char *ans) {
  int day;
  int count;
  int days[]   = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int daysly[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  /* 1900 was NOT a leap year, but 2000 was. */
  countsun(days, 1, &day);
  count = 0; /* Not counting 1900 */
  for (int yr = 1901; yr <= 2000; yr++) {
    if (yr % 4 == 0) {
      count += countsun(daysly, day, &day);
    } else {
      count += countsun(days, day, &day);
    }
  }

  sprintf(ans, "%d", count);
}

/* Sum of digits of 1000! */
void eu020(char *ans) {
  const int N = 100;
  char fact[1000];

  memset(fact, 0, sizeof(fact));
  fact[0] = 1;

  for (int i = 2; i < N; i++) {
    mul1(fact, i, 1000);
  }

  int t = 0;
  for (int i = 0; i < 1000; i++) {
    t += fact[i];
  }
  sprintf(ans, "%d", t);
}

/* Add up all amicable numbers under 10,000 */
void eu021(char *ans) {
  const int N = 10000;
  int ds[N];

  for (int i = 1; i < N; i++) {
    ds[i] = sumdivisors(i);
  }

  int sum = 0;
  for (int i = 1; i < N; i++) {
    if (ds[i] < N && i != ds[i] && ds[ds[i]] == i) {
      sum += i;
    }
  }

  sprintf(ans, "%d", sum);
}


int readwords(const char *filename, char **words, int maxwords) {
  FILE *fp = fopen(filename, "r");
  if (fp == 0) {
    perror(filename);
    abort();
  }
  static char buf[50000];
  char *p = fgets(buf, sizeof(buf), fp);
  fclose(fp);

  int i = 0;
  for (;;) {
    while (*p == '"') p++;
    words[i++] = p;
    while (*p != '"') p++;
    *p++ = 0;
    if (*p == 0) break;
    p++; /* skip comma */
    if (*p != '"') break;
  }
  return i;
}

int namesort(const void *a, const void *b) {
  return strcmp(* (char * const *) a, * (char * const *) b);
}

void eu022(char *ans) {
  const int maxwords = 8000;
  char *names[maxwords];
  int n = readwords("names.txt", names, maxwords);

  qsort(names, n, sizeof(char *), namesort);

  int total = 0;
  for (int i = 0; i < n; i++) {
    int val = 0;
    for (char *p = names[i]; *p; p++) {
      val += *p - 'A' + 1;
    }
    total += (i+1) * val;
  }

  sprintf(ans, "%d", total);
}

void eu023(char *ans) {
  int N = 28123;
  int abundant[N];
  char issum[N];
  int nabun = 0;

  memset(abundant, 0, sizeof(abundant));
  memset(issum, 0, sizeof(issum));

  for (int i = 2; i < N; i++) {
    if (sumdivisors(i) > i) {
      abundant[nabun++] = i;
    }
  }

  for (int i = 0; i < nabun; i++) {
    for (int j = 0; j <= i; j++) {
      int sum = abundant[i] + abundant[j];
      if (sum < N) {
	issum[sum] = 1;
      }
    }
  }

  int total = 0;
  for (int i = 1; i < N; i++) {
    if (!issum[i]) {
      total += i;
    }
  }

  sprintf(ans, "%d", total);
}


/* http://stackoverflow.com/a/362714 */
void genperm(char *ans, const char *xs, int len, const int perm, const int *fact) {
  if (len == 1) {
    *ans = xs[0];
    return;
  }

  char *buf = malloc(len);
  int p = (perm / fact[len - 1]) % len;
  *ans = xs[p];

  char *bp = buf;
  for (int i = 0; i < len; i++) {
    if (i != p) *bp++ = xs[i];
  }
  genperm(ans + 1, buf, len - 1, perm % fact[len-1], fact);
  free(buf);
}

void eu024(char *ans) {
  const int N = 10;
  const int perm = 1000000;
  int fact[N];

  for (int n = 1, i = 1; i < N; i++) {
    fact[i] = n;
    n *= i+1;
  }

  genperm(ans, "0123456789", 10, perm-1, fact);
}

void eu025(char *ans) {
  const int N = 1000;
  int n = 2;
  char a1[N], a2[N], a3[N];

  memset(a1, 0, N);
  memset(a2, 0, N);
  a1[0] = 1;
  a2[0] = 1;

  for (;;) {
    n++;
    memcpy(a3, a1, N);
    add(a3, a2, N);
    if (a3[N-1]) {
      sprintf(ans, "%d", n);
      return;
    }
    memcpy(a1, a2, N);
    memcpy(a2, a3, N);
  }
}

/*
 * Find the value of d < 1000 for which 1/d has the longest
 * recurring cycle in decimal.
 *
 * The length of the cycle is the smallest n for which
 *   10^n === 1 (mod d)
 * as long as d is relatively prime to 10.  (If not relatively
 * prime, then a smaller d has the same cycle length).
 */
int mulord(int b, int d) {
  int n = b % d;
  int iter = 1;

  while (n != 1) {
    n = (n * b) % d;
    iter++;
  }
  return iter;
}
void eu026(char *ans) {
  int d;
  int maxlen = 0;
  for (int i = 3; i < 1000; i++) {
    if (i % 2 != 0 && i % 5 != 0) {
      int len = mulord(10, i);
      if (len > maxlen) {
	d = i;
	maxlen = len;
      }
    }
  }

  sprintf(ans, "%d", d);
}

/*
 * Find the best generator of primes g(n) = n^2+an+b where
 * |a| < 1000 and |b| < 1000.
 *
 * Clearly, b has to be at least 2, otherwise g(0) is not prime.
 *
 * Also, 1+a+b >= 2 (since g(1) is prime), so a >= 1-b.
 *
 * Also, g(b) is not prime, so the sequence can't be longer
 * than 1000, so we only have to consider primes up to
 * 2,001,000 (a^2+a^2+b).
 */
void eu027(char *ans) {
  const int MAXPRIME = 2001000;
  char sieve[MAXPRIME];
  int max = 0;
  int max_ab;

  gensieve(sieve, MAXPRIME);

  for (int b = -999; b < 1000; b++) {
    for (int a = -999; a < 1000; a++) {
      int n = 0;
      while (n < b) {
	int f_n = n*n + a*n + b;
	if (f_n < 2 || f_n >= MAXPRIME || sieve[f_n]) {
	  break;
	}
	n++;
      }

      /*
       * At this point, n is the minimum for which f_n is composite.
       * Subtracting 1 makes it the maximum for which f_n is prime.
       */
      n--;

      if (n > max) {
	max = n;
	max_ab = a * b;
      }
    }
  }

  sprintf(ans, "%d", max_ab);
}

/*
 * Sum of numbers on square spiral's diagonals
 * Each ring of side 2n+1 (after the first) has
 * perimeter 8n, and the 4 numbers are:
 *   v+2n (SE), v+4n (SW), v+6n (NW), v+8n (NE)
 * where v = (2n-1)^2.
 *
 * So the contribution of ring n is v+20n
 *   = 4*(2n-1)^2 + 20n
 *   = 16n^2 - 16n + 4 + 20n
 *   = 16n^2 + 4n + 4
 *   = 4(4n^2 + n + 1)
 *
 * For example, the ring with side 5 has v=9, and
 * diagonals 13, 17, 21 and 25, and its contribution
 * is 13+17+21+25 = 76 (= 4(16+4+1) )
 *
 * We just add these up from 1 to 500 and add 1 for
 * the inner singleton to get the answer.
 */
void eu028(char *ans) {
  const int N = 1001;
  int t = 1;

  for (int n = 1; n <= (N-1)/2; n++) {
    t += 4*(4*n*n + n + 1);
  }

  sprintf(ans, "%d", t);
}

/*
 * How many distinct values of a^b are there for
 * 2 <= a, b < 100 ?
 *
 * Well I'm not bloody calculating them all, that's
 * for sure.
 *
 * If we represent each a^b as prime factors, it'll
 * be easy: factorize a into a vector of prime factors,
 * multiply each one by b, and check if we've already
 * seen it.
 *
 * For example, 76 = 2^2 * 19, which we'll represent as
 *   [2,0,0,0,0,0,0,1]
 * and so 76^31 is
 *   [62,0,0,0,0,0,0,31]
 *
 * There are only 10,000 numbers to check, so we can
 * just keep them in an array.
 */
void eu029(char *ans) {
  int primes100[25] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
    53, 59, 61, 67, 71, 73, 79, 83, 89, 97
  };

  int seen[10000][25];
  int nseen = 0;

  int factors[25];

  for (int a = 2; a <= 100; a++) {
    for (int i = 0; i < 25; i++) {
      int n = a;
      int p = primes100[i], k = 0; /* n has factor p^k */
      while (n % p == 0) {
	k++;
	n /= p;
      }
      factors[i] = k;
    }

    for (int b = 2; b <= 100; b++) {
      for (int i = 0; i < 25; i++) {
	seen[nseen][i] = factors[i] * b;
      }

      int isduplicate = 0;
      for (int j = 0; j < nseen; j++) {
	if (memcmp(seen[j], seen[nseen], sizeof(int[25])) == 0) {
	  isduplicate = 1;
	  break;
	}
      }
      if (!isduplicate) {
	nseen++;
      }
    }
  }
  sprintf(ans, "%d", nseen);
}

/*
 * Find all numbers that can be written as the sum of the
 * fifth power of their digits.
 *
 * We only have to check up to 413343 = 9^5 * 6, since the
 * digit sum is less than the number for anything larger.
 */
void eu030(char *ans) {
  int fp[10] = { 0, 1, 32, 243, 1024, 3125, 7776, 16807, 32768, 59049 };
  int t = 0;

  for (int n = 10; n < 413344; n++) {
    int digit5sum = 0;
    int v = n;
    while (v > 0) {
      int d = v % 10;
      v = v / 10;
      digit5sum += fp[d];
    }
    if (digit5sum == n) {
      t += n;
    }
  }

  sprintf(ans, "%d", t);
}

/*
 * How many ways can you make 200 using coins
 * 1,2,5,10,20,50,100,200?
 *
 * Let a(i,x) be the number of ways of making up x using
 * only the first i denominations.
 *
 * Then a(1,x) = 1, and
 *   a(i+1,x) = a(i,x) + a(i+1,x-v(i)).
 * (e.g., to make up 13p using 1, 2 and 5, you can either
 * not use a 5 at all a(i,x) ways, or make 8p and add a 5.
 */
void eu031(char *ans) {
  const int N = 200;
  int coins[8] = { 1,2,5,10,20,50,100,200 };
  int a[N+1];

  for (int k = 0; k <= N; k++) a[k] = 1;

  for (int i = 1; i < 8; i++) {
    int v = coins[i];
    for (int k = v; k <= N; k++) {
      a[k] += a[k-v];
    }
  }

  sprintf(ans, "%d", a[N]);
}


void swap(char *a, char *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

char *
nextperm(char *s) {
  int i, j, len = strlen(s);

  for (i = len-2; i >= 0; i--) {
    if (s[i] < s[i+1]) break;
  }
  if (i == -1) return 0;

  for (j = len-1; j > i; j--) {
    if (s[j] > s[i]) break;
  }
  swap(&s[i], &s[j]);

  i++; j = len - 1;
  while (i < j) swap(&s[i++], &s[j--]);

  return s;
}

char *
prevperm(char *s) {
  int i, j, len = strlen(s);

  for (i = len-2; i >= 0; i--) {
    if (s[i] > s[i+1]) break;
  }
  if (i == -1) return 0;

  for (j = len-1; j > i; j--) {
    if (s[j] < s[i]) break;
  }
  swap(&s[i], &s[j]);

  i++; j = len - 1;
  while (i < j) swap(&s[i++], &s[j--]);

  return s;
}

int
subint(char *s, int i, int j) {
  int t = 0;
  char *p = s + i;
  while (p < s + j) {
    t *= 10;
    t += *p++ - '0';
  }
  return t;
}

/*
 * Find all products that are a permutation of 1..9
 * e.g., 39 * 186 = 7254.
 */
void eu032(char *ans) {
  char buf[12], *s = buf;
  strcpy(s, "123456789");
  int len = strlen(s);
  int seen[1000];
  int nseen = 0;
  int t = 0;

  while (s) {
    for (int i = 1; i < len-1; i++) {
      for (int j = i+1; j < len; j++) {
	int a = subint(s, 0, i);
	int b = subint(s, i, j);
	int c = subint(s, j, len);

	if (a * b == c) {
	  int seenit = 0;
	  for (int k = 0; k < nseen; k++) {
	    if (c == seen[k]) {
	      seenit++;
	      break;
	    }
	  }
	  if (!seenit) {
	    seen[nseen++] = c;
	  }
	}
      }
    }
    s = nextperm(s);
  }

  for (int i = 0; i < nseen; i++) {
    t += seen[i];
  }

  sprintf(ans, "%d", t);
}

int gcd(int a, int b) {
  int t;
  if (a > b) {
    t = a;
    a = b;
    b = t;
  }

  while (b > 0) {
    t = b;
    b = a % b;
    a = t;
  }
  return a;
}

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

/* Find numbers that are the sum of the factorial
 * of their digits.
 *
 * The highest possible number is 9!*7 = 2,540,160.
 */
void eu034(char *ans) {
  int fact[10];
  int total = 0;

  fact[0] = 1;
  for (int i = 1, t=1; i < 10; i++) {
    t *= i;
    fact[i] = t;
  }

  for (int i = 10; i <= 2540160; i++) {
    int sum = 0;
    int n = i;

    while (n > 0) {
      int d = n % 10;
      n /= 10;
      sum += fact[d];
    }
    if (sum == i) {
       total += sum;
    }
  }
  sprintf(ans, "%d", total);
}

/*
 * How many circular primes are there under a million?
 *
 * A circular prime is one where every rotation of the
 * digits is prime - e.g, 197->971->719.
 * We are given that there are 13 such primes under 100.
 *
 * Clearly we only need to consider numbers containing
 * digits 1,3,7 and 9: no rotation can be a multiple of
 * 2 or 5.
 */
int chkcirc(int lo, int hi, int len, char *sieve) {
  int count = 0;
  int m = 1;

  for (int i = 0; i < len-1; i++) {
    m *= 10;
  }

  for (int i = lo; i < hi; i += 2) {
    int is_circular_prime = 1;
    int n = i;
    for (int j = 0; j < len; j++) {
      if (sieve[n]) {
	is_circular_prime = 0;
	break;
      }
      int d = n % 10;
      n /= 10;
      n += m * d;
    }

    if (is_circular_prime) {
      count++;
    }
  }
  return count;
}

void eu035(char *ans) {
  int sum = 13;
  char *sieve = malloc(1000000);
  gensieve(sieve, 1000000);
  sum += chkcirc(111, 1000, 3, sieve);
  sum += chkcirc(1111, 10000, 4, sieve);
  sum += chkcirc(11111, 100000, 5, sieve);
  sum += chkcirc(111111, 1000000, 6, sieve);

  free(sieve);

  sprintf(ans, "%d", sum);
}

int ispalindrome(char *a) {
  int i = 0, j = strlen(a) - 1;
  while (i < j) {
    if (a[i++] != a[j--])
      return 0;
  }
  return 1;
}

void base2(int n, char *a) {
  while (n) {
    *a++ = (n % 2 == 0) ? '0' : '1';
    n /= 2;
  }
  *a = 0;
}

/*
 * Sum of all numbers < 1,000,000 that are palindromic
 * in base 10 and base 2.
 */
void eu036(char *ans) {
  char buf[30];
  int t = 0;

  for (int i = 1; i < 1000000; i++) {
    sprintf(buf, "%d", i);
    if (ispalindrome(buf)) {
      base2(i, buf);
      if (ispalindrome(buf)) {
	t += i;
      }
    }
  }

  sprintf(ans, "%d", t);
}

/*
 * Find all 11 primes that are also prime when
 * truncated left or right.
 *
 * The first digit can be 2,3,5,7, the last must be 3,7 or 9,
 * and the remainder can be 1,3,7,9.
 *
 * There isn't an obvious upper bound, but we can just keep
 * going until we find 11 of them.
 *
 * We generate the numbers by increasing a counter
 * and decoding it in kinda base 4: 1,3,7,9, 11,13,17,19,
 * 31,33,37,39, ... - actually reversed for convenience but
 * we're just enumerating so that's OK.  Since we actually
 * want to start with 11, we'll start with n=4.
 */
void eu037(char *ans) {
  int MAX = 1000000;
  int digits1[] = {2,3,5,7};
  int digits[] = {1,3,7,9};
  int count = 0, sum = 0;
  int n = 4;
  char *sieve = malloc(MAX);

  gensieve(sieve, MAX);

  while (count < 11) {
    int j = n, val, istrunc = 1;

    val = digits1[j % 4];
    j /= 4;

    while (j) {
      val *= 10;
      val += digits[j % 4];
      j /= 4;
    }
    if (val >= MAX) {
      fprintf(stderr, "Too high, count = %d\n", count);
      return;
    }

    /* find right-truncations */
    j = val;
    while (j > 0) {
      if (sieve[j]) {
	istrunc = 0;
	break;
      }
      j /= 10;
    }

    /* find left-truncations */
    char buf[30];
    sprintf(buf, "%d", val);
    for (char *p = buf; *p; p++) {
      int j = atoi(p);
      if (sieve[j]) {
	istrunc = 0;
	break;
      }
    }

    if (istrunc) {
      sum += val;
      count++;
    }

    n++;
  }

  free(sieve);

  sprintf(ans, "%d", sum);
}

int ispandigital(char *prod) {
  char seen[10];
  char *p = prod;
  memset(seen, 0, 10);
  while (*p) {
    int d = *p - '0';
    if (d == 0 || seen[d]) {
      return 0;
    }
    seen[d] = 1;
    p++;
  }
  return 1;
}

void eu038(char *ans) {
  int max = 0;
  for (int i = 0; i < 54321; i++) {
    char prod[20];
    int k = 1;
    int len;
    prod[0] = 0;
    while ((len = strlen(prod)) < 9) {
      sprintf(prod + len, "%d", i * k);
      k++;
    }
    if (len == 9 && ispandigital(prod)) {
      int n = atoi(prod);
      if (n > max) max = n;
    }
  }
  sprintf(ans, "%d", max);
}

/* What number a+b+c under 1000 has the maximum integer
 * solutions to a^2+b^2=c^2 ?
 */

void eu039(char *ans) {
  int count[1001];

  memset(count, 0, sizeof(count));

  for (int c = 1; c < 1000; c++) {
    for (int b = 1; b <= c && b+c <= 1000; b++) {
      for (int a = 1; a <= b && a+b+c <= 1000; a++) {
	// Sides are a < b < c
	if (a*a + b*b == c*c) {
	  count[a+b+c]++;
	}
      }
    }
  }

  int max = 0, a;
  for (int i = 0; i < 1000; i++) {
    if (count[i] > max) {
      max = count[i];
      a = i;
    }
  }
  sprintf(ans, "%d", a);
}

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

/*
 * Largest pandigital prime.
 *
 * No 8- or 9-digit pandigital can be prime, since the digit sum is
 * 36 or 45, which makes it divisible by 3.  So we'll just generate
 * the permutations of 1..7 in reverse until we find one.
 */

void eu041(char *ans) {
  char *sieve = malloc(7654324);
  char *p;
  gensieve(sieve, 7654324);

  strcpy(ans, "7654321");

  while ((p = prevperm(ans)) != 0) {
    int v = atoi(ans);
    if (!sieve[v]) return;
  }
}

int istriangle(int num) {
  int i = 1;
  while (num > 0) {
    num -= i;
    i++;
  }
  return (num == 0);
}

/* How many triangle words in words.txt? */
void eu042(char *ans) {
  const int maxwords = 2000;
  char *words[maxwords];
  int count = 0;

  int n = readwords("words.txt", words, maxwords);

  for (int i = 0; i < n; i++) {
    int sum = 0;
    for (int j = 0; words[i][j]; j++) {
      int ch = words[i][j] - 'A' + 1;
      sum += ch;
    }

    if (istriangle(sum)) {
      count++;
    }
  }

  sprintf(ans, "%d", count);
}

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
  { "017", &eu017, "21124" },
  { "018", &eu018, "1074" },
  { "019", &eu019, "171" },
  { "020", &eu020, "648" },
  { "021", &eu021, "31626" },
  { "022", &eu022, "871198282" },
  { "023", &eu023, "4179871" },
  { "024", &eu024, "2783915460" },
  { "025", &eu025, "4782" },
  { "026", &eu026, "983" },
  { "027", &eu027, "-59231" },
  { "028", &eu028, "669171001" },
  { "029", &eu029, "9183" },
  { "030", &eu030, "443839" },
  { "031", &eu031, "73682" },
  { "032", &eu032, "45228" },
  { "033", &eu033, "100" },
  { "034", &eu034, "40730" },
  { "035", &eu035, "55" },
  { "036", &eu036, "872187" },
  { "037", &eu037, "748317" },
  { "038", &eu038, "932718654" },
  { "039", &eu039, "840" },
  { "040", &eu040, "210" },
  { "041", &eu041, "7652413" },
  { "042", &eu042, "162" },
  { "043", &eu043, "16695334890" },
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
