#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FS_SIZE 70000000
#define UPDATE_SIZE 30000000

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

int treeSize(node *d) {
  int sum = 0;
  ++sum;
  for (int i = 0; i < d->childrenSize; i++) {
    sum += treeSize(d->children[i]);
  }
  return sum;
}

void flatListR(node **list, node *c, int *size) {
  list[*size] = c;
  for (int i = 0; i < c->childrenSize; i++) {
    *size += 1;
    flatListR(list, c->children[i], size);
  }
}

node **flatList(node *d, int *size) {
  int ts = treeSize(d);
  node **list = malloc(sizeof(node *) * ts);
  flatListR(list, d, size);
  *size += 1;
  return list;
}

int sortNodesBySizeASC(const void *a, const void *b) {
  const node *nodeA = *(node *const *)a;
  const node *nodeB = *(node *const *)b;
  if (nodeB->size > nodeA->size)
    return -1;
  if (nodeB->size < nodeA->size)
    return 1;
  return 0;
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

  int listSize = 0;
  node **list = flatList(root, &listSize);
  qsort(list, listSize, sizeof(node *), sortNodesBySizeASC);

  int requiredToDelete = UPDATE_SIZE - (FS_SIZE - root->size);
  for (int i = 0; i < listSize; i++) {
    if (list[i]->size > requiredToDelete) {
      printf("%d\n", list[i]->size);
      return 0;
    }
  }
  printf("could not find a directory to delete\n");
  return 1;
}