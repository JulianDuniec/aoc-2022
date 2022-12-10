#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CRT_WIDTH 40
#define CRT_HEIGHT 6

void clearLineBreak(char *s) {
  int len = strlen(s);
  if (s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

int main(int argc, char **arv) {
  size_t lineLengthLimit = 0;
  char *line = NULL;
  int cycle = 0, xRegister = 1, row, col, incr, add, i, j;
  char crt[CRT_HEIGHT][CRT_WIDTH] = {0};
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
    for (i = 0; i < incr; i++, cycle++) {
      row = cycle / 40;
      col = cycle % 40;
      if (col + 1 >= xRegister && col + 1 <= xRegister + 2) {
        crt[row][col] = '#';
      } else {
        crt[row][col] = '.';
      };
    }
    xRegister += add;
  }
  for (i = 0; i < CRT_HEIGHT; i++) {
    for (j = 0; j < CRT_WIDTH; j++) {
      printf("%c", crt[i][j]);
    }
    printf("\n");
  }
  return 0;
}
