#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  struct t_tree *tree = malloc(sizeof(struct t_tree));
  tree->root = malloc(sizeof(struct t_node));
  init_node(tree->root);
  tree->root->color = black;
  printf("Enter tree root: ");
  scanf("%d", &tree->root->key);

  printf("Enter tree values followed by a 0: ");
  while (true) {
    struct t_node *new_node = malloc(sizeof(struct t_node));
    init_node(new_node);
    scanf("%d", &new_node->key);

    if (new_node->key == 0) {
      free(new_node);
      break;
    }

    tree_insert(tree, new_node);
  }

  print_tree(tree->root);

  int searched;
  printf("Enter the key which you want to verify if it is in the tree: ");
  scanf("%d", &searched);
  if (tree_search(tree->root, searched)) {
    printf("Key found\n");
  } else {
    printf("Key not found\n");
  }

  free_tree(tree->root);
  return 0;
}
