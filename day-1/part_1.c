#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **arv) {
  char *line = NULL;
  size_t lineLengthLimit = 10;
  int numCharsRead;
  int currentSum = 0;
  int highestSum = 0;
  while (1) {
    numCharsRead = getline(&line, &lineLengthLimit, stdin);
    if (numCharsRead == EOF || (numCharsRead == 1 && line[0] == '\n')) {
      if (currentSum > highestSum) {
        highestSum = currentSum;
      }
      currentSum = 0;
      if (numCharsRead == EOF) {
        break;
      }
      continue;
    }
    currentSum += atoi(line);
  }
  printf("%d\n", highestSum);
  return 0;
}