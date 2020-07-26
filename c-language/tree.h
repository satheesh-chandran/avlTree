#ifndef __TREE_H_
#define __TREE_H_

typedef struct node
{
  int value;
  struct node *left;
  struct node *right;
  int height;
} Node;

typedef Node *Node_ptr;

typedef enum
{
  False,
  True
} Bool;

Node_ptr insert_to_tree(Node_ptr tree, int value);
Node_ptr right_rotate(Node_ptr tree);
Node_ptr left_rotate(Node_ptr tree);
Node_ptr rotate(Node_ptr tree, int value);
Node_ptr delete_node(Node_ptr tree, int value);

void destroy_tree(Node_ptr tree);
void print_two_dimensional(Node_ptr root, int space);

#endif