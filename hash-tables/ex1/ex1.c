#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"
#include "ex1.h"

Answer *get_indices_of_item_weights(int *weights, int length, int limit)
{
  HashTable *ht = create_hash_table(16);
  // allocating memory for answer and setting fields to default
  Answer *answer = malloc(sizeof(Answer));
  answer->index_1 = -1;
  answer->index_2 = -1;
  // looping through weights array and storing the weight and index in the hashtable
  for (int i = 0; i < length; i++)
  {
    hash_table_insert(ht, weights[i], i);
  }
  // looping through weights array again
  for (int i = 0; i < length; i++)
  {
    // checking if the limit can be reached through addition of weights in the hashtable
    if (hash_table_retrieve(ht, limit - weights[i]) != -1)
    {
      // if the smaller index index_2 is null, assign it to i (index in weights array)
      if (answer->index_2 == -1)
      {
        answer->index_2 = i;
      }
      // if the smaller index is already full, then assign index_1 to i
      else
      {
        answer->index_1 = i;
      }
    }
  }
  // freeing up hashtable memory
  destroy_hash_table(ht);
  // returning answer if the values of index_1 and 2 are filled
  if (answer->index_1 != -1)
    return answer;
  // returning null if nothing adds to the limit
  return NULL;
}

void print_answer(Answer *answer)
{
  if (answer != NULL)
  {
    printf("%d %d\n", answer->index_1, answer->index_2);
  }
  else
  {
    printf("NULL\n");
  }
}

#ifndef TESTING
int main(void)
{

  // TEST 1
  int weights_1 = {9};
  Answer *answer_1 = get_indices_of_item_weights(&weights_1, 1, 9);
  print_answer(answer_1); // NULL

  // TEST 2
  int weights_2[] = {4, 4};
  Answer *answer_2 = get_indices_of_item_weights(weights_2, 2, 8);
  print_answer(answer_2); // {1, 0}

  // TEST 3
  int weights_3[] = {4, 6, 10, 15, 16};
  Answer *answer_3 = get_indices_of_item_weights(weights_3, 5, 21);
  print_answer(answer_3); // {3, 1}

  // TEST 4
  int weights_4[] = {12, 6, 7, 14, 19, 3, 0, 25, 40};
  Answer *answer_4 = get_indices_of_item_weights(weights_4, 9, 7);
  print_answer(answer_4); // {6, 2}

  return 0;
}
#endif
