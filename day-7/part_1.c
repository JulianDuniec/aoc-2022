#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_CHILD_COUNT 10

typedef struct node {
  int size;
  int childrenSize;
  int childrenSizeMax;
  struct node *parent;
  struct node **children;
} node;

node *initNode(node *parent) {
  node *child = malloc(sizeof(node));
  child->parent = parent;
  child->size = 0;
  child->childrenSize = 0;
  child->childrenSizeMax = DEF_CHILD_COUNT;
  child->children = malloc(sizeof(node *) * child->childrenSizeMax);
  return child;
}

node *addChild(node *parent) {
  node *child = initNode(parent);
  parent->children[parent->childrenSize++] = child;
  if (parent->childrenSize >= parent->childrenSizeMax) {
    parent->childrenSizeMax *= 2;
    parent->children =
        realloc(parent->children, sizeof(node *) * parent->childrenSizeMax);
  }
  return child;
}

void addSizeToNode(node *d, int size) {
  node *tmp = d;
  do {
    tmp->size += size;
  } while ((tmp = tmp->parent) != NULL);
}

int sumNodeSizesSmallerThan(node *d, int max) {
  int sum = 0;
  if (d->size < max) {
    sum += d->size;
  }
  for (int i = 0; i < d->childrenSize; i++) {
    sum += sumNodeSizesSmallerThan(d->children[i], max);
  }
  return sum;
}

void clearLineBreak(char *s) {
  int len = strlen(s);
  if (s[len - 1] == '\n') {
    s[len - 1] = '\0';
  }
}

int main(int argc, char **arv) {
  node *root = initNode(NULL);
  node *currentNode = root;
  size_t lineLengthLimit = 0;
  char cmd[3];
  char *first, *dirname, *line = NULL;
  int size;
  while (getline(&line, &lineLengthLimit, stdin) != EOF) {
    clearLineBreak(line);
    first = strtok(line, " ");
    if (strcmp(first, "$") == 0) {
      strcpy(cmd, strtok(NULL, " "));
      if (strcmp(cmd, "cd") == 0) {
        dirname = strtok(NULL, " ");
        if (strcmp(dirname, "/") == 0) {
          currentNode = root;
        } else if (strcmp(dirname, "..") == 0) {
          currentNode = currentNode->parent;
        } else {
          currentNode = addChild(currentNode);
        }
      }
      continue;
    }
    if (strcmp(cmd, "ls") == 0) {
      if (strcmp(first, "dir") == 0) {
        continue;
      }
      size = atoi(first);
      addSizeToNode(currentNode, size);
    }
  }

  printf("%d\n", sumNodeSizesSmallerThan(root, 100000));
  return 0;
}