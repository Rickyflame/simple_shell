#include "main.h"

/**
 * add_alias_end - add a node to the end of a linked list
 * @head: pointer to the head of a list
 * @name: name of the new alias
 * @value: value of the new alias to be added
 * Return: if error occured NULL otherwise a pointer
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}
	new_node->value = value;
	_strcpy(new_node->name, name);
	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * add_node_end - adds a node to the end of a linked list
 * @head: pointer to the head of the list
 * @dir: directory path for new node to contain
 * Return: if error occurs NULL otherwise a pointer
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);
	new_node->dir = dir;
	new_node->next = NULL;
	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}
/**
 * free_alias_list - frees an alias_t linked list
 * @head: head of the alias_t list
 * Return: void has no return value
 */
void free_alias_list(alias_t *head)
{
	alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}
/**
 * free_list - frees a list_t linked list
 * @head: head of the list_t list
 * Return: void has no return value
 */
void free_list(list_t *head)
{
	list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
