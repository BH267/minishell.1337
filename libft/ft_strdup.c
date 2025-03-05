/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:00:37 by ybouanan          #+#    #+#             */
/*   Updated: 2024/11/10 17:51:52 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(s);
	tmp = malloc(len + 1);
	if (tmp == NULL)
		return (NULL);
	ft_memcpy(tmp, s, len);
	tmp[len] = '\0';
	return (tmp);
}
