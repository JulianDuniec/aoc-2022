#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EOL 0

int scoreFromChar(char c) {
  if (c > 96) {
    return c - 96;
  }
  return c - 38;
}

int main(int argc, char **arv) {
  size_t lineLengthLimit = 0;
  char *lines[3] = {NULL, NULL, NULL};
  char c, d, e;
  int i = 0, j = 0, k = 0, li = 0, score = 0, found;
  while (getline(&lines[li], &lineLengthLimit, stdin) != EOF) {
    if (++li < 3) {
      continue;
    }
    li = 0;
    found = 0;
    for (i = 0, c = lines[0][i]; c != EOL && found == 0; c = lines[0][++i]) {
      for (j = 0, d = lines[1][j]; d != EOL && found == 0; d = lines[1][++j]) {
        if (d != c) {
          continue;
        }
        for (k = 0, e = lines[2][k]; e != EOL; e = lines[2][++k]) {
          if (e == c) {
            score += scoreFromChar(c);
            found = 1;
            break;
          }
        }
      }
    }
    free(lines[0]);
    free(lines[1]);
    free(lines[2]);
    lines[0] = NULL;
    lines[1] = NULL;
    lines[2] = NULL;
  }

  printf("%d\n", score);
  return 0;
}