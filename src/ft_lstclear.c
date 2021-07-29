/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:42:43 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/05/29 15:59:02 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	while (lst != NULL && *lst != NULL)
	{
		next = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = next;
	}
	lst = NULL;
}
