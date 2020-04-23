#include "htable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

node_t *hash_array[SIZE] = { NULL };
node_t *newnode(const char *id, const char *name);
void *s_malloc(size_t size);
unsigned long get_hash_index(const char *s);

table_t htable_create_table(int size)
{
  int i;
  table_t table;
  table.size = size;
  table.list = s_malloc(sizeof(node_t*)*size);
  for (i = 0; i < size; i++)
    table.list[i] = NULL;
  return table;
}
void insert(const char *id, const char *name)
{
  node_t *newp, *ptr;
  unsigned long index;

  newp = newnode(id, name);
  index = get_hash_index(id);
  if (hash_array[index] == NULL)
    hash_array[index] = newp;
  else {
    ptr = hash_array[index];
    while (1) {
      if (ptr->next == NULL)
      {
        ptr->next = newp;
        break;
      }
      ptr = ptr->next;
    }
  }
}
node_t *lookup(const char *id)
{
  unsigned long index = get_hash_index(id);
  node_t *ptr;

  ptr = hash_array[index];
  while(ptr) {
    if ((strcmp(id, ptr->data->id)) == 0)
      return ptr;
    ptr = ptr->next;
  }
  fprintf(stderr, "Failed to find element with id: %s\n", id);
  exit(1);
}
unsigned long get_hash_index(const char *s)
{
  unsigned long hash = 5821;
  int c;

  while ((c = *s++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    
  return hash % SIZE;
}
void *s_malloc(size_t size) { // safe malloc
  void *p = malloc(size);
  if (!p)
    exit(1);
  return p;
}
node_t *newnode(const char *id, const char *name)
{
  node_t *newp;

  newp             = s_malloc(sizeof(node_t));
  newp->data       = s_malloc(sizeof(data_t));
  newp->data->id   = strdup(id);
  newp->data->name = strdup(name);
  newp->next       = NULL;
  return newp;
}
