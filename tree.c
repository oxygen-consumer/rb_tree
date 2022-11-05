#include "tree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void init_node(struct t_node *node) {
  node->parent = node->left = node->right = NULL; // FIXME: does this work?
  node->key = 0;
  node->color = red;
}

void tree_insert(struct t_tree *tree, struct t_node *node) {
  struct t_node *current = tree->root;

  while (true) {
    if (node->key < current->key) {
      if (current->left == NULL) {
        current->left = node;
        break;
      }
      current = current->left;
    }

    else if (node->key > current->key) {
      if (current->right == NULL) {
        current->right = node;
        break;
      }
      current = current->right;
    }

    else {
      break;
    }
  }

  node->parent = current;
  insert_fixup(tree, node);
}

void insert_fixup(struct t_tree *tree, struct t_node *node) {
  // TODO: document this function because it's a bit hard to understand

  while (node->parent != NULL && node->parent->color == red) {
    struct t_node *grandfather = node->parent->parent;

    if (node->parent == grandfather->left) {
      struct t_node *uncle = grandfather->right;

      if (uncle != NULL && uncle->color == red) {
        node->parent->color = black;
        uncle->color = black;
        grandfather->color = red;
        node = grandfather;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotate_left(tree, node);
        }
        grandfather = node->parent->parent;

        node->parent->color = black;
        grandfather->color = red;
        rotate_right(tree, grandfather);
      }
    }

    else {
      struct t_node *uncle = grandfather->left;

      if (uncle != NULL && uncle->color == red) {
        node->parent->color = black;
        uncle->color = black;
        grandfather->color = red;
        node = grandfather;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotate_right(tree, node);
        }
        grandfather = node->parent->parent;

        node->parent->color = black;
        grandfather->color = red;
        rotate_left(tree, grandfather);
      }
    }
  }

  tree->root->color = black;
}

// TODO: format and document rotate functions

void rotate_left(struct t_tree *tree, struct t_node *node) {
  struct t_node *other = node->right;
  node->right = other->left;
  if (other->left != NULL) {
    other->left->parent = node;
  }

  other->parent = node->parent;
  if (other->parent == NULL) {
    tree->root = other;
  } else if (node == node->parent->left) {
    node->parent->left = other;
  } else {
    node->parent->right = other;
  }

  other->left = node;
  node->parent = other;
}

void rotate_right(struct t_tree *tree, struct t_node *node) {
  struct t_node *other = node->left;
  node->left = other->right;
  if (other->right != NULL) {
    other->right->parent = node;
  }

  other->parent = node->parent;
  if (other->parent == NULL) {
    tree->root = other;
  } else if (node == node->parent->left) {
    node->parent->left = other;
  } else {
    node->parent->right = other;
  }

  other->right = node;
  node->parent = other;
}

void print_tree(struct t_node *current) {
  if (current == NULL) {
    // we shouldn't get here
    printf("Tree is empty\n");
    return;
  }

  if (current->left != NULL) {
    print_tree(current->left);
  }

  if (current->color == black) {
    printf("[B] ");
  } else {
    printf("[R] ");
  }
  printf("%d\n", current->key);

  if (current->right != NULL) {
    print_tree(current->right);
  }
}

bool tree_search(struct t_node *current, int key) {
  if (current == NULL) {
    // We shouldn't get here
    printf("Tree is empty\n");
    return false;
  }

  if (current->key == key) {
    return true;
  }

  if (current->key < key && current->right != NULL) {
    return tree_search(current->right, key);
  } else if (current->key > key && current->left != NULL) {
    return tree_search(current->left, key);
  } else {
    return false;
  }
}

void free_tree(struct t_node *current) {
  if (current == NULL) {
    // We shouldn't get here
    printf("Tree is empty");
    return;
  }

  if (current->left != NULL) {
    free_tree(current->left);
  }
  if (current->right != NULL) {
    free_tree(current->right);
  }

  free(current);
}
