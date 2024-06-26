/*
 * lists.c, a short linked list exercise for the C language lab in CS 105
 * 
 * <<Insert your names here!>>
 *
 */
#include <stdio.h>
#include <stdlib.h>

/* cell_t
 *    the type for a typical linked-list element with one
 *    integer
 */
typedef struct cell {
  int value;
  struct cell *next;
} cell_t;

/* makeempty
 *    frees all the elements in a list and makes the list empty
 */
void makeempty(cell_t** thelist) {

}

/* prepend
 *    creates a new element with the specified value
 *    and adds it to the front of the list
 */
void prepend(int newvalue, cell_t** thelist) {

}

/* append
 *    creates a new element with the specified value
 *    and adds it to the end of the list
 *
 * See the lab writeup for a complete line-by-line
 * description.
 */
void append(int newvalue, cell_t** thelist) {
  // allocate enough memory for a new cell 
  cell_t *newelt  = (cell_t*) malloc(sizeof(cell_t));

  // initialize the fields of the cell struct
  newelt->value = newvalue;
  newelt->next = NULL;

  if (*thelist == NULL){ // if list is currently empty
    // set new cell to be head of the list
    *thelist = newelt;
  } else { // if list has at least one element already
    // walk to the end of the list
    cell_t *p = *thelist;
    while (p->next != NULL) {
      p = p->next;
    }

    // set the pointer in the last cell to point to the new cell
    p->next = newelt;
  }
}

/* reverse
 *    rearranges the elements in a list so that they
 *    are in the opposite order
 */
void reverse(cell_t** thelist) {

}

/* printlist
 *    prints a title and then gives the value and location
 *    of each element in a list
 */
void printlist(char* title, cell_t* thelist) {
  // print the title
  printf("%s\n", title);

  // walk through the list printing each value and location
  cell_t *p;
  for (p = thelist; p != NULL; p = p->next){
    printf("%d, %p\n", p->value, p); 
  }
}

/* main
 *    demonstrates the functions above
 */
int main() {
  int j;
  cell_t *list = NULL;

  // create a list of values from 9 down to 0 and print the list
  for (j = 0; j < 10; j++) {
    prepend(j, &list);
  }
  printlist("backward", list);

  // reverse the list and print the reversed list
  reverse(&list);
  printlist("backward reversed", list);

  // empty the list and print the empty list
  makeempty(&list);
  printlist("empty", list);

  // create a list of values from 0 up to 9 and print it
  for (j = 0; j < 10; j++) {
    append(j, &list);
  }
  printlist("forward", list);

  // reverse the list and print the reversed list
  reverse(&list);
  printlist("forward reversed", list);

  // make the list empty and print the empty list
  makeempty(&list);
  printlist("empty again", list);

  return 0;
}
