/*
 *  doubly linked list interface modified by single linked list
 *
 *
 *  (C)    2015-4    Yuanda Zhang
 */

/*
 *  modified    2014-5    Yuanda Zhang
 */

#ifndef __DOUBLY_LIST_H__
#define __DOUBLY_LIST_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* data in the doubly linked list
 * void * make the list common used
 */
typedef void * Elem;

/* definition of doubly linked list */
typedef struct list{
	Elem data;
	struct list *next;
	struct list *prev;
}DListNode;

typedef DListNode *pDListNode;

/* data structure stores the doubly linked list's head pointer and tail pointer */
typedef struct{
	DListNode *head;
	DListNode *tail;
	int      length;
}DLinkedList;

//// fundamental operatoin on doubly linked list ////

#define list_head(list)            ( (list) ? (list)->head : NULL )
#define list_tail(list)            ( (list) ? (list)->tail : NULL )
#define next_list_node(node)        ( (node)->next )
#define prev_list_node(node)        ( (node)->prev )
#define is_valid_node(node, list)   ( (node) != NULL && (node)->next != list_tail(list) )
#define data_list_node(node, type)  ( (type)((node)->data) )

/*
 * function:        initialize the doubly linked list
 * return:          return 0 if fail
 * parameter:       the list
 * call:            none
 * called by:       none
 */
int init_list(DLinkedList *p_list);

/* 
 * function:  get the length of the list
 * return:    return the length
 * parameter: the list
 * call:      none
 * called by: none
 */
int get_list_len(DLinkedList *p_list);

/*
 * function:        add a new node to the end of doubly linked list
 * return:          return the address of the new node(NULL means fail)
 * parameter:       the list
 * call:            none
 * called by:       none
 */

pDListNode new_node_back(DLinkedList *p_list);

/*
 * function:        add a new node to the beginning(at the back of guard) of doubly linked list 
 * return:          return the address of the new node(NULL means fail)
 * parameter:       the list
 * call:            none
 * called by:       none
 */
pDListNode new_node_front(DLinkedList *p_list);

/*
 * function:        insert a existing node of the list to somewhere in the list
 * return:          none
 * parameter:       1. the list;  2. the node moved;  3. the node moved toward
 * call:            none
 * called by:       invert_list
 * others:          guard can't be moved
 */
void insert_node_back(DLinkedList *p_list, pDListNode src_node, pDListNode dst_node);

/*
 * function:        delete a node from the list
 * return:          return NULL if fail, else return the address of previous node
 * parameter:       1. the list;  2. the node would be deleted
 * call:            none
 * called by:       free_list
 * others:          NULL and guard can't be deleted, so return NULL.
 */
pDListNode delete_node(DLinkedList *p_list, pDListNode node);

/*
 * function:        free the space of all nodes including guard
 * return:          none
 * parameter:       the list
 * call:            delete_node
 * called by:       none
 */
void free_list(DLinkedList *p_list);

/*
 * function:        seek node by given value
 * return:          return NULL if can't find the node, else return the address
 * parameter:       1. the list; 2. the data used to seek; 3.the function to compare
 * call:            none
 * called by:       none
 */
pDListNode seek_by_value(DLinkedList *p_list, Elem data, int (*cmp)(Elem, Elem));

/*
 * function:       assign value to a node
 * return:         return 0 if fail
 * parameter:      1. the node; 2. void pointer to data; 3. bytes of data
 * call:           none
 * called by:      none
 * others:         same as that in single linked list
 */
void* assign_value(pDListNode node, Elem data, size_t count);

/*
 * function:        invert the list
 * return:          none
 * parameter:       1. the list
 * call:            insert_node_back
 * called by:       none
 * description:     call insert_node_back to finish this work, in every iteration insert the "third" node
 *                  (guard is first, we record the "second" so we can always get third readily) to guard's back.
 */
void invert_list(DLinkedList *p_list);

/*
 * function:        print the list
 * return:          none
 * parameter:       1. the list; 2. the function to print list
 * call:            none
 * called by:       none
 */
void print_list(DLinkedList *p_list, void (*print)(pListNode));

/*
 * function:        conbine two lists into one (connect the second to the primary's ass) and disable the second
 * return:          none
 * parameter:       1. the primary list;  2. the secondary list
 * call:            none
 * called by:       none
 */
void combine_two_list(DLinkedList *p_list_primary, DLinkedList *p_list_scndry);

/*
* function:        insert sort on doubly linked list in ascending order
* return:          none
* parameter:       1. the list; 2.function to compare
* call:            none
* called by:       none
*/
void sort_on_list(DLinkedList *p_list, int(*is_bigger)(Elem, Elem));

#endif
