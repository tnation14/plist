// Zach Lockett-Streiff and Taylor Nation
//  Incrementally testing functionalityof our plist
#include <stdio.h>
#include <stdlib.h>
#include "plist.h"

#define TEST_TYPE int
//#define TEST_TYPE short
//#define TEST_TYPE char

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
  int i;
  printf("mylist: ");
  for(i = 0; i<10; i++){
    append(mylist,(void *)i);
	printf("%d ",(int)get(mylist,i));
  }
  printf("\nSetting mylist[3] to 100...done!\n");
  set(mylist,3,(void *)100);
  printf("Before changes: \n");
  for(i = 0; i<size(mylist); i++){
	printf("%d ",(int)get(mylist,i));
  }
  printf("\nInserting 20 at mylist[1]...done!\n");
  insert_list(mylist,1,(void *)20);
  
  printf("After insert_list:\n");
  for(i = 0; i<size(mylist); i++){
    printf("%d ",(int)get(mylist,i));
  }
  printf("\n");
  free_list(mylist);
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
