/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 15:22:38 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/25 15:12:10 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <sys/types.h>
#include "get_next_line.h"

void	my_memcpy(char *dst, char *src, ssize_t n)
{
	ssize_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		++i;
	}
}

void	sb_init(t_string_builder *string_builder)
{
	string_builder->data = NULL;
	string_builder->length = 0;
	string_builder->capacity = 0;
}

int	sb_append(t_string_builder *string_builder, char *data, ssize_t len)
{
	char	*tmp;
	ssize_t	new_capacity;

	if (len + string_builder->length > string_builder->capacity)
	{
		new_capacity = string_builder->capacity * 2;
		if (new_capacity < len + string_builder->length)
			new_capacity = (len + string_builder->length) * 2;
		tmp = malloc(new_capacity);
		if (tmp == NULL)
			return (-1);
		my_memcpy(tmp, string_builder->data, string_builder->length);
		free(string_builder->data);
		string_builder->data = tmp;
		string_builder->capacity = new_capacity;
	}
	my_memcpy(string_builder->data + string_builder->length, data, len);
	string_builder->length = string_builder->length + len;
	return (0);
}

// returns NULL if no data is stored
char	*sb_get_string(t_string_builder string_builder)
{
	char	*result;

	if (string_builder.data == NULL)
		return (NULL);
	result = malloc(string_builder.length + 1);
	if (result == NULL)
		return (NULL);
	my_memcpy(result, string_builder.data, string_builder.length);
	result[string_builder.length] = '\0';
	return (result);
}

void	sb_clear(t_string_builder *string_builder)
{
	free(string_builder->data);
	string_builder->data = NULL;
	string_builder->length = 0;
	string_builder->capacity = 0;
}
