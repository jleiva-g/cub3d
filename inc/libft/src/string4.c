/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:04:16 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/04/23 18:32:58 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s != c && (!s[1] || s[1] == c))
			words++;
		s++;
	}
	return (words);
}

static char	**splitalloc(int words)
{
	char	**split;

	split = malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	while (words--)
		split[words] = NULL;
	return (split);
}

void	*free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	split = splitalloc(count_words(s, c));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			j = 0;
			while (s[j] && s[j] != c)
				j++;
			split[i] = ft_substr(s, 0, j);
			if (!split[i])
				return (free_split(split));
			s += j;
			i++;
		}
		else
			s++;
	}
	return (split);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	while (*a && (*a == *b))
	{
		a++;
		b++;
	}
	return (*a - *b);
}
