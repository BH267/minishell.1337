/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:51:43 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/01 12:00:26 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	f;

	f = -1;
	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			f = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + i));
	if (f != -1)
		return ((char *)(s + f));
	return (NULL);
}
