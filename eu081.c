#include "euler.h"


void read_matrix(int matrix[80][80], const char *filename) {
  FILE *fp = fopen(filename, "r");
  for (int i = 0; i < 80; i++) {
    for (int j = 0; j < 80; j++) {
      fscanf(fp, "%d,", &matrix[i][j]);
    }
  }
  fclose(fp);
}

void eu081(char *ans) {
  static int matrix[80][80];
  read_matrix(matrix, "matrix.txt");

  static int sums[80][80];
  memset(sums, 0, sizeof(sums));

  sums[0][0] = matrix[0][0];
  for (int i = 1; i < 80; i++) {
    sums[0][i] = sums[0][i-1] + matrix[0][i];
    sums[i][0] = sums[i-1][0] + matrix[i][0];
  }

  for (int i = 1; i < 80; i++) {
    for (int j = 1; j < 80; j++) {
      int above = sums[i-1][j];
      int left = sums[i][j-1];

      sums[i][j] = min(above, left) + matrix[i][j];
    }
  }

  sprintf(ans, "%d", sums[79][79]);
}
