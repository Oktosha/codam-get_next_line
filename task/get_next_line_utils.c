/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 15:22:38 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/18 16:05:53 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/types.h>
#include "get_next_line.h"

void sb_init(t_string_builder *string_builder)
{
	string_builder->first = NULL;
	string_builder->last = NULL;
}

char *str_duplicate(char *data, ssize_t data_length)
{
	char *result;
	ssize_t position;

	result = malloc(data_length);
	if (result == NULL)
		return NULL;
	position = 0;
	while(position < data_length)
	{
		result[position] = data[position];
		++position;
	}
	return result;
}

int sb_append(t_string_builder *string_builder, char *data, ssize_t data_length)
{
	t_string_node	*node = malloc(sizeof(t_string_node));
	if (node == NULL)
		return -1;
	node->data = duplicate(data, data_length);
	if (node->data == NULL)
	{
		free(node);
		return -2;
	}
	node->data_length = data_length;
	node->next = NULL;
	if (string_builder->first == NULL)
	{
		string_builder->first = node;
		string_builder->last = node;
	}
	else
	{
		string_builder->last->next = node;
		string_builder->last = node;
	}
	return 0;
}

// returns NULL if no nodes are stored
char *sb_get_string(t_string_builder string_builder)
{
	ssize_t i;
	ssize_t j;
	char	*result;
	t_string_node *node;

	if (string_builder.first == NULL)
		return NULL;
	i = 0;
	node = string_builder.first;
	while(node != NULL)
	{
		i += node->data_length;
		node = node->next;
	}
	result = malloc(sizeof(char) * (i + 1));
	if (result == NULL)
		return NULL;
	node = string_builder.first;
	i = 0;
	while(node != NULL)
	{
		j = 0;
		while(j < node->data_length)
			result[i + j] = node->data[i++];
		i += node->data_length;
		node = node->next;
	}
	result[i] = '\0';
	return result;
}

void sb_clear(t_string_builder *string_builder)
{
	t_string_node *node = string_builder->first;
	t_string_node *temp = NULL;
	while(node != NULL)
	{
		free(node->data);
		temp = node->next;
		free(node);
		node = temp;
	}
	string_builder->first = NULL;
	string_builder->last = NULL;
}