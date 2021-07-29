/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   str.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/06/23 12:01:02 by ngerrets      #+#    #+#                 */
/*   Updated: 2021/07/06 20:36:21 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"
#include <unistd.h>

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}

static void	ft_putstr_fd(const char *str, int fd)
{
	size_t	length;

	if (str == NULL)
		return ;
	length = 0;
	while (str[length] != '\0')
		length++;
	write(fd, str, sizeof(char) * length);
}

static void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else if (n < 0)
	{
		c = '-';
		write(fd, &c, 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		c = '0' + n;
		write(fd, &c, sizeof(char));
	}
}

void	put(const char *str, const int *n)
{
	if (str != NULL)
		ft_putstr_fd(str, 1);
	if (n != NULL)
		ft_putnbr_fd(*n, 1);
	write(1, &"\n", sizeof(char));
}
