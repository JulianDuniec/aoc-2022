#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char contains(char *s, char c) {
  int i = 0;
  while (s[i] != '\0') {
    if (s[i] == c)
      return 1;
    i++;
  }
  return 0;
}

typedef struct {
  char *array;
  size_t size;
  size_t head;
} Stack;

void initStack(Stack *s, size_t size) {
  s->array = malloc(size * sizeof(char));
  s->head = 0;
  s->size = size;
}

void push(Stack *s, char c) {
  if (s->head == s->size) {
    s->size *= 2;
    s->array = realloc(s->array, s->size * sizeof(char));
  }
  s->array[s->head++] = c;
}

void pushN(Stack *s, char *c, int n) {
  for (int i = 0; i < n; i++) {
    push(s, c[i]);
  }
}

char pop(Stack *s) { return s->array[--s->head]; }

char *popN(Stack *s, int n) {
  char *res = &(s->array[s->head - n]);
  s->head -= n;
  return res;
}

void reverse(Stack *s) {
  char temp;
  for (int i = 0; i < s->head / 2; i++) {
    temp = s->array[i];
    s->array[i] = s->array[s->head - i - 1];
    s->array[s->head - i - 1] = temp;
  }
}

void parseInstruction(char *line, int *move, int *from, int *to) {
  strtok(line, " ");
  *move = atoi(strtok(NULL, " "));
  strtok(NULL, " ");
  *from = atoi(strtok(NULL, " "));
  strtok(NULL, " ");
  *to = atoi(strtok(NULL, " "));
}

int main(int argc, char **arv) {
  char *line = NULL, c;
  size_t lineLengthLimit = 0;
  int i, j, move, from, to, numCharsRead, numStacks;
  Stack *stacks = NULL;

  while ((numCharsRead = getline(&line, &lineLengthLimit, stdin)) != EOF &&
         contains(line, '[')) {
    numStacks = (numCharsRead + 1) / 4;
    if (stacks == NULL) {
      stacks = malloc(sizeof(Stack) * numStacks);
      for (i = 0; i < numStacks; i++) {
        initStack(&stacks[i], 10);
      }
    }
    for (i = 0, j = 1; i < numStacks; i++, j += 4) {
      char c = line[j];
      if (c != ' ') {
        push(&stacks[i], c);
      }
    }
  }
  for (int i = 0; i < numStacks; i++) {
    reverse(&stacks[i]);
  }
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    if (strncmp(line, "move", 4) != 0) {
      continue;
    }
    parseInstruction(line, &move, &from, &to);
    pushN(&stacks[to - 1], popN(&stacks[from - 1], move), move);
  }
  for (int i = 0; i < numStacks; i++) {
    printf("%c", pop(&stacks[i]));
  }
  printf("\n");
  return 0;
}
