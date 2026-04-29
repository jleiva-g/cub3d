/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdlib0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:52:31 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/08/28 18:16:27 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (nptr && ft_isspace(*nptr))
		nptr++;
	if (*nptr == 43 || *nptr == 45)
	{
		sign = (*nptr - 44) * -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + *nptr - 48;
		nptr++;
	}
	return (n * sign);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

static int	ilen(long n)
{
	int	len;

	len = 0;
	if (n < 1)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*fillstr(char *str, long n, int len)
{
	if (n < 0)
		n = -n;
	while (--len)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (n)
		str[len] = n + '0';
	else
		str[len] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		len;
	char	*str;

	nbr = n;
	len = ilen(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (!nbr)
	{
		str[0] = '0';
		return (str);
	}
	return (fillstr(str, nbr, len));
}
