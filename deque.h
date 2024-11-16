#ifndef DEQUE_H
#define DEQUE_H
#include <stddef.h>
/* about the container https://en.wikipedia.org/wiki/Double-ended_queue */
/* deque here is implemented using a doubly linked list rather than a  */
/*
 * algoritm complexity:
 *  - pushing element at front or back takes O(1) time
 *  - poping element from front or back takes O(1) time
 *  - poping element from front or back takes O(1) time
 *  - searching for an element takes O(n) at worse; not bad but this
 *       container isn't meant for fast and effecient search.
 *  - since the underlying ds is a doubly-linked-list, there will be
 *       allocation/deallocation overhead
 */
typedef struct node_t node_t;
struct node_t {
	void   *data; /* void pointer to data; cast to desired type when it is
					 returnd from a function*/
	node_t *next; /* pointer to next node*/
	node_t *prev; /* pointer to prev node */
};

typedef struct {
	node_t *front; /* pointer to front element of containter */
	node_t *back;  /* pointer to the element at the back */
	size_t	size;  /* total size */
} deque_t;

// clang-format off
deque_t *init_deque(void);               /* allocates and returns the container, can return NULL so check */
int push_front(deque_t *dq, void *data); /* push data to the front, returns 0 on success, -1 otherwise */
int push_back(deque_t *dq, void *data);  /* push data to the back, returns 0 on success, -1 otherwise */
int pop_front(deque_t *dq);              /* removes data from the front, returns 0 on success, -1 otherwise */
int pop_back(deque_t *dq);               /* removes data from the back, returns 0 on success, -1 otherwise */
void *front(deque_t *dq);                /* retrives data from the front without removing it, returns NULL on error */
void *back(deque_t *dq);                 /* retrives data from the back without removing it, returns NULL on error */
int contains(deque_t *dq, void *data);   /* searches for an element in o(n) at worst, returns true if found, false otherwise */
int size(deque_t *dq);                   /* returns the size */
int is_empty(deque_t *dq);               /* returns true if dq is empty, false otherwise */
void free_deque(deque_t *dq);
// clang-format on
#endif
