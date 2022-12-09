#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SNAKE_SIZE 2
#define SET_SIZE 100

typedef struct entry {
  char *key;
  struct entry *next;
} entry;

static struct entry *set[SET_SIZE] = {NULL};

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % SET_SIZE;
}

int setContains(char *key) {
  entry *np;
  for (np = set[hash(key)]; np != NULL; np = np->next) {
    if (strcmp(key, np->key) == 0)
      return 1;
  }
  return 0;
}

void addToSet(char *key) {
  entry *np;
  unsigned hashval;
  if (!setContains(key)) {
    np = malloc(sizeof(entry));
    hashval = hash(key);
    np->key = key;
    np->next = set[hashval];
    set[hashval] = np;
  }
}

void advance(int hx, int hy, int *tx, int *ty) {
  int dx = hx - *tx;
  int dy = hy - *ty;
  int absx = abs(dx);
  int absy = abs(dy);
  if (absx <= 1 && absy <= 1) {
    return;
  }
  int signx = (dx > 0) - (dx < 0);
  int signy = (dy > 0) - (dy < 0);
  if (absx > 1 && absy > 1) {
    (*tx) += signx;
    (*ty) += signy;
  } else if (absx > 1) {
    (*tx) += signx;
    (*ty) += dy;
  } else if (absy > 1) {
    (*ty) += signy;
    (*tx) += dx;
  }
}

int main(int argc, char **arv) {
  int numSquaresVisited = 0;
  size_t lineLengthLimit = 0;
  char *line = NULL;
  char dir;
  int i, j, count = 0, steps;
  const int snakeSize = SNAKE_SIZE * 2;
  int *snake = malloc(sizeof(int) * snakeSize);
  memset(snake, 0, snakeSize);
  int *hx, *hy, *tx, *ty;
  char *key;
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    dir = strtok(line, " ")[0];
    steps = atoi(strtok(NULL, "\n"));
    for (i = 0; i < steps; i++) {
      hx = &snake[0];
      hy = &snake[1];
      if (dir == 'U') {
        (*hy)++;
      } else if (dir == 'D') {
        (*hy)--;
      } else if (dir == 'L') {
        (*hx)--;
      } else if (dir == 'R') {
        (*hx)++;
      }
      for (j = 2; j < snakeSize; j += 2) {
        tx = &snake[j];
        ty = &snake[j + 1];
        advance(*hx, *hy, tx, ty);
        hx = tx;
        hy = ty;
        if (j == snakeSize - 2) {
          key = malloc(sizeof(char) * 10);
          sprintf(key, "%dx%d", *tx, *ty);
          addToSet(key);
        }
      }
    }
  }

  for (int i = 0; i < SET_SIZE; i++) {
    entry *e = set[i];
    if (e == NULL)
      continue;
    do {
      ++count;
    } while ((e = e->next) != NULL);
  }
  printf("%d\n", count);
  return 0;
}
