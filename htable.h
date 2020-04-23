#ifndef HTABLE_H
#define HTABLE_H

typedef struct table {
  int size;
  struct node **list;
} table_t;
typedef struct node {
  struct data *data;
  struct node *next;
} node_t;

typedef struct data {
  char *id;
  char *name;
} data_t;


table_t htable_create_table(int size);
void insert(const char *id, const char *name);
node_t *lookup(const char *name);

#endif
