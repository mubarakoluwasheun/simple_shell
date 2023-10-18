#include "shell.h"

/**
 * add_endnode - Adds a node to the end of a linked list.
 * @head: A pointer to the head of the list
 * @path: The directory path for the new node
 *
 * Return: Returns (endnode) on SUCCESS and (NULL) on FAILURE
 */
list_node *append_node(list_node **head, char *path)
{
	list_node *tmp;
	list_node *append_node = malloc(sizeof(list_node));

	if (!append_node)
		return (NULL);

	append_node->dir = path;
	append_node->next = NULL;

	if (*head)
	{
		tmp = *head;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = append_node;
	}
	else
		*head = append_node;

	return (append_node);
}

/**
 * free_list - Frees a list_path linked list
 * @head: The head of the list_path list
 */
void free_list(list_node *head)
{
	list_node *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
