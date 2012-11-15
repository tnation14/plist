//
// TODO: add a top-level comment here
// all functions should be well commented!
//
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

// the "private" underlying implementation of a python 
// list is defined by this struct type
struct python_list {
  int capacity;  // total current capacity 
  int size;      // current size of the list
  int type_size;  // number of bytes stored in each bucket
  unsigned char  *array;
};

// the begining capcity size and grow size (20 bytes)
#define START_SIZE  20

// NOTE: YOU DO NOT NEED TO USE MY DEBUG PRINT MACROS IN YOUR SOLN
//       these are just here for your information, you can use them
//       if you'd like
// These are C macros defined to either call printf or not
// this is one way to easily enable/disable debug output in your code 
// // the various versions are for different number of arguments to printf
// to use: 
//   (1) call PRINTX macros in your code instead of printf, for example:
//       PRINT2("the values of x and y are %d and %d\n", x,y);
//   (2) uncomment the #define to enable printing, comment out to disable
//       (it is currently disabled)

// #define DEBUG_PRINTS
#ifdef DEBUG_PRINTS
#define PRINT0(s) printf(s)
#define PRINT1(s,x1) printf(s, x1)
#define PRINT2(s,x1, x2) printf(s, x1, x2)
#define PRINT3(s,x1, x2, x3) printf(s, x1, x2, x3)
#define PRINT4(s,x1, x2, x3, x4) printf(s, x1, x2, x3, x4)
#else
#define PRINT0(s) 
#define PRINT1(s,x1) 
#define PRINT2(s,x1, x2) 
#define PRINT3(s,x1, x2, x3) 
#define PRINT4(s,x1, x2, x3, x4) 
#endif

/*********************************************************/
//
// init_list: creates an initial empty list 
//             allocates the starting capacity  
//   type_size: the number of bytes in the type stored in each bucket 
//              (the caller should pass in sizeof(type))
//               only support sizes 1, 2 and 4 byte values
//               any other value is an error
//   returns: 0 (NULL) on error or a pointer to a python_list that
//            was created and initialized on success
//
struct python_list *init_list(int type_size) {
  printf("type_size: %d\n",type_size);
  if (type_size != 1 && type_size != 2 && type_size != 4) {
    printf("Invalid type size.\n");
    return NULL;
  }

  struct python_list *plist;
  
  plist = malloc(sizeof(struct python_list));
  if (plist == NULL) {
    printf("malloc failed");
    exit(1);
  }

  plist->array = malloc(type_size*START_SIZE);
  // for some reason, sizeof(plist->array) won't evaluate to 20 (8). Why?
  if (plist->array == NULL) {
    printf("malloc failed");
    exit(1);
  }

  plist->capacity = START_SIZE/type_size;
  plist->size = 0;
  plist->type_size = type_size;
  
  return plist;
}
/*********************************************************/
//
//  free_list: frees all memory associated with a plist
//             
//       list: the plist whose memory will be freed
//
//    returns: nothing
void free_list(plist list) {
  free(list->array);
  free(list);
  list = NULL;
}
/*********************************************************/
//
//     size: returns the size of the array
//             
//     list: the plist whose size will be returned
//
//  returns: the size of plist
int size(plist list) {   // TODO: Figure out that "Invalid read of size 4"
  return list->size;     //       on this line
}
/*********************************************************/
//
//     append: appends value to the end of list
//             increments size
//             increases capacity of array if necessary
//             
//             
//       list: the plist to which value will be appended
//
//      value: the value to be appended to list
//
//    returns: nothing
void append(plist list, void *value) {
  // Add additional element to list->array, we can do this at least
  // once without repercussion
  
  // Determine offset from existing elements of list->array
  int shift = list->size * list->type_size;
  
  memcpy(list->array+shift, &value, list->type_size); //test w/ w/o the &
  list->size++;
  // Check if an additional call will exceed capacity
  if (list->type_size * list->size+1 >= list->capacity) {
    expand_capacity(list);
  }
}
/*********************************************************/
//
//     expand_capacity: expands the capacity of the array
//             
//                list: the plist whose capacity will be expanded
//
//             returns: the new plist
void expand_capacity(plist list) {

  if (!(list->array = realloc(list->array,2*START_SIZE))){
    printf("realloc failed");
    exit(1);
  }
  
}

/* Insert_list places an element in list[index], shifting
   all other list elements one place to the right.
   
   list: The list being modified.
   index: the index at which to insert the value.
   value: value being added to the list. */
void insert_list(plist list, int index, void *value){
	if(!(0<=index || index<list->size)){
	  printf("Index %d out of range.\n",index);
	  exit(1);
	}
	int i;
	// Moves every element one list (NOT ARRAY) bucket
	// to the right. 
	for(i=list->size-1;i>=index;i--){
	  // Expand capacity if we're at the end of the list's
	  // Underlying array.
	  if (list->type_size * list->size+1 >= list->capacity) {
        expand_capacity(list);
  	  }	  
  	  set(list,i+1,get(list,i));
    }
    // Put the new value into a memory bucket, increase size.
    set(list,index,value);
    list->size++;
}
/* Insert_list writes an element into list[index].
   
   list: The list being modified.
   index: the index at which to write the value.
   value: value being added to the list. */
   
void set(plist list, int index, void *value){
  if(!(0<=index || index<list->size)){
	  printf("Index %d out of range.\n",index);
	  exit(1);
	}
    /*Finds the actual array index. The array in the plist
    struct has 20n buckets, and every (type_size)
    buckets holds one actual list element. Therefore,
    the index of the element we want is the index passed
    to us*type_size. */
    
  int shift = index * list->type_size;
  
  //Overwrites (type_size) bytes of memory in order to store
  //value.
  memcpy(list->array+shift, &value, list->type_size); 
  
}

/* Get returns the index at list[index].
   list: list being modified.
   index: value to return. */

void *get(plist list, int index){
  if(!(0<=index || index<list->size)){
	  printf("Index %d out of range.\n",index);
	  exit(1);
	}
	
  /*Finds the actual array index. The array in the plist
    struct has 20n buckets, and every (type_size)
    buckets holds one actual list element. Therefore,
    the index of the element we want is the index passed
    to us*type_size. */
    
    
  int real_index = index * list->type_size;

  return (void *)list->array[real_index];  
}