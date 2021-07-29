/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/20 14:49:52 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/05/05 13:47:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	Find the element in the list with the corresponding fd
*/

static t_gnl_lst	*gnl_lst_get_from_fd(t_gnl_lst **head, int fd)
{
	t_gnl_lst	*ret;

	ret = *head;
	while (ret != NULL)
	{
		if (ret->fd == fd)
		{
			return (ret);
		}
		ret = ret->next;
	}
	ret = gnl_lst_create_elem(fd);
	ret->next = *head;
	*head = ret;
	return (ret);
}

/*
**	Read into a buffer from a file-descriptor (fd)
*/

static size_t	gnl_get_buffer(int fd, t_gnl_lst *element)
{
	ssize_t	length;
	char	*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL || element == NULL)
		return (-1);
	length = 1;
	while (gnl_check_newline(element->content) == 0 && length != 0)
	{
		length = read(fd, buffer, BUFFER_SIZE);
		if (length == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[length] = '\0';
		element->content = gnl_strjoin(element, buffer);
	}
	free(buffer);
	return (length);
}

/*
**	Remove and reallocate the buffer of the given element
*/

static char	*gnl_realloc_content(t_gnl_lst *element)
{
	char	*new_content;
	size_t	length;
	size_t	i;
	size_t	j;

	i = 0;
	while ((element->content)[i] != '\n' && (element->content)[i] != '\0')
		i++;
	if ((element->content)[i] == '\0')
	{
		free(element->content);
		return (NULL);
	}
	length = gnl_strlen(&(element->content)[i + 1]) + 1;
	new_content = malloc(length * sizeof(char));
	if (new_content == NULL)
		return (NULL);
	j = 0;
	while (j < length)
	{
		new_content[j] = (element->content)[i + j + 1];
		j++;
	}
	free(element->content);
	return (new_content);
}

/*
**	Allocate and give back the line
*/

static char	*gnl_alloc_line(t_gnl_lst *element)
{
	size_t	length;
	size_t	i;
	char	*ret;
	char	*content;

	content = element->content;
	length = 0;
	while (content[length] != '\n' && content[length] != '\0')
		length++;
	ret = malloc((length + 1) * sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ret[i] = content[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*
**	Read the next line from given filedescriptor (fd) and
**	put the result in char *line.
**	Returns 1 on succes, 0 on End of File and -1 on Error
*/

int	get_next_line(int fd, char **line)
{
	static t_gnl_lst	*head;
	t_gnl_lst			*element;
	ssize_t				length;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (GNL_ERROR);
	element = gnl_lst_get_from_fd(&head, fd);
	length = gnl_get_buffer(fd, element);
	if (length == -1)
	{
		gnl_rem_element(&head, element);
		return (GNL_ERROR);
	}
	*line = gnl_alloc_line(element);
	element->content = gnl_realloc_content(element);
	if (*line == NULL || element->content == NULL || length == 0)
	{
		gnl_rem_element(&head, element);
		if (length == 0)
			return (GNL_EOF);
		return (GNL_ERROR);
	}
	return (GNL_SUCCES);
}
