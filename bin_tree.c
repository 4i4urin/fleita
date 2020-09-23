#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int data;
	struct node* left;
	struct node* right;	
} node_t;


void bt_insert(node_t** head, int key, int data)
{
	if (*head == NULL)
	{
		*head = (node_t*)malloc(sizeof(node_t));
		if (*head == NULL) return;
		(*head)->key = key;
		(*head)->data = data;
		(*head)->left = NULL;
		(*head)->right = NULL;
	} else
	{
		if (key < (*head)->key) 
			bt_insert(&((*head)->left), key, data);
		else if (key > (*head)->key)
			bt_insert(&((*head)->right), key, data);
		else
			(*head)->data = data;
	}
} 


void bt_print(node_t* head)
{
	if (head == NULL)
	{
		printf("NULL\n");
		return;
	} else 
	{
		printf("key = %d, data = %d\n", head->key, head-> data);
		printf("left: \n");
		bt_print(head->left);
		printf("right:\n");
		bt_print(head->right);
	}

}

node_t* bt_search(node_t* head, int key)
{
	if (head == NULL) return NULL;
	if (key == head->key) return head;
	else if (key < head->key) return bt_search(head->left, key);
	else if (key > head->key) return bt_search(head->right, key);
	return NULL;
}

node_t* bt_minimum(node_t* head)
{
	if (head->left == NULL)
		return head;
	return bt_minimum(head->left);
}

node_t* bt_delite(node_t* head, int key)
{
	if (head == NULL) 
		return head;
	else if (head->key > key) // рекурсивно удалить из правого поддерева
		head->left = bt_delite(head->left, key);
	else if (head->key < key) // рекурсивно удалить из left поддерева
		head->right = bt_delite(head->right, key);
	else if (head->key == key) // удалить со смешением
	{
		if (head->left != NULL && head->right != NULL)
		{
			head->key = (bt_minimum(head->right))->key;
			head->right = bt_delite(head->right, head->key);
		} else
		{
			if (head->left != NULL)
			{
				node_t* tmp = head;
				head = head->left;
				free(tmp);
			}
			else if (head->right != NULL)
			{
				node_t* tmp = head;
				head = head->right;
				free(tmp);
			}
			else
			{
				free(head);
				head = NULL;
			}
		}
	}
	return head;
}

int main(void)
{
	node_t* head = NULL;
	bt_insert(&head, 42, 5);
	// printf("head key = %d, val = %d\n", head->key, head->data);
	bt_insert(&head, 50, 8);
	bt_insert(&head, 30, 57);
	bt_insert(&head, 40, 89);
	bt_insert(&head, 35, 845);
	bt_insert(&head, 45, 893);
	bt_insert(&head, 60, 556);
	bt_insert(&head, 55, 35);
	bt_print(head);

	printf("%d\n", (bt_minimum(head))->key);
	// node_t* tmp = bt_search(head, 35);
	// if (tmp != NULL)
	// {
	// 	printf("Yes value = %d\n", tmp->data);
	// }
	printf("\n\n");
	head = bt_delite(head, 42);
	bt_print(head);
	printf("\n\n");
	head = bt_delite(head, 30);
	bt_print(head);
	printf("\n\n");

	bt_insert(&head, 42, 920);
	bt_insert(&head, 45, 920);
	bt_insert(&head, 70, 920);

	bt_print(head);
	printf("\n\n");
	return 0;
}
