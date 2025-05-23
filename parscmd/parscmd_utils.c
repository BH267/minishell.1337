/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parscmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:42:56 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 10:52:24 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../expand/expand.h"
#include "../header/lexer_token.h"
#include "../ms.h"
#include <ctype.h>

int	has_quotes_mask_zero(t_token *tok)
{
	int	i;

	i = 0;
	if (!tok || !tok->value || !tok->mask)
		return (0);
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
			return (1);
		i++;
	}
	return (0);
}

int	count_zeromask_quotes(t_token *tok)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
			count++;
		i++;
	}
	return (count);
}

static char	*create_new_value(t_token *tok, int quote_count)
{
	char	*new_value;
	int		original_length;
	int		i;
	int		k;

	original_length = hb_strlen(tok->value);
	new_value = (char *)ft_malloc(sizeof(char) * (original_length - quote_count
				+ 1));
	if (!new_value)
		return (NULL);
	i = 0;
	k = 0;
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
		{
			i++;
			continue ;
		}
		new_value[k++] = tok->value[i++];
	}
	new_value[k] = '\0';
	return (new_value);
}

void	delete_zeromask_quotes(t_token *tok)
{
	int		quote_count;
	char	*new_value;

	if (!tok || !tok->value || !tok->mask)
		return ;
	quote_count = count_zeromask_quotes(tok);
	if (quote_count == 0)
		return ;
	new_value = create_new_value(tok, quote_count);
	if (!new_value)
		return ;
	tok->value = new_value;
}

void	clear_quotes(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (has_quotes_mask_zero(tok))
		{
			delete_zeromask_quotes(tok);
		}
		tok = tok->next;
	}
}
