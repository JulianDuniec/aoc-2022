#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WINDOW_SIZE 4

int main(int argc, char **arv) {
  int counter = 0, i, j, found;
  char c;
  char slidingWindow[WINDOW_SIZE] = {0};
  while (1) {
    ++counter;
    c = getchar();
    if (c == EOF) {
      printf("unable to find sequence");
      exit(1);
    }
    if (counter <= WINDOW_SIZE) {
      slidingWindow[counter - 1] = c;
      if (counter < WINDOW_SIZE) {
        continue;
      }
    } else {
      for (int i = 0; i < WINDOW_SIZE - 1; i++) {
        slidingWindow[i] = slidingWindow[i + 1];
      }
      slidingWindow[WINDOW_SIZE - 1] = c;
    }
    found = 0;
    for (i = 0; i < WINDOW_SIZE && !found; i++) {
      for (j = i + 1; j < WINDOW_SIZE; j++) {
        if (slidingWindow[i] == slidingWindow[j] && i != j) {
          found = 1;
          break;
        }
      }
    }
    if (!found) {
      break;
    }
  }
  printf("%d", counter);
  printf("\n");
  return 0;
}