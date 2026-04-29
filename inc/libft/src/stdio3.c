/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 18:17:24 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/10/09 15:08:55 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	*free_str(char *str)
{
	free(str);
	return (NULL);
}

static void	free_rest(char **rest, int fd)
{
	if (rest[fd])
		free(rest[fd]);
	rest[fd] = NULL;
}

static char	*next_line(char **rest, int next_lf)
{
	char	*line;
	char	*temp;

	line = ft_substr(*rest, 0, next_lf + 1);
	temp = ft_strdup(&(*rest)[next_lf + 1]);
	free(*rest);
	if (!temp)
		return (free_str(line));
	*rest = temp;
	return (line);
}

static char	*gnl_read(int fd, char **rest)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && find_lf(rest[fd]) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free_rest(rest, fd);
			return (free_str(buffer));
		}
		buffer[bytes_read] = '\0';
		rest[fd] = gnl_strjoin(rest[fd], buffer);
	}
	free(buffer);
	return (rest[fd]);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*line;
	int			next_lf;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (rest[0])
			free(rest[0]);
		return (NULL);
	}
	rest[fd] = gnl_read(fd, rest);
	if (!rest[fd])
		return (NULL);
	next_lf = find_lf(rest[fd]);
	if (next_lf > -1)
		return (next_line(&rest[fd], next_lf));
	if (rest[fd] && *rest[fd])
	{
		line = ft_strdup(rest[fd]);
		free_rest(rest, fd);
		return (line);
	}
	free_rest(rest, fd);
	return (NULL);
}
