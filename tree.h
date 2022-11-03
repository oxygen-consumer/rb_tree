#ifndef TREE_H_
#define TREE_H_

#include <stdbool.h>

struct t_node {
  int key;
  enum { red, black } color;
  struct t_node *parent, *left, *right;
};

struct t_tree {
  struct t_node *root;
};

void init_node(struct t_node *node);

void tree_insert(struct t_tree *tree, struct t_node *node);

void insert_fixup(struct t_tree *tree, struct t_node *node);

void rotate_left(struct t_tree *tree, struct t_node *node);

void rotate_right(struct t_tree *tree, struct t_node *node);

void print_tree(struct t_node *current);

bool tree_search(struct t_node *current, int key);

#endif // TREE_H_
