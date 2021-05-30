//LinkedList.c
#include "LinkedList.h"
#include <stdlib.h>
#include <memory.h>

// Create
void Create(LinkedList *linkedList)
{
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

// AppendFromHead
Node *AppendFromHead(LinkedList *linkedList, void *object, size_t size)
{

	linkedList->current = (Node *)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = linkedList->current;
	if (linkedList->head != NULL)
	{
		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

// AppendFromTail
Node *AppendFromTail(LinkedList *linkedList, void *object, size_t size)
{

	linkedList->current = (Node *)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = linkedList->current;
	if (linkedList->tail != NULL)
	{
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

// InsertBefore
Node *InsertBefore(LinkedList *linkedList, Node *index, void *object, size_t size)
{

	linkedList->current = (Node *)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = index;
	if (linkedList->head != index)
	{
		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

// InsertAfter
Node *InsertAfter(LinkedList *linkedList, Node *index, void *object, size_t size)
{

	linkedList->current = (Node *)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = index;
	if (linkedList->tail != index)
	{
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;

	return linkedList->current;
}

// Delete
Node *Delete(LinkedList *linkedList, Node *index)
{

	if (linkedList->head != index && linkedList->tail != index)
	{
		index->previous->next = index->next;
		index->next->previous = index->previous;
		linkedList->current = index->next;
	}
	else if (linkedList->head == index && linkedList->tail != index)
	{
		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = index->next;
	}
	else if (linkedList->head != index && linkedList->tail == index)
	{
		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

// DeleteFromHead
Node *DeleteFromHead(LinkedList *linkedList)
{
	Node *index;

	index = linkedList->head;
	if (linkedList->head != linkedList->tail)
	{
		index->next->previous = index->next;
		linkedList->head = index->next;
		linkedList->current = index->next;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

// DeleteFromTail
Node *DeleteFromTail(LinkedList *linkedList)
{
	Node *index;

	index = linkedList->tail;
	if (linkedList->tail != linkedList->head)
	{
		index->previous->next = index->previous;
		linkedList->tail = index->previous;
		linkedList->current = index->previous;
	}
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;

	return index;
}

// DeleteAllItems
void DeleteAllItems(LinkedList *linkedList)
{
	Node *it;
	Node *previous = NULL;

	it = linkedList->head;

	while (it != previous)
	{
		linkedList->head = it->next;
		previous = it;
		if (it != NULL)
		{
			free(it);
		}
		it = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
}

// LinearSearchUnique
Node *LinearSearchUnique(LinkedList *linkedList, void *key, int (*compare)(void *, void *))
{
	Node *index = NULL;
	Node *it;
	Node *previous = NULL;

	it = linkedList->head;
	while (it != previous && compare(it + 1, key) != 0)
	{
		previous = it;
		it = it->next;
	}
	if (it != previous)
	{
		index = it;
	}
	return index;
}

// LinearSearchDuplicate
void LinearSearchDuplicate(LinkedList *linkedList, void *key, Node **(*indexes), Long *count,
						   size_t size, int (*compare)(void *, void *))
{
	Node *previous = NULL;
	Node *it;
	Long i = 0;
	*count = 0;

	*indexes = (Node * (*)) calloc(linkedList->length, sizeof(Node *));
	it = linkedList->head;
	while (it != previous)
	{
		if (compare(it + 1, key) == 0)
		{
			(*indexes)[i] = it;
			i++;
			(*count)++;
		}
		previous = it;
		it = it->next;
	}
}

// GetAt
void GetAt(LinkedList *linkedList, Node *index, void *object, size_t size)
{

	memcpy(object, index + 1, size);
}

// First
Node *First(LinkedList *linkedList)
{

	linkedList->current = linkedList->head;

	return linkedList->current;
}

//: Previous
Node *Previous(LinkedList *linkedList)
{

	linkedList->current = linkedList->current->previous;

	return linkedList->current;
}

// Next
Node *Next(LinkedList *linkedList)
{

	linkedList->current = linkedList->current->next;

	return linkedList->current;
}

// Last
Node *Last(LinkedList *linkedList)
{

	linkedList->current = linkedList->tail;

	return linkedList->current;
}

// Move
Node *Move(LinkedList *linkedList, Node *index)
{

	linkedList->current = index;

	return linkedList->current;
}

// Destroy
void Destroy(LinkedList *linkedList)
{
	Node *it;
	Node *previous = NULL;

	it = linkedList->head;
	while (it != previous)
	{
		linkedList->head = it->next;
		previous = it;
		if (it != NULL)
		{
			free(it);
		}
		it = linkedList->head;
	}
}