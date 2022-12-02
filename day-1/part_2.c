#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **arv) {
  char *line = NULL;
  size_t lineLengthLimit = 0;
  int numCharsRead;
  int currentSum = 0;
  int top1 = 0, top2 = 0, top3 = 0;
  while (1) {
    numCharsRead = getline(&line, &lineLengthLimit, stdin);
    if (numCharsRead == EOF || (numCharsRead == 1 && line[0] == '\n')) {
      if (currentSum > top1) {
        top3 = top2;
        top2 = top1;
        top1 = currentSum;
      } else if (currentSum > top2) {
        top3 = top2;
        top2 = currentSum;
      } else if (currentSum > top3) {
        top3 = currentSum;
      }
      currentSum = 0;
      if (numCharsRead == EOF) {
        break;
      }
      continue;
    }
    currentSum += atoi(line);
  }
  printf("%d\n", top1 + top2 + top3);
  return 0;
}