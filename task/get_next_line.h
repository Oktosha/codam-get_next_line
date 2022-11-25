/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 17:25:05 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/25 14:59:19 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <sys/types.h>

char	*get_next_line(int fd);

typedef struct s_string_builder
{
	char	*data;
	ssize_t	length;
	ssize_t	capacity;
}	t_string_builder;

typedef struct s_read_state
{
	char	buffer[BUFFER_SIZE];
	int		len;
	int		pos;
}	t_read_state;

typedef struct s_local_read_state
{
	ssize_t				read_return_value;
	t_string_builder	builder;
	char				*result;
	ssize_t				i;
}	t_local_read_state;

void	sb_init(t_string_builder *string_builder);
int		sb_append(t_string_builder *string_builder, char *data,
			ssize_t data_length);
char	*sb_get_string(t_string_builder string_builder);
void	sb_clear(t_string_builder *string_builder);

#endif
