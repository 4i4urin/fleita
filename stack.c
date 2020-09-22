#include <stdio.h>
#include <stdlib.h>

struct stack
{
	struct stack* next;
	int data;	
};

struct stack* push(struct stack*, int);
void list(struct stack*);
struct stack* pop(struct stack*);
int push_or_pop(void);
int string_cmd(char*, char*);
int number_from_input(void);

int main(void)
{
	struct stack* head = NULL;
	printf("Example: push 40, list, pop\n");
	int push_pop = push_or_pop();
	while (push_pop)
	{
		if (push_pop == 1)
		{
			int x = number_from_input();
			head = push(head, x);
		}else if (push_pop == 2)
		{
			head = pop(head);
			list(head);
		}
		else 
			list(head);
		push_pop = push_or_pop();
	}
	return 0;
}

struct stack* pop(struct stack* head)
{
	if (head != NULL)
	{
		struct stack* delite = head;
		head = head->next;
		free(delite);
	}
	return head;
}

struct stack* push(struct stack* head, int x)
{
	struct stack* new = malloc(sizeof(struct stack));
	if (new == NULL)
		exit(100);
	new->data = x;
	new->next = head;
	return new;
}

void list(struct stack* ptr)
{
	while(ptr != NULL)
	{
		printf("%d\n", ptr->data);
		ptr = ptr->next;
	}
}

int number_from_input(void)
{
	int number = 0, c;
	while((c = getchar()) != '\n')
	{
		number *= 10;
		if (c >= '0' && c <= '9')
			number = number + (c - '0');
		else
		{
			printf("Input doesn't integer\n");
			exit(200);
		}
	}
	return number;
}

int push_or_pop(void)
{
	char input[6];
	int i, c;
	for (i = 0; i < 5 && (c = getchar()) != '\n'; ++i)
		input[i] = c;
	input[i] = '\0';
	if (string_cmd(input, "push "))
		return 1;
	else if (string_cmd(input, "pop"))
		return 2;
	else if (string_cmd(input, "list"))
		return 3;
	else
		return 0;
}

int string_cmd(char* s1, char* s2)
{
	int flag = 1, i;
	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; ++i)
	{
		if (s1[i] != s2[i])
		{
			flag = 0;
			return flag;
		}
	}
	if (s1[i] != s2[i])
		flag = 0;
	return flag;
}
