/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:13:05 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:13:23 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	count_args_using_mask(t_token *token)
{
	int (i), (count_args), (max), (in_word);
	i = 0;
	count_args = 0;
	in_word = 0;
	max = hb_strlen(token->value);
	while (i < max)
	{
		if (token->mask[i] == MASK_EXPANSION && !is_space(token->value[i]))
		{
			if (!in_word)
			{
				count_args++;
				in_word = 1;
			}
		}
		else if (token->mask[i] == MASK_EXPANSION && is_space(token->value[i]))
			in_word = 0;
		else if (!in_word)
		{
			count_args++;
			in_word = 1;
		}
		i++;
	}
	return (count_args);
}

char	*submem(char *str, int start, int len)
{
	char	*sub;
	int		i;

	sub = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
