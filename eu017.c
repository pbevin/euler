#include "euler.h"

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
