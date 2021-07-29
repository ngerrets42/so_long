/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 13:11:44 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/05/05 13:47:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# define GNL_ERROR -1
# define GNL_EOF 0
# define GNL_SUCCES 1

# include <unistd.h>
# include <stdlib.h>

typedef struct s_gnl_lst
{
	char				*content;
	int					fd;
	struct s_gnl_lst	*next;
}						t_gnl_lst;

size_t					gnl_strlen(const char *str);
char					*gnl_strjoin(t_gnl_lst *element, char const *buffer);
t_gnl_lst				*gnl_lst_create_elem(int fd);
void					gnl_rem_element(t_gnl_lst **head, t_gnl_lst *element);
int						gnl_check_newline(char *str);
int						get_next_line(int fd, char **line);

#endif
