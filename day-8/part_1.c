#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **arv) {
  char c, visible;
  int dataSize = 10;
  char *heights = malloc(sizeof(char) * dataSize);
  int cols = 0, rows = 1, i = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (cols == 0)
        cols = i;
      rows++;
      continue;
    }
    if (i == dataSize) {
      dataSize *= 2;
      heights = realloc(heights, sizeof(char) * dataSize);
    }
    heights[i++] = c;
  }
  int j, k, numVisible = 0;
  for (i = 0; i < rows; i++) {
    for (j = 0; j < cols; j++) {
      c = heights[i * cols + j];
      visible = 1;
      for (k = i - 1; k >= 0; k--) {
        if (heights[k * cols + j] >= c) {
          visible = 0;
          break;
        }
      }
      if (visible) {
        ++numVisible;
        continue;
      }
      visible = 1;
      for (k = i + 1; k < rows; k++) {
        if (heights[k * cols + j] >= c) {
          visible = 0;
          break;
        }
      }
      if (visible) {
        ++numVisible;
        continue;
      }
      visible = 1;
      for (k = j - 1; k >= 0; k--) {
        if (heights[i * cols + k] >= c) {
          visible = 0;
          break;
        }
      }
      if (visible) {
        ++numVisible;
        continue;
      }
      visible = 1;
      for (k = j + 1; k < cols; k++) {
        if (heights[i * cols + k] >= c) {
          visible = 0;
          break;
        }
      }
      if (visible) {
        ++numVisible;
        continue;
      }
    }
  }
  printf("%d\n", numVisible);
  return 0;
}