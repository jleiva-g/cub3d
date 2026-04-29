/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdio2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 15:00:06 by jleiva-g          #+#    #+#             */
/*   Updated: 2025/09/11 18:15:40 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	handle_specifier(va_list args, const char c, int fd)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int), fd));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *), fd));
	if (c == 'p')
		return (ft_putptr(va_arg(args, uintptr_t), fd));
	if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(args, int), fd));
	if (c == 'u')
		return (ft_putunsigned(va_arg(args, unsigned int), fd));
	if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(args, unsigned int), c, fd));
	if (c == '%')
		return (ft_putchar('%', fd));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len += handle_specifier(args, *format, STDIN_FILENO);
		}
		else
			len += ft_putchar(*format, STDIN_FILENO);
		format++;
	}
	va_end(args);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		len;

	va_start(args, format);
	len = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len += handle_specifier(args, *format, fd);
		}
		else
			len += ft_putchar(*format, fd);
		format++;
	}
	va_end(args);
	return (len);
}

int	find_lf(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_strjoin(char *s1, const char *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*dst;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	dst = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!dst)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dst, s1, s1len + 1);
	ft_strlcat(dst, s2, s1len + s2len + 1);
	free(s1);
	return (dst);
}
