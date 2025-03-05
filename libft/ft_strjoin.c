/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:20:56 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/07 21:13:32 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	x1;
	size_t	x2;

	if (!s1 || !s2)
		return (NULL);
	x1 = ft_strlen(s1);
	x2 = ft_strlen(s2);
	res = (char *)malloc(x1 + x2 + 1);
	if (!res)
		return (NULL);
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	res -= (x1 + x2);
	return (res);
}
