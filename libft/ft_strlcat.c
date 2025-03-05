/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:38:09 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/09 13:46:27 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ld;
	size_t	ls;
	size_t	lt;
	size_t	i;

	if (!dst && size == 0)
		return (ft_strlen(src));
	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	lt = ld + ls;
	if (size <= ld)
		return (size + ls);
	i = 0;
	while (i < (size - ld - 1) && src[i])
	{
		dst[i + ld] = src[i];
		i++;
	}
	dst[i + ld] = '\0';
	return (lt);
}
