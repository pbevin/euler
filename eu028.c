#include "euler.h"

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
