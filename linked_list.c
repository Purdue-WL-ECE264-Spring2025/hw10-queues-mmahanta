#include "linked_list.h"

#include <stdlib.h>

struct list_node *new_node(size_t value) {
  return malloc(sizeof(struct list_node));
}

void insert_at_head(struct linked_list *list, size_t value) {
  struct list_node *new = malloc(sizeof(struct list_node));
    new->value = value;
    new->next = list->head;
    list->head = new;
}

void insert_at_tail(struct linked_list *list, size_t value) {
  struct list_node *new = malloc(sizeof(struct list_node));
    new->value = value;
    new->next = NULL;
    
    if (list->head == NULL) {
        list->head = new;
        return;
    }
    
    struct list_node *current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new;
}

size_t remove_from_head(struct linked_list *list) {
    if (list->head == NULL) {
      return 0;
    }

    struct list_node *temp = list->head;
    size_t value = temp->value;
    list->head = list->head->next;
    free(temp);
    return value;
}

size_t remove_from_tail(struct linked_list *list) {
  if (list->head == NULL) {
    return 0;
  }

  if (list->head->next == NULL) {
      size_t value = list->head->value;
      free(list->head);
      list->head = NULL;
      return value;
  }

  struct list_node *current = list->head;
  while (current->next->next != NULL) {
      current = current->next;
  }

  size_t value = current->next->value;
  free(current->next);
  current->next = NULL;
  return value;
}

void free_list(struct linked_list list) {
  struct list_node *current = list.head;
  while (current != NULL) {
      struct list_node *temp = current;
      current = current->next;
      free(temp);
  }
  list.head = NULL;
}

// Utility function to help you debugging, do not modify
void dump_list(FILE *fp, struct linked_list list) {
  fprintf(fp, "[ ");
  for (struct list_node *cur = list.head; cur != NULL; cur = cur->next) {
    fprintf(fp, "%zu ", cur->value);
  }
  fprintf(fp, "]\n");
}
