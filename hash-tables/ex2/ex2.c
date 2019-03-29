#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));
  // looping through tickets and storing entries into ht with the source as the key
  for (int i = 0; i < length; i++)
  {
    hash_table_insert(ht, tickets[i]->destination, tickets[i]->source);
  }
  // initializing destination as NONE
  char *destination = "NONE";
  // looping backwards through route and assigning it the value of destination
  for (int i = length - 1; i >= 0; i--)
  {
    route[i] = destination;
    // assign destination as the destination's source
    destination = hash_table_retrieve(ht, destination);
  }
  // freeing up ht allocated memory
  destroy_hash_table(ht);
  // returning flight route
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
