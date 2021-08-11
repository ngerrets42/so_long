/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:40:54 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/06/23 14:11:05 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_back(t_list **lst, t_list *element)
{
	t_list	*last;

	if (lst == NULL)
		return ;
	last = ft_lstlast(*lst);
	if (last != NULL)
		last->next = element;
	else
		*lst = element;
}
