#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

List* init_history() {
  List *list = (List*) malloc(sizeof(List));//allocate memory for the list
  list->root = NULL; //the list is initially empty
  return list;
}

void add_history(List *list, char *str){
   Item *newItem = (Item*) malloc(sizeof(Item));
   newItem->str = strdup(str);//duplicate the input string

   //find the last item in the list and assign the id
   if(list->root == NULL){
     newItem->id = 1;
     newItem->next = NULL;
     list->root = newItem;
   }
   else{
     Item *current = list->root;
     while (current->next!= NULL){
       current = current->next;
     }
     newItem->id = current->id +1;
     newItem->next = NULL;
     current->next = newItem;
   }
}

char *get_history(List *list, int id){
  Item *current = list->root;

  while(current != NULL){
    if (current->id == id){
      return current->str;
    }
    current = current->next;
  }
  return NULL;//return null if no matching id is found
}

void print_history(List *list){
  Item *current = list->root;
  while(current != NULL){
    printf("%d: %s\n", current->id, current->str);
    current = current->next;
  }
}

void free_history(List *list){
  Item *current = list->root;

  while(current != NULL){
    Item *next = current->next;
    free(current->str);//free the duplicated string
    free(current); //free the item structure
    current = next;
  }
  free(list);// free the list structure itself
}
