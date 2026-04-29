/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:57:40 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/08/29 17:31:54 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*dst;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1, s1len + 1);
	ft_strlcat(dst, s2, s1len + s2len + 1);
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;

	if (!s1)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	end = ft_strlen(s1);
	while (end > 0 && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr(s1, 0, end));
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dst;

	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	while (*s)
		f(i++, s++);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = ft_strlen(src);
	dest[i] = '\0';
	while (i--)
		dest[i] = src[i];
	return (dest);
}
