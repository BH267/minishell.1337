/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_mask_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:55:12 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:55:03 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../header/mini.h"
#include "../libhb/libhb.h"
#include "../ms.h"
#include "expand.h"

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

int	copy_new_mask(char *dst, char *src, int pos, int len)
{
	int	j;
	int	i;

	j = 0;
	i = pos;
	while (j < len)
	{
		dst[i++] = src[j++];
	}
	return (i);
}

void	copy_suffix(t_suffix_copy *sc)
{
	int	k;

	k = 0;
	while (k < sc->len)
	{
		sc->dst[sc->dst_pos++] = sc->src[sc->src_pos + k++];
	}
	sc->dst[sc->dst_pos] = '\0';
}
