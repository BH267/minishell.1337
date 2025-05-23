/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_process_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 21:56:25 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/23 22:13:40 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	init_word_params(t_word_params *wp, t_data_splited *data,
		t_token *token, int *j)
{
	wp->token = token;
	wp->data = data;
	wp->j = j;
	wp->start = 0;
}

void	process_token_word(t_word_params *wp, int *in_word, int i)
{
	wp->i = i;
	wp->in_word = in_word;
	handle_token_char(wp);
}

void	handle_last_word(t_word_params *wp, int in_word, int i)
{
	if (in_word)
	{
		wp->i = i;
		store_word(wp);
	}
}
