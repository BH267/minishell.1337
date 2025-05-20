/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitcmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:01:11 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/20 12:13:03 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../expand/expand.h"
#include "../header/lexer_token.h"
#include "../ms.h"
#include <ctype.h>

void	add_token_ae(t_token **lst, t_data_splited *data, int index)
{
	t_token	*new;

	new = (t_token *)ft_malloc(sizeof(t_token));
	new->value = data->args[index];
	new->type = TOKEN_WORD;
	new->mask = data->mask_args[index];
	new->next = NULL;
	new->flag = 42;
	if (*lst)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
	}
	else
		*lst = new;
}

void	replace_args(t_token *tok, t_data_splited *data)
{
	int		i;
	t_token	*current;
	t_token	*next_orig;

	i = 0;
	current = tok;
	next_orig = tok->next;
	if (!data || !data->args || !data->args[0])
		return ;
	current->mask = data->mask_args[i];
	current->value = data->args[i++];
	while (data->args[i])
	{
		add_token_ae(&current, data, i);
		current = current->next;
		i++;
	}
	current->next = next_orig;
}


void	split_tokens_by_mask(t_token *tokens)
{
	t_token			*tok;
	t_data_splited	*data;

	tok = tokens;
	while (tok)
	{
		if (tok->flag == 42)
		{
			data = split_args(tok);
			replace_args(tok, data);
		}
		tok = tok->next;
	}
}
