#include "tree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void print_two_dimensional(Node_ptr root, int space)
{
  if (root == NULL)
    return;
  print_two_dimensional(root->right, space + 10);
  printf("\n");
  for (int count = 0; count < space; count++)
  {
    printf(" ");
  }
  printf("%d\n", root->value);
  print_two_dimensional(root->left, space + 10);
}

void destroy_tree(Node_ptr tree)
{
  if (tree == NULL)
    return;
  Node_ptr left_tree = tree->left;
  Node_ptr right_tree = tree->right;
  free(tree);
  destroy_tree(left_tree);
  destroy_tree(right_tree);
}

/////////////////////////////////////////////////

Node_ptr create_node(int value)
{
  Node_ptr node = malloc(sizeof(Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  return node;
}

int max(int a, int b)
{
  return a > b ? a : b;
}

int get_height(Node_ptr node)
{
  return node == NULL ? 0 : node->height;
};

int get_balance_factor(Node_ptr node)
{
  return node == NULL ? 0 : get_height(node->left) - get_height(node->right);
};

void update_height(Node_ptr node)
{
  node->height = max(get_height(node->left), get_height(node->right)) + 1;
};

Node_ptr right_rotate(Node_ptr tree)
{
  Node_ptr temp = tree->left;
  tree->left = temp->right;
  temp->right = tree;
  update_height(tree);
  update_height(temp);
  return temp;
};

Node_ptr left_rotate(Node_ptr tree)
{
  Node_ptr temp = tree->right;
  tree->right = temp->left;
  temp->left = tree;
  update_height(tree);
  update_height(temp);
  return temp;
};

Node_ptr rotate(Node_ptr tree, int value)
{
  tree->height = 1 + max(get_height(tree->left), get_height(tree->right));
  int height_range = get_balance_factor(tree);
  if (height_range > 1 && value < tree->left->value)
    return right_rotate(tree);
  if (height_range < -1 && value > tree->right->value)
    return left_rotate(tree);
  if (height_range > 1 && value > tree->left->value)
  {
    tree->left = left_rotate(tree->left);
    return right_rotate(tree);
  }
  if (height_range < -1 && value < tree->right->value)
  {
    tree->right = right_rotate(tree->right);
    return left_rotate(tree);
  }
  return tree;
};

Node_ptr insert_to_tree(Node_ptr tree, int value)
{
  if (tree == NULL)
    return create_node(value);
  if (value < tree->value)
    tree->left = insert_to_tree(tree->left, value);
  else
    tree->right = insert_to_tree(tree->right, value);
  return rotate(tree, value);
};

/////////////////////////////////////////////////

// Node_ptr find_min_node(Node_ptr root)
// {
//   return root->left == NULL ? root : find_min_node(root->left);
// }

// Node_ptr push_to_last_and_remove(Node_ptr tree)
// {
//   if (tree->left == NULL && tree->right == NULL)
//     return NULL;
//   if (tree->left == NULL)
//   {
//     Node_ptr temp = tree->right;
//     free(tree);
//     return temp;
//   }
//   if (tree->right == NULL)
//   {
//     Node_ptr temp = tree->left;
//     free(tree);
//     return temp;
//   }

//   Node_ptr min_node = find_min_node(tree->right);
//   tree->value = min_node->value;
//   tree->right = delete_node(tree->right, min_node->value);
//   return tree;
// }

// Node_ptr delete_node(Node_ptr tree, int value)
// {
//   if (tree == NULL)
//     return NULL;
//   if (value < tree->value)
//   {
//     tree->left = delete_node(tree->left, value);
//     return tree;
//   }
//   if (value > tree->value)
//   {
//     tree->right = delete_node(tree->right, value);
//     return tree;
//   }
//   return push_to_last_and_remove(tree);
// }
