/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:56:17 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/09/11 18:09:00 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putstr(const char *s, int fd)
{
	if (!s)
		return (ft_putstr("(null)", fd));
	return (write(fd, s, ft_strlen(s)));
}

int	ft_putnbr(int n, int fd)
{
	long	nbr;
	int		len;

	nbr = n;
	len = 0;
	if (nbr < 0)
	{
		len += ft_putchar('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
		len += ft_putnbr(nbr / 10, fd);
	len += ft_putchar((nbr % 10) + '0', fd);
	return (len);
}

int	ft_putunsigned(unsigned int n, int fd)
{
	int		len;

	len = 0;
	if (n > 9)
		len += ft_putunsigned(n / 10, fd);
	len += ft_putchar((n % 10) + '0', fd);
	return (len);
}

int	ft_puthex(unsigned long n, const char lower, int fd)
{
	int	len;

	len = 0;
	if (n > 15)
		len += ft_puthex(n / 16, lower, fd);
	if (lower == 'x' && n % 16 > 9)
		len += ft_putchar(n % 16 + 'a' - 10, fd);
	else if (n % 16 > 9)
		len += ft_putchar(n % 16 + 'A' - 10, fd);
	else
		len += ft_putchar(n % 16 + '0', fd);
	return (len);
}

int	ft_putptr(uintptr_t ptr, int fd)
{
	int	len;

	if (!ptr)
		return (ft_putstr("(nil)", fd));
	len = ft_putstr("0x", fd);
	len += ft_puthex(ptr, 'x', fd);
	return (len);
}
