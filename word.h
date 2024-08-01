#include <stdlib.h>
#include <string.h>

#ifndef WORD_H__
#define WORD_H__

// longest word in the english language is 45 letters, hence the character limit.
#define MAX_WORD 45

typedef struct word
{
	char str[MAX_WORD];
	int freq;
} Word;

typedef struct Node
{
	Word WordValue;
	struct Node *next;
} WordList, *WordListPtr;

WordListPtr createNode(char buffer[])
{
	Word data;
	if (buffer == NULL)
	{
	}
	else
	{
		strcpy(data.str, buffer);
	}
	data.freq = 1;

	WordListPtr newNode = (WordListPtr)malloc(sizeof(WordList));
	newNode->WordValue = data;
	newNode->next = NULL;
	return newNode;
}

int get_length(WordListPtr head)
{
	int length = 0;
	while (head)
	{
		length++;
		head = head->next;
	}
	return length;
}

WordListPtr split(WordListPtr head, int size)
{
	if (!head)
	{
		return NULL;
	}
	int i;
	// ITERATE TO MIDDLE OF LINKED LIST
	for (i = 0; i < size - 1; i++)
	{
		if (head->next != NULL)
		{
			head = head->next;
		}
		else
		{
			break;
		}
	}
	// SAVE ADDRESS OF MIDDLE OF LIST
	WordListPtr next_head = head->next;
	// SEVER LINK FROM MIDDLE
	head->next = NULL;
	return next_head;
}

WordListPtr merge(WordListPtr left, WordListPtr right, WordListPtr head)
{
	if (!head)
		return NULL; // Ensure head is not NULL

	WordListPtr current = head;
	while ((left != NULL) && (right != NULL))
	{
		if (left->WordValue.freq > right->WordValue.freq)
		{
			current->next = left;
			left = left->next;
		}
		else
		{
			current->next = right;
			right = right->next;
		}
		current = current->next;
	}
	current->next = left ? left : right;
	while (current->next != NULL)
	{
		current = current->next;
	}

	return current;
}

WordListPtr merge_sort_bottom_up(WordListPtr head)
{
	if ((head == NULL) || (head->next == NULL))
	{
		return head;
	}
	int length = get_length(head);
	int size = 1;

	WordListPtr dummy = createNode(NULL);
	if (!dummy)
		return NULL; // Ensure memory allocation was successful
	dummy->next = head;

	while (size < length)
	{
		WordListPtr current = dummy->next;
		WordListPtr tail = dummy;

		while (current != NULL)
		{
			WordListPtr left = current;
			WordListPtr right = split(left, size);
			current = split(right, size);
			tail = merge(left, right, tail); // Corrected order of arguments
		}
		size *= 2;
	}

	WordListPtr sorted_head = dummy->next;
	free(dummy);
	return sorted_head;
}

#endif
