#include "euler.h"

void eu059(char *ans) {
  unsigned char encrypted[] = {
#include "cipher1.txt"
  };
  unsigned char plaintext[1500];
  double maxRatio = 0;

  /*
   * Going to assume that the answer is the valid plaintext
   * with the highest ratio of space to non-space characters.
   * Valid in this context means "without any non-ASCII characters."
   *
   * NB. This is the first puzzle where we write into ans[] more
   * than once.
   */
  for (int a = 'a'; a <= 'z'; a++) {
    for (int b = 'a'; b <= 'z'; b++) {
      for (int c = 'a'; c <= 'z'; c++) {
        char key[4];
        int invalid = 0;
        int space = 0;
        int nonspace = 0;
        int sumOfChars = 0;

        key[0] = a; key[1] = b; key[2] = c; key[3] = 0;
        for (int i = 0; i < sizeof(encrypted); i++) {
          char ch;
          ch = plaintext[i] = encrypted[i] ^ key[i%3];

          if (!isprint(plaintext[i])) {
            invalid = 1;
            break;
          }

          if (isspace(ch)) { space++; }
          else { nonspace++; }
          sumOfChars += ch;
        }
        plaintext[sizeof(encrypted)] = 0;
        if (!invalid) {
          double ratio = (double)space / (space+nonspace);
          if (ratio > maxRatio) {
            maxRatio = ratio;
            sprintf(ans, "%d", sumOfChars);
          }
        }
      }
    }
  }
}

