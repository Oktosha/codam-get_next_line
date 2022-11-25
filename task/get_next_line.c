/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 17:32:42 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/21 22:40:31 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "get_next_line.h"

char	*sb_pop_all(t_string_builder *string_builder)
{
	char	*result;

	result = sb_get_string(*string_builder);
	sb_clear(string_builder);
	return (result);
}

ssize_t	pos_after_end(ssize_t start, ssize_t len, char *str)
{
	ssize_t	i;

	i = 1;
	while (i + start < len && str[i + start - 1] != '\n')
		++i;
	return (i);
}

char	*get_next_line(int fd)
{
	static t_read_state	state = {};
	t_local_read_state	locals;

	sb_init(&locals.builder);
	while (1)
	{
		if (state.pos == state.len)
		{
			locals.read_return_value = read(fd, state.buffer, BUFFER_SIZE);
			if (locals.read_return_value == -1)
				return (sb_clear(&locals.builder));
			if (locals.read_return_value == 0)
				return (sb_pop_all(&locals.builder));
			state.pos = 0;
			state.len = locals.read_return_value;
		}
		locals.i = pos_after_end(state.pos, state.len, state.buffer);
		if (sb_append(&locals.builder, state.buffer + state.pos, locals.i) < 0)
			return (sb_clear(&locals.builder));
		state.pos += locals.i;
		if (state.buffer[state.pos - 1] == '\n')
			return (sb_pop_all(&locals.builder));
	}
}
