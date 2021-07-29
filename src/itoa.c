/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   itoa.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/29 16:23:33 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:25:45 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	static_absi(int n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		digits;
	int		nbr;
	int		negative;

	digits = 1;
	nbr = n;
	while (nbr / 10 != 0)
	{
		nbr /= 10;
		digits++;
	}
	negative = (n < 0);
	result = malloc(sizeof(char) * (digits + negative + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '-';
	result[digits + negative] = '\0';
	while (digits > 0)
	{
		result[digits - 1 + negative] = '0' + static_absi(n % 10);
		n /= 10;
		digits--;
	}
	return (result);
}
