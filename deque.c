#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define _FREE_(ptr)                                                       \
	do {                                                                  \
		free(ptr);                                                        \
		ptr = NULL;                                                       \
	} while (0)

#define TRUE  1
#define FALSE 0

static node_t *
create_node(void *data)
{
	if (data == NULL)
		return NULL;

	node_t *node = (node_t *)malloc(sizeof(node_t));
	if (node == NULL)
		return NULL;

	node->data = data;
	node->next = node->prev = NULL;
	return node;
}

int
size(deque_t *dq)
{
	assert(dq != NULL);
	return (int)dq->size;
}

int
is_empty(deque_t *dq)
{
	return dq->size == 0;
}

deque_t *
init_deque(void)
{
	deque_t *dq = (deque_t *)malloc(sizeof(deque_t));
	if (dq == NULL)
		return NULL;
	dq->size  = 0;
	dq->front = dq->back = NULL;
	return dq;
}

int
push_front(deque_t *dq, void *data)
{
	if (dq == NULL)
		return -1;

	node_t *node = create_node(data);
	if (node == NULL)
		return -1;

	/* Increment size counter before insertion
	 * Safe to do here since create_node() succeeded
	 * and remaining operations are guaranteed to succeed */
	dq->size++;

	/* if dq is empty, point front and back to node, no need to update
	 * bi-directional pointers */
	if (dq->front == NULL) {
		dq->front = node;
		dq->back  = node;
		return 0;
	}

	/* if not, update head and set up bidirectional link */
	node_t *old_front = dq->front; /* hold the pointer to current front */
	node->next		  = old_front; /* forward link: new -> old */
	old_front->prev	  = node;	   /* backward link: old <- new */
	dq->front		  = node;	   /* update front pointer */

	return 0;
}

int
push_back(deque_t *dq, void *data)
{
	if (dq == NULL)
		return -1;

	node_t *node = create_node(data);
	if (node == NULL)
		return -1;

	dq->size++;

	/* if dq back is empty, point front and back to node */
	if (dq->back == NULL) {
		dq->front = dq->back = node;
		return 0;
	}

	/* if not, hold on to old back/tail element */
	node_t *old_tail = dq->back;
	node->prev		 = old_tail;
	old_tail->next	 = node;
	dq->back		 = node;

	return 0;
}

int
pop_front(deque_t *dq)
{
	if (dq == NULL)
		return -1;

	if (is_empty(dq))
		return -1;

	/* hold the front node */
	node_t *old_front = dq->front;
	/* update front pointer */
	dq->front		  = old_front->next;

	/* handle case where this was the last node */
	if (dq->front == NULL) {
		dq->front = NULL; /* dq is now empty */
	} else {
		dq->front->prev = NULL; /* new front has no previous node */
	}
	dq->size--;

	_FREE_(old_front);

	return 0;
}

int
pop_back(deque_t *dq)
{
	if (dq == NULL)
		return -1;

	if (is_empty(dq))
		return -1;

	node_t *old_back = dq->back;
	dq->back		 = old_back->prev;

	/* handle case where this was the last node */
	if (dq->back == NULL) {
		dq->front = NULL; /* dq is now empty */
	} else {
		dq->back->next = NULL; /* new back has no next node */
	}
	dq->size--;

	_FREE_(old_back);
	return 0;
}

void *
front(deque_t *dq)
{
	if (dq == NULL)
		return NULL;

	if (dq->size == 0)
		return NULL;

	return dq->front == NULL ? NULL : dq->front->data;
}

void *
back(deque_t *dq)
{
	if (dq == NULL)
		return NULL;

	if (dq->size == 0)
		return NULL;

	return dq->back == NULL ? NULL : dq->back->data;
}

int
contains(deque_t *dq, void *data)
{
	if (dq == NULL || data == NULL)
		return FALSE;

	node_t *curr_ptr = dq->front;
	while (curr_ptr != NULL) {
		if (curr_ptr->data == data)
			return TRUE;
		curr_ptr = curr_ptr->next;
	}
	return FALSE;
}

void
free_deque(deque_t *dq)
{
	assert(dq != NULL);
	while (!is_empty(dq)) {
		pop_front(dq);
	}
	_FREE_(dq);
}
