#include "monty.h"
/**
 * func_add - this function adds the top two elements of the stack.
 * @head: pointer to stack head
 * @counter: the line number
*/
void func_add(stack_t **head, unsigned int counter)
{
	stack_t *h;
	int len = 0, ax;

	h = *head;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	ax = h->n + h->next->n;
	h->next->n = ax;
	*head = h->next;
	free(h);
}

/**
  *func_nop - this function do nothing
  *@head: pointer stack head
  *@counter: the line number
 */
void func_nop(stack_t **head, unsigned int counter)
{
	(void) counter;
	(void) head;
}

/**
  *func_sub - this functiom if for sustration
  *@head: pointer stack head
  *@counter: the line number
 */
void func_sub(stack_t **head, unsigned int counter)
{
	stack_t *ax;
	int sus, nodes;

	ax = *head;
	for (nodes = 0; ax != NULL; nodes++)
		ax = ax->next;
	if (nodes < 2)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	ax = *head;
	sus = ax->next->n - ax->n;
	ax->next->n = sus;
	*head = ax->next;
	free(ax);
}

/**
* free_stack - this function frees a doubly linked list
* @head: pointer to head of the stack
*/
void free_stack(stack_t *head)
{
	stack_t *ax;

	ax = head;
	while (head)
	{
		ax = head->next;
		free(head);
		head = ax;
	}
}

/**
* execute - this function executes the opcode
* @stack: head linked list (stack)
* @counter: the line counter
* @file: poiner to monty file
* @content: line content
*/
int execute(char *content, stack_t **stack, unsigned int counter, FILE *file)
{
	instruction_t opst[] = {
				{"push", func_push}, {"pall", func_pall}, {"pint", func_pint},
				{"pop", func_pop},
				{"swap", func_swap},
				{"add", func_add},
				{"nop", func_nop},
				{"sub", func_sub},
				{NULL, NULL}
				};
	unsigned int i = 0;
	char *op;

	op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	bus.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{	opst[i].f(stack, counter);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{ fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free(content);
		free_stack(*stack);
		exit(EXIT_FAILURE); }
	return (1);
}
