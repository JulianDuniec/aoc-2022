#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scoreFromChar(char c) {
  if (c > 96) {
    return c - 96;
  }
  return c - 38;
}

int main(int argc, char **arv) {
  char *line = NULL;
  size_t lineLengthLimit = 0;
  int numCharsRead;
  int score = 0, imax, mid, found, i;
  char c, d;
  while ((numCharsRead = getline(&line, &lineLengthLimit, stdin)) != EOF) {
    imax = line[numCharsRead - 1] == '\n' ? numCharsRead - 2 : numCharsRead - 1;
    mid = (imax + 1) / 2;
    found = 0;
    for (int i = 0; i < mid && found == 0; i++) {
      c = line[i];
      for (int j = mid; j <= imax; j++) {
        d = line[j];
        if (c == d) {
          score += scoreFromChar(c);
          found = 1;
          break;
        }
      }
    }
  }
  printf("%d\n", score);
  return 0;
}