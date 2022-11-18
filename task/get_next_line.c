/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 17:32:42 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/18 16:11:55 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	stored_length = 0;
	static int	pos = 0;

	ssize_t				read_return_value;
	t_string_builder	result_builder;
	char				*result;
	ssize_t					i;

	sb_init(&result_builder);
	while(1)
	{
		if (pos == stored_length)
		{
			read_return_value = read(fd, buffer, BUFFER_SIZE);
			if (read_return_value == -1)
			{
				sb_clear(&result_builder);
				return NULL;
			}
			if (read_return_value == 0)
			{
				result = sb_get_string(result_builder);
				sb_clear(&result_builder);
				return result;
			}
			pos = 0;
			stored_length = read_return_value;
		}
		i = 0;
		while(i + pos < stored_length && buffer[i + pos] != '\n')
			++i;
		if (i + pos < stored_length)
		{
			sb_append(&result_builder, buffer + pos, i + 1);
			result = sb_get_string(result_builder);
			pos += i + 1;
			sb_clear(result_builder);
			return result;
		}
		sb_append(&result_builder, buffer + pos, i);
		pos += i;
	}

}
