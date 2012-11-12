// TODO: * Add top-level comment here
//       * Add function prototypes as you incrementally implement and 
//         test your solution.  
//       * Remove my comments to you from these files (like this one)
//
#ifndef _PLIST_H_
#define _PLIST_H_

// This is an incomplete type definition:  the compiler only knows
// that plist is an alias for the type (struct python_list *).  
// Code can be compiled that declares and passes varaibles of type plist
// to functions because the compiler knows how much space is needed
// to store a pointer value.  However, the fields of the underlying
// struct pointed to by plist variables cannot cannot be accessed.
// This allows us to hide the underlying python list implementation
// from the user of this library (this is good).
//
// The type plist should be used in fuction prototypes here (instead of 
// using struct python_list *): users of your library should declare 
// variables of type plist, not (struct python_list *).
typedef struct python_list * plist;


//
// init_list: creates an initial empty list 
//   type_size: the number of bytes in the type stored in 
//              each list bucket.  Must be one of 1, 2 or 4
//   returns: 0 on error, an initilized empty plist on success 
plist init_list(int type_size);

//
//  free_list: frees all memory associated with a plist
//             
//       list: the plist whose memory will be freed
//
//    returns: nothing
void free_list(plist list);

//
//     size: returns the size of the array
//             
//     list: the plist whose size will be returned
//
//  returns: the size of plist
int size(plist list);

//
//     append: appends value to the end of list
//             
//       list: the plist to which value will be appended
//
//      value: the value to be appended to list
//
//    returns: nothing
void append(plist list, void *value);

//
//     expand_capacity: expands the capacity of the array
//             
//                list: the plist whose capacity will be expanded
//
//             returns: the new plist
void expand_capacity(plist list);
#endif
