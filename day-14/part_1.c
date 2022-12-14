#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 200
#define COLS 600
#define SOURCE_X 500
#define SOURCE_Y 0

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a > b) ? b : a; }

int main(int argc, char **arv) {
  size_t lineLengthLimit = 0;
  char *line = NULL;
  char matrix[ROWS][COLS];
  memset(matrix, '.', ROWS * COLS * sizeof(char));
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    char *points = strtok(line, "->");
    int px = -1, py = -1;
    do {
      char *ptr;
      int x = atoi(strtok_r(points, ",", &ptr));
      int y = atoi(strtok_r(NULL, ",", &ptr));
      if (px != -1) {
        if (px == x) {
          int ma = max(py, y);
          int mi = min(py, y);
          for (int j = mi; j <= ma; j++) {
            matrix[j][px] = '#';
          }
        } else if (py == y) {
          int ma = max(px, x);
          int mi = min(px, x);
          for (int j = mi; j <= ma; j++) {
            matrix[py][j] = '#';
          }
        }
      }
      px = x;
      py = y;
      continue;
    } while ((points = strtok(NULL, "->")) != NULL);
  }
  int counter = 0;
  char found = 0;
  while (1) {
    int sx = SOURCE_X, sy = SOURCE_Y;
    for (;;) {
      if (matrix[sy + 1][sx] == '.') {
        sy++;
        continue;
      }
      if (matrix[sy + 1][sx - 1] == '.') {
        sy++;
        sx--;
        continue;
      }
      if (matrix[sy + 1][sx + 1] == '.') {
        sy++;
        sx++;
        continue;
      }
      matrix[sy][sx] = 'o';
      if (sy == ROWS - 1) {
        found = 1;
      }
      break;
    }
    if (found) {
      break;
    }
    ++counter;
  }

  printf("%d\n", counter);
}