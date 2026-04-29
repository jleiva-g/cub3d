/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleiva-g <jleiva-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 18:33:11 by jleiva-g          #+#    #+#             */
/*   Updated: 2026/04/23 18:33:37 by jleiva-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strcat(char *dst, const char *src)
{
	size_t	dstlen;
	size_t	srclen;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	ft_strlcpy(dst + dstlen, src, srclen + 1);
	return (dstlen + srclen);
}
