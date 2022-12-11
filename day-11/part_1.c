#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_ROUNDS 20
#define MAX_ITEMS 100

typedef struct {
  int items[MAX_ITEMS];
  int divisor;
  int trueIndex;
  int falseIndex;
  int ls, rs;
  char op;
  int numInspections;
} monkey;

void clearLineBreak(char *s) {
  int len = strlen(s);
  if (len == 0)
    return;
  if (s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

char *trimStart(char *s) {
  for (int i = 0;; i++) {
    if (s[i] != ' ') {
      return s + i;
    }
  }
  return s;
}

int hasPrefix(const char *pre, const char *str) {
  return strncmp(pre, str, strlen(pre)) == 0;
}

int main(int argc, char **arv) {
  size_t lineLengthLimit = 0;
  char *line = NULL;
  size_t charsRead;

  int numMonkeys = 0;
  int monkeySize = 4;
  monkey *monkeys = malloc(sizeof(monkey) * monkeySize);
  while ((charsRead = getline(&line, &lineLengthLimit, stdin)) != EOF) {
    monkeys[numMonkeys].numInspections = 0;
    if (charsRead == 1) {
      numMonkeys++;
      if (numMonkeys == monkeySize) {
        monkeySize *= 2;
        monkeys = realloc(monkeys, sizeof(monkey) * monkeySize);
      }
      continue;
    }

    clearLineBreak(line);
    char *attr = strtok(line, ":");
    attr = trimStart(attr);

    if (hasPrefix(attr, "Starting items")) {
      char *it;
      int i = 0;
      memset(monkeys[numMonkeys].items, 0, MAX_ITEMS);
      while ((it = strtok(NULL, ",")) != NULL) {
        monkeys[numMonkeys].items[i++] = atoi(it);
      }
      continue;
    }

    if (hasPrefix(attr, "Operation")) {
      strtok(NULL, "=");
      char *ls = strtok(NULL, " ");
      char *op = strtok(NULL, " ");
      char *rs = strtok(NULL, " ");
      monkeys[numMonkeys].ls = atoi(ls);
      monkeys[numMonkeys].rs = atoi(rs);
      monkeys[numMonkeys].op = op[0];
      continue;
    }

    if (hasPrefix(attr, "Test")) {
      char *s = strtok(NULL, " divisible by");
      monkeys[numMonkeys].divisor = atoi(s);
      continue;
    }

    if (hasPrefix(attr, "If true")) {
      char *s = strtok(NULL, " throw to monkey ");
      monkeys[numMonkeys].trueIndex = atoi(s);
      continue;
    }

    if (hasPrefix(attr, "If false")) {
      char *s = strtok(NULL, " throw to monkey ");
      monkeys[numMonkeys].falseIndex = atoi(s);
      continue;
    }
  }
  numMonkeys++;

  int h1 = 0, h2 = 0;
  for (int round = 0; round < NUM_ROUNDS; round++) {
    for (int mindex = 0; mindex < numMonkeys; mindex++) {
      monkey *m = &monkeys[mindex];
      for (int i = 0; m->items[i] != 0; i++) {
        m->numInspections++;
        if (m->numInspections > h1) {
          h1 = m->numInspections;
        } else if (m->numInspections > h2) {
          h2 = m->numInspections;
        }
        int wr = m->items[i];
        int ls = m->ls == 0 ? wr : m->ls;
        int rs = m->rs == 0 ? wr : m->rs;
        if (m->op == '*') {
          wr = ls * rs;
        } else if (m->op == '+') {
          wr = ls + rs;
        }
        wr /= 3;
        monkey *to;
        if (wr % m->divisor == 0) {
          to = &monkeys[m->trueIndex];
        } else {
          to = &monkeys[m->falseIndex];
        }
        for (int j = 0;; j++) {
          if (to->items[j] == 0) {
            to->items[j] = wr;
            break;
          }
        }
        m->items[i] = 0;
      }
    }
  }
  printf("%d\n", h1 * h2);
  return 0;
}
