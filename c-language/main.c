#include "tree.h"
#include <stdio.h>

int main(void)
{
  int numbers[] = {5, 3, 8, 1, 4, 7, 9, 2, 12, 17, 13, 19};
  int length = sizeof(numbers) / sizeof(int);
  Node_ptr tree = NULL;
  for (int index = 0; index < length; index++)
  {
    tree = insert_to_tree(tree, numbers[index]);
  }

  print_two_dimensional(tree, 0);

  destroy_tree(tree);
  return 0;
}
