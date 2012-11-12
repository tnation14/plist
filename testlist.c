// Zach Lockett-Streiff and Taylor Nation
//  Incrementally testing functionalityof our plist
#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

//#define TEST_TYPE int
//#define TEST_TYPE short
#define TEST_TYPE char

//#define SIGNED_OR_NOT  unsigned
#define SIGNED_OR_NOT  

//static void print_list(plist mylist);
//static void print_list(plist mylist);
/*****************************************************************/
int main () {
  system("clear");
  plist mylist;

  SIGNED_OR_NOT TEST_TYPE x;
  
  if(!(mylist = init_list(sizeof(TEST_TYPE)))) {
        printf("init failed\n");
        exit(1);
  }
  x = 6;
  
  printf("size of mylist before free: %d\n",size(mylist));
  free_list(mylist);
  printf("size of mylist after free: %d\n",size(mylist));

  return 0;
}
/*****************************************************************/
// add comment and implement this function if helpful (it will be).
// feel free to add more parameters if helpful...this is your test code. 
//
// Your print_list code will have to check for different types to 
// have special case printf statmens with the correct % format specifiers
// (you cannot just do this in one generic printf statement...you want
// printf to print out the right type)
//static void print_list(plist mylist) {}
