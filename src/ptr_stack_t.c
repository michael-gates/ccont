#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

#include <debug.h>
#include <ptr_stack_t.h>
#define DEFAULT_CAPACITY 256



ptr_stack_t * ptr_stack_create() {
	ptr_stack_t * stack = ALLOC(sizeof(ptr_stack_t));
	memset(stack, 0, sizeof(ptr_stack_t));

	stack->capacity = DEFAULT_CAPACITY;
	stack->begin = ALLOC(stack->capacity);

	return stack;
}

void ptr_stack_destroy(ptr_stack_t * stack) {
	assert(stack != NULL);

	FREE(stack->begin);
	FREE(stack);
}

void ptr_stack_push(ptr_stack_t * stack, void * ptr) {
	assert(stack != NULL);

	size_t capNeeded = compute_capacity(ptr_stack_size(stack), DEFAULT_CAPACITY);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);

		// FUNC_DEBUG("realloc");
	}

	*ptr_stack_end(stack) = ptr;
	stack->count++;
}

void ptr_stack_pop(ptr_stack_t * stack) {
	assert(stack != NULL);

	stack->count--;

	size_t capNeeded = compute_capacity(ptr_stack_size(stack), DEFAULT_CAPACITY);
	if(stack->capacity != capNeeded) {
		stack->capacity = capNeeded;
		stack->begin = REALLOC(stack->begin, stack->capacity);
		// FUNC_DEBUG("realloc");
	}
}

void * ptr_stack_back(ptr_stack_t * stack) {
	assert(stack != NULL);
	assert(stack->count > 0);

	return *(ptr_stack_end(stack) - 1);
}



#ifndef NDEBUG
#include <stdio.h>

void ptr_stack_debug(ptr_stack_t * stack) {
	assert(stack != NULL);
	FUNC_DEBUG("");

	fprintf(stderr, "\tbegin: %p\n", stack->begin);
	fprintf(stderr, "\tend: %p\n", ptr_stack_end(stack));
	fprintf(stderr, "\tcount: %zu\n", stack->count);
	fprintf(stderr, "\tsize: %zu\n", ptr_stack_size(stack));
	fprintf(stderr, "\tcapacity: %zu\n", stack->capacity);

	fputc('\n', stderr);
}


#endif