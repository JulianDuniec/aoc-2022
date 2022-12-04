#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **arv) {
  char *line = NULL;
  size_t lineLengthLimit = 0;
  int numCharsRead;

  int p1L, p1H, p2L, p2H;
  int count = 0;
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    p1L = atoi(strtok(line, "-"));
    p1H = atoi(strtok(NULL, ","));
    p2L = atoi(strtok(NULL, "-"));
    p2H = atoi(strtok(NULL, "\n"));
    if ((p1L <= p2L && p1H >= p2H) || ((p2L <= p1L && p2H >= p1H))) {
      ++count;
    }
  }
  printf("%d\n", count);
  return 0;
}