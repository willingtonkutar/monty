#include "monty.h"


/**
* find_opcode - find operation code
*
* @stack: stack pointer
* @opcode: user input opcode
* @line_number: line number
*
* Return: Always 1 (Success) or stderr
**/
int find_opcode(stack_t **stack, char *opcode, int line_number)
{
	instruction_t opcodes[] = {
		{"pall", op_pall},
		{"pop", op_pop},
		{"swap", op_swap},
		{"pint", op_pint},
		{NULL, NULL}
	};
	int i;

	for (i = 0; opcodes[i].opcode; i++)
	{
		if (strcmp(opcode, opcodes[i].opcode) == 0)
		{
			(opcodes[i].f)(stack, line_number);
			return (EXIT_SUCCESS);
		}
	}
	fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
	exit(EXIT_FAILURE);
}


/**
* main - main function
*
* @argc: number of command line arguments
* @argv: list of command line arguments
*
* Return: EXIT_SUCCESS if no errors or EXIT_FAILURE
**/

int main(__attribute__((unused)) int argc, char const *argv[])
{
	FILE *mf;
	char *buff = NULL, *opcode, *n;
	size_t lol = 0;
	int line_number = 0;
	stack_t *stack = NULL, *current;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		return (EXIT_FAILURE);
	}
	mf = fopen(argv[1], "r");
	if (mf == NULL)
	{
		fprintf(stderr, "Error: can't open file %s\n", argv[1]);
		exit(1);
	}
	while ((getline(&buff, &lol, mf)) != -1)
	{
		line_number++;
		opcode = strtok(buff, DELIMITER);
		if (opcode == NULL || opcode[0] == '#')
			continue;
		if (!strcmp(opcode, "nop"))
			continue;
		else if (!strcmp(opcode, "push"))
		{
			n = strtok(NULL, DELIMITER);
			op_push(&stack, n, line_number);
		}
		else
			find_opcode(&stack, opcode, line_number);
	}
	fclose(mf);
	free(buff);
	while (stack != NULL)
	{
		current = stack;
		stack = stack->next;
		free(current);
	}
	return (0);
}
