/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:21:08 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/07 21:15:06 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	sl1;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	sl1 = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = sl1;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	res = (char *)malloc(end - start + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1 + start, end - start + 1);
	res[end - start] = '\0';
	return (res);
}
