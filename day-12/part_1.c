#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char isEmpty(const int *v, const int len) {
  for (int i = 0; i < len; i++) {
    if (v[i] != -1)
      return 0;
  }
  return 1;
}

char contains(const int *s, const int v, const int len) {
  for (int i = 0; i < len; i++) {
    if (s[i] == v)
      return 1;
  }
  return 0;
}

int main(int argc, char **arv) {
  char c;
  int counter = 0, cols = 0, rows = 1;
  int mapSize = 10;
  char *map = malloc(sizeof(char) * mapSize);
  int startIndex, endIndex;
  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      if (cols == 0) {
        cols = counter;
      }
      ++rows;
      continue;
    }
    if (counter == mapSize) {
      mapSize *= 2;
      map = realloc(map, sizeof(char) * mapSize);
    }
    if (c == 'S') {
      startIndex = counter;
      c = 'a';
    } else if (c == 'E') {
      endIndex = counter;
      c = 'z';
    }
    map[counter++] = c;
  }

  const int numItems = counter;
  int distance[numItems];
  int vertices[numItems][4];
  int queue[numItems];

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int index = i * cols + j;
      char current = map[index];
      queue[index] = index;
      distance[index] = INT_MAX;
      vertices[index][0] = -1;
      if (j > 0) {
        const int vindex = i * cols + j - 1;
        char vc = map[vindex];
        if (vc - current <= 1) {
          vertices[index][0] = vindex;
        }
      }
      vertices[index][1] = -1;
      if (j < cols - 1) {
        const int vindex = i * cols + j + 1;
        char vc = map[vindex];
        if (vc - current <= 1) {
          vertices[index][1] = vindex;
        }
      }
      vertices[index][2] = -1;
      if (i > 0) {
        const int vindex = (i - 1) * cols + j;
        char vc = map[vindex];
        if (vc - current <= 1) {
          vertices[index][2] = vindex;
        }
      }
      vertices[index][3] = -1;
      if (i < rows - 1) {
        const int vindex = (i + 1) * cols + j;
        char vc = map[vindex];
        if (vc - current <= 1) {
          vertices[index][3] = vindex;
        }
      }
    }
  }

  distance[startIndex] = 0;
  while (!isEmpty(queue, numItems)) {
    int min = INT_MAX, u = -1;
    for (int i = 0; i < numItems; i++) {
      if (queue[i] == -1)
        continue;
      int dist = distance[i];
      if (dist <= min) {
        min = dist;
        u = i;
      }
    }
    if (u == endIndex) {
      break;
    }
    queue[u] = -1;

    for (int i = 0; i < 4; i++) {
      int v = vertices[u][i];
      if (v == -1 || !contains(queue, v, numItems)) {
        continue;
      }
      int alt = distance[u] + 1;
      if (alt < distance[v]) {
        distance[v] = alt;
      }
    }
  }
  printf("%d\n", distance[endIndex]);
}