/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/24 14:39:29 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/06/23 14:10:42 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"

void	ft_lstadd_front(t_list **lst, t_list *element)
{
	if (lst != NULL && element != NULL)
		element->next = *lst;
	*lst = element;
}
