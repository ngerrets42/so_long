/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:43:33 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/05/29 15:59:36 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*head;
	t_list		*element;

	if (lst == NULL)
		return (NULL);
	head = ft_lstnew(f(lst->content));
	if (head == NULL)
		return (NULL);
	lst = lst->next;
	element = head;
	while (lst != NULL)
	{
		element->next = ft_lstnew(f(lst->content));
		if (element == NULL)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		element = element->next;
		lst = lst->next;
	}
	element->next = NULL;
	return (head);
}
