/**
 * -------------------------------------
 * @project a5
 * @file dllist.h
 * @author Sameer Abdullah
 * @version 2025-02-14
 * -------------------------------------
 */

 #ifndef DLL_H
 #define DLL_H
 
 typedef struct node {
   char data;
   struct node *prev;  
   struct node *next;
 } NODE;
 
 typedef struct dllist {
   int length;
   NODE *start;
   NODE *end;
 } DLL;
 
 NODE *dll_node(char value);
 void dll_insert_start(DLL *dllp, NODE *np);
 void dll_insert_end(DLL *dllp, NODE *np);
 void dll_delete_start(DLL *dllp);
 void dll_delete_end(DLL *dllp);
 void dll_clean(DLL *dllp);
 
 #endif