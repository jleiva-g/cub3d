/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:38:29 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/08/28 18:16:31 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *) s;
	while (n--)
		a[n] = c;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *) dest;
	b = (unsigned char *) src;
	if (!n || src == dest)
		return (dest);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) dest;
	b = (unsigned char *) src;
	if (src < dest)
		while (n--)
			a[n] = b[n];
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
