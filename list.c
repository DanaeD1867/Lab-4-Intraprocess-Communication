// list/list.c
// 
// Implementation for linked list.
//
// Author: Danae Dunlap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int elem;

struct node {
	elem value;
	struct node *next;
};
typedef struct node node_t;

struct list {
	node_t *head;
};
typedef struct list list_t;

list_t *list_alloc();
void list_free(list_t *l);
void list_print(list_t *l);
char* listToString(list_t *l);
int list_length(list_t *l);
void list_add_to_back(list_t *l, elem value);
void list_add_to_front(list_t *l, elem value);
void list_add_at_index(list_t *l, elem value, int index);
elem list_remove_from_back(list_t *l);
elem list_remove_from_front(list_t *l);
elem list_remove_at_index(list_t *l, int index);
bool list_is_in(list_t *l, elem value);
elem list_get_elem_at(list_t *l, int index);
int list_get_index_of(list_t *l, elem value);

list_t *list_alloc() { 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) {

  if(list_length(l) == 0){
    printf("List already empty\n"); 
    return ; 
  }

  node_t* curr = l->head; 
  node_t* temp; 

  
  while(curr != NULL){ 
    temp = curr->next; 
    free(curr); 
    curr = temp; 
  }

  l->head = NULL; 
}


void list_print(list_t *l){
  node_t* curr = l->head;
  printf("My List: \n"); 
  while (curr != NULL){
    printf("%d\n", curr->value);
    curr = curr->next;
  }
}

char * listToString(list_t *l) {
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) { 
  int listlen = 0; 
  node_t* curr = l->head;
  while(curr != NULL){
    listlen++; 
    curr = curr->next;
  }

  return listlen; 
}

void list_add_to_back(list_t *l, elem value) {
  node_t* newNode = (node_t *) malloc(sizeof(node_t)); 
  node_t* curr = l->head;

  newNode->value = value;
  newNode->next = NULL;

  if(curr != NULL){
    while(curr->next != NULL){
    curr = curr->next;
    }
    curr->next = newNode; 
  }else{
    l->head = newNode; 
  }

}

void list_add_to_front(list_t *l, elem value) {
    node_t* cur_node = (node_t *) malloc(sizeof(node_t));
    node_t* head = l->head;  // get head of list
    
    cur_node->value = value;

     /* Insert to front */
     cur_node->next = head;
     l->head = cur_node;
}

void list_add_at_index(list_t *l, elem value, int index){

  if(l == NULL){
    printf("List is not intialized"); 
    return; 
  }

  node_t* curr = l->head;
  node_t* prev = NULL;

  node_t* newNode = (node_t *) malloc(sizeof(node_t));
  if(newNode == NULL){
    printf("Memory allocation failed\n"); 
    return; 
  }

  newNode->value = value; 
  newNode->next = NULL; 

  int listlen = list_length(l); 
  if(index < 0){
    index = listlen + index + 1; 
    if(index < 0){
      printf("Given index surpasses current list length\n"); 
      return; 
    }
  }

  if(index > listlen){
    printf("Given index surpasses current list length\n"); 
    return; 
  }else if(index == 0){
    newNode->next = l->head; 
    l->head=newNode; 
  }else if(index == listlen){
    list_add_to_back(l, value); 
  }
  else{
    int i; 
    for(i = 0; i < index; i++){
      prev = curr; 
      curr = curr->next; 
    }
    prev->next = newNode; 
    newNode->next = curr;
  }
}

elem list_remove_from_back(list_t *l) { 

  if(l->head == NULL){
    printf("List is empty\n"); 
    return -1; 
  }

  node_t* curr = l->head; 

  int listlen = list_length(l); 
  elem value; 

  if(listlen == 1){
    value = l->head->value; 
    l->head = NULL;
    free(l->head); 
    return value; 
  }
  
  while(curr->next->next != NULL){
    curr = curr->next; 
  }

  node_t* last = curr->next; 
  value = last->value;
  curr->next = NULL;
  free(last); 
  return value; 

}

elem list_remove_from_front(list_t *l) { 
  if(l->head == NULL || l == NULL){
    return -1; 
  }

  node_t *first = l->head; 
  elem value = first->value; 

  l->head = first->next;

  return value;
}

elem list_remove_at_index(list_t *l, int index) { 
  node_t* curr = l->head; 
  node_t* prev = l->head;
  node_t* removed; 
  int listlen = list_length(l);

  if(listlen == 0){
    printf("List already empty\n"); 
    return -1; 
  }

  if(index < 0){
    index = listlen + index + 1; 
    if(index < 0){
      printf("Given index is greater than current length of list"); 
      return -1; 
    }
  }

  if(index >= listlen){
    printf("Given index is greater than current length of list"); 
    return -1; 
  }

  if(index == 0){
    list_remove_from_front(l); 
  }

  if(index == listlen-1){
    list_remove_from_back(l); 
  }

  int i; 
  for(i = 0; i < index; i++){
    prev = curr; 
    curr = curr->next; 
  }

  if(curr){
    prev->next = curr->next; 
    removed = curr; 
    return removed->value; 
  }

  return -1; 
}


bool list_is_in(list_t *l, elem value) { 
  node_t* curr = l->head;

  while(curr != NULL){
    if (curr->value == value){
      return true; 
    }
    curr = curr->next;
  } 
  return false; 
}

elem list_get_elem_at(list_t *l, int index) { 
  node_t* curr = l->head;
  int listlen = list_length(l); 

  if(index >= listlen){
    printf("Given index is greater than current list length\n"); 
    return -1; 
  }

  if(index < 0){
    index = listlen + index; 
  
    if(index < 0){
      printf("Given index is greater than current list length\n"); 
      return -1; 
    }
  }

  int i; 
  for(i = 0; i < index; i++){
    if(curr == NULL){
      break; 
    }
    curr = curr->next; 
  }

  return curr->value; 
}


int list_get_index_of(list_t *l, elem value) { 
  node_t* curr = l->head;
  int index = 0; 

  while(curr != NULL){
    if(curr->value == value){
      return index; 
    }
    curr = curr->next;
    index++; 
  } 

  printf("Value is not in linked list\n"); 
  return -1; 
}

