/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handle_word.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:29:35 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 21:40:05 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

int	is_word_start(t_token *token, int i, int in_word)
{
	return ((token->mask[i] == MASK_EXPANSION && !is_space(token->value[i]))
		|| (token->mask[i] != MASK_EXPANSION && !in_word));
}

int	is_word_end(t_token *token, int i, int in_word)
{
	return (token->mask[i] == MASK_EXPANSION && is_space(token->value[i])
		&& in_word);
}

void	handle_token_char(t_word_params *wp)
{
	if (is_word_start(wp->token, wp->i, *(wp->in_word)))
	{
		if (!(*(wp->in_word)))
		{
			wp->start = wp->i;
			*(wp->in_word) = 1;
		}
	}
	else if (is_word_end(wp->token, wp->i, *(wp->in_word)))
	{
		store_word(wp);
		*(wp->in_word) = 0;
	}
}

void	store_word(t_word_params *wp)
{
	wp->data->mask_args[*(wp->j)] = submem(wp->token->mask,
			wp->start, wp->i - wp->start);
	wp->data->args[*(wp->j)] = hb_substr(wp->token->value,
			wp->start, wp->i - wp->start);
	(*(wp->j))++;
}
