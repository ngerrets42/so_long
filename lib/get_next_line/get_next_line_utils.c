/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/21 15:56:33 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/05/05 13:47:11 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	This strlen is different in that it'll return 0 when given a NULL-pointer
*/

size_t	gnl_strlen(const char *str)
{
	size_t	length;

	if (str == NULL)
		return (0);
	length = 0;
	while (str[length] != '\0')
		length++;
	return (length);
}

/*
**	This strjoin is different in that it'll use an element from the lst
**	It'll also free previous allocations
*/

char	*gnl_strjoin(t_gnl_lst *element, char const *buffer)
{
	size_t	length1;
	size_t	length2;
	size_t	i;
	char	*result;

	if (element->content == NULL && buffer == NULL)
		return (NULL);
	length1 = gnl_strlen(element->content);
	length2 = gnl_strlen(buffer);
	result = malloc(sizeof(char) * (length1 + length2 + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < length1 + length2)
	{
		if (i < length1)
			result[i] = (element->content)[i];
		else
			result[i] = buffer[i - length1];
		i++;
	}
	result[i] = '\0';
	free(element->content);
	return (result);
}

/*
**	Create an element for the get_next_line list
*/

t_gnl_lst	*gnl_lst_create_elem(int fd)
{
	t_gnl_lst	*element;

	element = malloc(sizeof(t_gnl_lst));
	if (element == NULL)
		return (NULL);
	element->next = NULL;
	element->fd = fd;
	element->content = NULL;
	return (element);
}

/*
**	Check to see if there's a newline in str
*/

int	gnl_check_newline(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

/*
**	Remove an element from the list and stitch the list back together
*/

void	gnl_rem_element(t_gnl_lst **head, t_gnl_lst *element)
{
	t_gnl_lst	*current;

	if (*head == element)
	{
		*head = element->next;
		free(element->content);
		free(element);
		return ;
	}
	current = *head;
	while (current != NULL)
	{
		if (current->next == element)
		{
			current->next = element->next;
			free(element->content);
			free(element);
			return ;
		}
		current = current->next;
	}
}
