#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearLineBreak(char *s) {
  int len = strlen(s);
  if (s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

int main(int argc, char **arv) {
  size_t lineLengthLimit = 0;
  char *line = NULL;
  int sigStrSum = 0;
  int cycle = 0, xRegister = 1, chk = 20, incr, add, i;
  char *op;
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    clearLineBreak(line);
    op = strtok(line, " ");
    if (strcmp(op, "noop") == 0) {
      incr = 1;
      add = 0;
    } else if (strcmp(op, "addx") == 0) {
      add = atoi(strtok(NULL, " "));
      incr = 2;
    }
    for (i = 0; i < incr; i++) {
      if (++cycle == chk) {
        chk += 40;
        sigStrSum += cycle * xRegister;
      }
    }
    xRegister += add;
  }

  printf("%d\n", sigStrSum);
  return 0;
}
