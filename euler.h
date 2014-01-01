#include <assert.h>
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>
#include <ctype.h>
#include <math.h>
#include <gmp.h>

#define todigit(ch) ((ch) - '0')

extern void gensieve(char *sieve, int n);
extern int genprimes(int *primes, int n);
extern int isprime(int n);
extern int is_prime(int n);
extern int is_palindrome(int n);
extern int sumdivisors(int n);
extern void add(char *dst, char *src, int n);
extern void mul1(char *dst, int a, int n);
extern int max(int a, int b);
extern int readwords(const char *filename, char **words, int maxwords);
extern void swap(char *a, char *b);
extern char *nextperm(char *s);
extern char *prevperm(char *s);
extern int subint(char *s, int i, int j);
extern int gcd(int a, int b);
extern int digitsum(mpz_t z);
extern void digitsort(char *buf, int n);
extern int isperm(int a, int b);
extern void genphi(int *phi, int max);
extern void strrev(char *str);


typedef void (solver)(char *ans);
struct puzzle {
  const char *name;
  solver *fn;
  const char *ans;
};

solver eu001, eu002, eu003, eu004, eu005, eu006, eu007, eu008, eu009, eu010;
solver eu011, eu012, eu013, eu014, eu015, eu016, eu017, eu018, eu019, eu020;
solver eu021, eu022, eu023, eu024, eu025, eu026, eu027, eu028, eu029, eu030;
solver eu031, eu032, eu033, eu034, eu035, eu036, eu037, eu038, eu039, eu040;
solver eu041, eu042, eu043, eu044, eu045, eu046, eu047, eu048, eu049, eu050;
solver eu051, eu052, eu053, eu054, eu055, eu056, eu057, eu058, eu059, eu060;
solver eu061, eu062, eu063, eu064, eu065, eu066, eu067, eu068, eu069, eu070;
solver eu071, eu072, eu073, eu074, eu075, eu076, eu077, eu078, eu079, eu080;
