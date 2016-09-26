/*
 *  doubly linked list(with guard) implementation
 *
 *
 *  (C)    2015-4    Yuanda Zhang
 */

/*
 *  modified    2014-5    Yuanda Zhang
 */

#include "doubly_linked_list.h"

/* p_list is a structure that holds the head and tail of the list */
int init_list(DLinkedList *p_list)
{
	p_list->head = malloc(sizeof(DListNode));
	p_list->tail = malloc(sizeof(DListNode));

	if ( p_list->head != NULL && p_list->tail != NULL)
	{
		p_list->head->prev = NULL;
		p_list->head->next = p_list->tail;
		p_list->head->data = NULL;
		p_list->tail->prev = p_list->head;
		p_list->tail->next = NULL;
		p_list->tail->data = NULL;
		p_list->length = 0;
	}

	return (int)(p_list->head);
}

int get_list_len(DLinkedList *p_list)
{
	return (p_list != NULL) ? p_list->length : 0;
}

pDListNode new_node_back(DLinkedList *p_list)
{
	pDListNode prev = p_list->tail->prev;
	pDListNode new_node = malloc(sizeof(DListNode));

	if ( new_node != NULL )
	{
		p_list->tail->prev = new_node;
		prev->next = new_node;
		new_node->prev = prev;
		new_node->next = p_list->tail;
		new_node->data = NULL;
		p_list->length++;
	}

	return new_node;
}

pDListNode new_node_front(DLinkedList *p_list)
{
	pDListNode next = p_list->head->next;
	pDListNode new_node = malloc(sizeof(DListNode));
	
	if ( new_node != NULL )
	{
		p_list->head->next = new_node;
		next->prev = new_node;
		new_node->prev = p_list->head;
		new_node->next = next;
		new_node->data = NULL;
		p_list->length++;
	}

	return new_node;
}

void insert_node_back(DLinkedList *p_list, pDListNode src_node, pDListNode dst_node)
{
	pDListNode prev_of_src = src_node->prev;
	pDListNode next_of_src = src_node->next;

	if ( src_node != p_list->head && src_node != p_list->tail &&
	     dst_node != p_list->tail &&
	     src_node != dst_node )
	{
		prev_of_src->next = next_of_src;
		next_of_src->prev = prev_of_src;
		src_node->next = dst_node->next;
		src_node->prev = dst_node;
		dst_node->next->prev = src_node;
		dst_node->next = src_node;
	}
}

pDListNode delete_node(DLinkedList *p_list, pDListNode node)
{
	pDListNode prev_node;
	pDListNode next_node;
	pDListNode ret = NULL;

	if ( node != p_list->head && node != p_list->tail && node != NULL)
	{
		prev_node = node->prev;
		next_node = node->next;
		prev_node->next = next_node;
		next_node->prev = prev_node;
		p_list->length--;
		free(node->data);
		free(node);
		ret = prev_node;
	}

	return ret;
}

void free_list(DLinkedList *p_list)
{
	pDListNode death = p_list->head;

	while ( death->next != p_list->tail )
		delete_node(p_list, death->next);        //when only gurad left, loop over!
	free(p_list->head);
	free(p_list->tail);
	p_list->length = 0;
	p_list->head = NULL;
	p_list->tail = NULL;
}

pDListNode seek_by_value(DLinkedList *p_list, Elem data, int(*cmp)(Elem, Elem))
{
	pDListNode target_node = p_list->head;
	pDListNode ret = NULL;

	while ( target_node->next != p_list->tail )
	{
		target_node = target_node->next;
		if ( target_node->data && cmp(target_node->data, data) )
			ret = target_node;
	}

	return ret;
}

void* assign_value(pDListNode node, Elem data, size_t count)
{
	node->data = malloc(count);
	if ( node->data )
		memcpy(node->data, data, count);

	return node->data;
}

void invert_list(DLinkedList *p_list)
{
	pDListNode trace_node = p_list->head->next;

	while ( trace_node != p_list->tail && trace_node->next != p_list->tail )
		insert_node_back(p_list, trace_node->next, p_list->head);
}

void print_list(DLinkedList *p_list, void(*print)(pListNode))
{
	pDListNode print_node = p_list->head;

	while ( print_node->next != p_list->tail )
	{
		print_node = print_node->next;
		if ( print_node->data )
			print(print_node);
		else
			printf("No data here.\n");
	}
}

void combine_two_list(DLinkedList *p_list_primary, DLinkedList *p_list_scndry)
{
	p_list_primary->tail->prev->next = p_list_scndry->head->next;
	p_list_scndry->head->next->prev = p_list_primary->tail->prev;
	free(p_list_scndry->head);
	free(p_list_primary->tail);
	p_list_primary->tail = p_list_scndry->tail;
	p_list_primary->length += p_list_scndry->length;
	p_list_scndry->length = 0;
	p_list_scndry->head = NULL;
	p_list_scndry->tail = NULL;
}

void sort_on_list(DLinkedList *p_list, int(*is_bigger)(Elem, Elem))
{
	pDListNode key_node = p_list->head->next;
	pDListNode insert_pos;

	while ( key_node != p_list->tail && key_node != NULL )
	{
		insert_pos = key_node;
		key_node = key_node->next;
		while ( insert_pos != p_list->head &&
		        key_node->data && insert_pos->data &&     //if data is NULL,no change
			is_bigger(insert_pos->data, key_node->data) == 1 )
		{
			insert_pos = insert_pos->prev;
		}
		insert_node_back(p_list, key_node, insert_pos);
	}
}