/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:41:16 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/08/28 18:16:33 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (size <= dstlen)
		return (size + srclen);
	ft_strlcpy(dst + dstlen, src, size - dstlen);
	return (dstlen + srclen);
}

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	unsigned char	b;

	a = (unsigned char *) s;
	b = (unsigned char) c;
	while (n--)
	{
		if (*a == b)
			return ((void *) a);
		a++;
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

char	*ft_strrchr(const char *s, int c)
{
	char			*last;
	unsigned char	a;

	a = (unsigned char) c;
	last = NULL;
	while (*s)
	{
		if (*s == a)
			last = (char *) s;
		s++;
	}
	if (*s == a)
		last = (char *) s;
	return (last);
}
