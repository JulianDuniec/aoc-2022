#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **arv) {
  char c;
  int dataSize = 10;
  char *heights = malloc(sizeof(char) * dataSize);
  int cols = 0, rows = 1, i = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (cols == 0) {
        cols = i;
      }
      rows++;
      continue;
    }
    if (i == dataSize) {
      dataSize *= 2;
      heights = realloc(heights, sizeof(char) * dataSize);
    }
    heights[i++] = c;
  }
  int maxTreeScore = 0, ls, rs, us, ds, treeScore, j, k;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      ls = rs = us = ds = 0;
      c = heights[i * cols + j];
      for (k = i - 1; k >= 0; k--) {
        ++us;
        if (heights[k * cols + j] >= c) {
          break;
        }
      }
      for (k = i + 1; k < rows; k++) {
        ++ds;
        if (heights[k * cols + j] >= c) {
          break;
        }
      }
      for (k = j + 1; k < cols; k++) {
        ++rs;
        if (heights[i * cols + k] >= c) {
          break;
        }
      }
      for (k = j - 1; k >= 0; k--) {
        ++ls;
        if (heights[i * cols + k] >= c) {
          break;
        }
      }
      treeScore = ls * rs * us * ds;
      if (treeScore > maxTreeScore) {
        maxTreeScore = treeScore;
      }
    }
  }
  printf("%d\n", maxTreeScore);
  return 0;
}