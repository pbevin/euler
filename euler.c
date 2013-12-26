#include "euler.h"

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

  for (i = 2; i * i < n; i++) {
    if (sieve[i] == 0) {
      for (j = i * i; j < n; j += i) {
        sieve[j] = 1;
      }
    }
  }
}

/*
 * Generate primes below n
 */
int genprimes(int *primes, int n) {
  char *sieve = malloc(n);
  gensieve(sieve, n);

  primes[0] = 2;
  int nprimes = 1;

  for (int i = 3; i < n; i += 2) {
    if (sieve[i] == 0) primes[nprimes++] = i;
  }

  free(sieve);
  return nprimes;
}


/*
 * Check one number for primality.
 * Some problems need primes up to ~1billion, so the sieve
 * isn't practical without better data compression.
 */
int isprime(int n) {
  if (n == 1)
    return 0;
  else if (n == 2 || n == 3 || n == 5)
    return 1;
  else if (n == 1 || n % 2 == 0 || n % 3 == 0 || n % 5 == 0) {
    return 0;
  }
  for (int i = 7; i * i <= n; i += 2) {
    if (n % i == 0) {
      return 0;
    }
  }
  return 1;
}

/*
 * Generate phi(n) up to max.
 */
void genphi(int *phi, int max) {
  for (int i = 2; i < max; i++) {
    phi[i] = i;
  }

  for (int i = 2; i < max; i++) {
    if (phi[i] == i) {
      // i is prime
      for (int j = i; j < max; j += i) {
        // phi[j] is definitely divisible by i.
        phi[j] = phi[j] / i * (i-1);
      }
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


int
is_prime(int n) {
  int i;
  if (n % 2 == 0) return 0;
  for (i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return 0;
  }
  return 1;
}



int max(int x, int y) {
  if (x > y)
    return x;
  else
    return y;
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


int digitsum(mpz_t z) {
  static char buf[10000];
  char *p = mpz_get_str(buf, 10, z);
  int digitsum = 0;
  for (int i = 0; p[i]; i++) {
    digitsum += todigit(p[i]);
  }
  return digitsum;
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


int charcmp(const void *a, const void *b) {
  const char *aa = a;
  const char *bb = b;
  return *aa - *bb;
}

void digitsort(char *buf, int n) {
  sprintf(buf, "%d", n);
  qsort(buf, strlen(buf), 1, charcmp);
}

int isperm(int a, int b) {
  /* if (10*a < b || 10*b < a) { */
  /*   return 0; */
  /* } */
  char abuf[20], bbuf[20];
  digitsort(abuf, a);
  digitsort(bbuf, b);
  return strcmp(abuf, bbuf) == 0;
}

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
  { "044", &eu044, "5482660" },
  { "045", &eu045, "1533776805" },
  { "046", &eu046, "5777" },
  { "047", &eu047, "134043" },
  { "048", &eu048, "9110846700" },
  { "049", &eu049, "296962999629" },
  { "050", &eu050, "997651" },
  { "051", &eu051, "121313" },
  { "052", &eu052, "142857" },
  { "053", &eu053, "4075" },
  { "054", &eu054, "376" },
  { "055", &eu055, "249" },
  { "056", &eu056, "972" },
  { "057", &eu057, "153" },
  { "058", &eu058, "26241" },
  { "059", &eu059, "107359" },
  { "061", &eu061, "28684" },
  { "062", &eu062, "127035954683" },
  { "063", &eu063, "49" },
  { "064", &eu064, "1322" },
  { "065", &eu065, "272" },
  { "066", &eu066, "661" },
  { "067", &eu067, "7273" },
  { "068", &eu068, "6531031914842725" },
  { "069", &eu069, "510510" },
  { "070", &eu070, "8319823" },
  { "071", &eu071, "428570" },
  { "072", &eu072, "303963552391" },
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

    if (argc == 1 || strcmp(argv[1], puz->name) == 0) {
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
  }
  return 0;
}
