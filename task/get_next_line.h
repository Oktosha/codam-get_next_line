/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkolodze <dkolodze@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/08 17:25:05 by dkolodze      #+#    #+#                 */
/*   Updated: 2022/11/18 15:56:25 by dkolodze      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

#include <sys/types.h>

char	*get_next_line(int fd);

typedef struct s_string_node
{
	char					*data;
	ssize_t					data_length;
	struct s_string_node	*next;
}	t_string_node;

typedef struct s_string_builder
{
	struct s_string_node	*first;
	struct s_string_node	*last;
}	t_string_builder;

void sb_init(t_string_builder *string_builder);
int sb_append(t_string_builder *string_builder, char *data, ssize_t data_length);
char *sb_get_string(t_string_builder string_builder);
void sb_clear(t_string_builder *string_builder);

#endif