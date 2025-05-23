/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mask_utils_extra.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 22:14:50 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 22:16:05 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*c_new_mask(char *value, char type)
{
	int		i;
	char	*new_mask;

	type = (type & ~MASK_EXPANSION) | MASK_EXPANSION;
	i = 0;
	new_mask = (char *)ft_malloc(hb_strlen(value) + 1);
	if (!new_mask)
		return (NULL);
	while (value[i])
	{
		new_mask[i] = type;
		i++;
	}
	new_mask[i] = '\0';
	return (new_mask);
}

void	copy_prefix_mask(char *dst, char *src, int prefix_len)
{
	int	i;

	i = 0;
	while (i < prefix_len)
	{
		dst[i] = src[i];
		i++;
	}
}
