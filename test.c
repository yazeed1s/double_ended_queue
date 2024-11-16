#include "deque.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define TRUE  1
#define FALSE 0

void
test_basic_operations()
{
	printf("testing basic operations...\n");

	printf("testing initialize...\n");
	deque_t *dq = init_deque();
	assert(dq != NULL);
	assert(is_empty(dq) == TRUE);
	assert(size(dq) == 0);
	printf("testing initialize OK...\n");

	printf("testing push front...\n");
	int *nums = malloc(sizeof(int) * 3);
	nums[0]	  = 10;
	nums[1]	  = 20;
	nums[2]	  = 30;

	assert(push_front(dq, &nums[0]) == 0);
	assert(size(dq) == 1);
	assert(*(int *)front(dq) == 10);
	assert(*(int *)back(dq) == 10);
	printf("testing push front OK...\n");

	printf("testing push back...\n");
	assert(push_back(dq, &nums[1]) == 0);
	assert(size(dq) == 2);
	assert(*(int *)front(dq) == 10);
	assert(*(int *)back(dq) == 20);
	printf("testing push back OK...\n");

	printf("testing second push front...\n");
	assert(push_front(dq, &nums[2]) == 0);
	assert(size(dq) == 3);
	assert(*(int *)front(dq) == 30);
	assert(*(int *)back(dq) == 20);
	printf("testing second push front OK...\n");

	printf("testing contains...\n");
	assert(contains(dq, &nums[0]) == TRUE);
	assert(contains(dq, &nums[1]) == TRUE);
	assert(contains(dq, &nums[2]) == TRUE);
	int dummy = 100;
	assert(contains(dq, &dummy) == FALSE);
	printf("testing contains OK...\n");

	printf("testing pop back...\n");
	assert(pop_back(dq) == 0);
	assert(size(dq) == 2);
	assert(*(int *)back(dq) == 10);
	printf("testing pop back OK...\n");

	printf("testing pop front...\n");
	assert(pop_front(dq) == 0);
	assert(size(dq) == 1);
	assert(*(int *)front(dq) == 10);
	assert(*(int *)back(dq) == 10);
	printf("testing pop front OK...\n");

	printf("testing deque cleanup...\n");
	free_deque(dq);
	free(nums);
	printf("testing deque cleanup OK...\n");

	printf("basic operations tests passed!\n");
}

void
test_edge_cases()
{
	printf("\ntesting edge cases...\n");

	printf("testing empty deque initialization...\n");
	deque_t *dq = init_deque();
	assert(dq != NULL);
	printf("testing empty deque initialization OK...\n");

	printf("testing operations on empty deque...\n");
	assert(front(dq) == NULL);
	assert(back(dq) == NULL);
	assert(pop_front(dq) == -1);
	assert(pop_back(dq) == -1);
	printf("testing operations on empty deque OK...\n");

	printf("testing NULL data handling...\n");
	assert(push_front(dq, NULL) == -1);
	assert(push_back(dq, NULL) == -1);
	assert(contains(dq, NULL) == FALSE);
	printf("testing NULL data handling OK...\n");

	printf("testing deque cleanup for edge cases...\n");
	free_deque(dq);
	printf("testing deque cleanup for edge cases OK...\n");

	printf("testing operations on NULL deque...\n");
	assert(push_front(NULL, NULL) == -1);
	assert(push_back(NULL, NULL) == -1);
	assert(pop_front(NULL) == -1);
	assert(pop_back(NULL) == -1);
	assert(front(NULL) == NULL);
	assert(back(NULL) == NULL);
	assert(contains(NULL, NULL) == FALSE);
	printf("testing operations on NULL deque OK...\n");

	printf("edge cases tests passed!\n");
}

int
main()
{
	printf("Starting deque tests...\n\n");
	test_basic_operations();
	test_edge_cases();
	printf("\nAll tests completed successfully!\n");
	return 0;
}
