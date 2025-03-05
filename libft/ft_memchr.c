/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:56:31 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/10 16:41:17 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			index;

	tmp = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (tmp[index] == (unsigned char)c)
			return (tmp + index);
		index++;
	}
	return (NULL);
}
