#include "monty.h"
/**
 * addnode - this function add node to the head stack
 * @head: pointer to head of the stack
 * @n: the new value
*/
void addnode(stack_t **head, int n)
{

	stack_t *new_node, *ax;

	ax = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{ printf("Error\n");
		exit(0); }
	if (ax)
		ax->prev = new_node;
	new_node->n = n;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}

/**
 * addqueue - this function add node to the tail stack
 * @n: the new value
 * @head: the head of the stack
*/
void addqueue(stack_t **head, int n)
{
	stack_t *new_node, *ax;

	ax = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		printf("Error\n");
	}
	new_node->n = n;
	new_node->next = NULL;
	if (ax)
	{
		while (ax->next)
			ax = ax->next;
	}
	if (!ax)
	{
		*head = new_node;
		new_node->prev = NULL;
	}
	else
	{
		ax->next = new_node;
		new_node->prev = ax;
	}
}
