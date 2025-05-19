/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:11:16 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/19 13:48:21 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"


int	check_balanced_quotes(const char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return (0);
		}
		if (input[i])
			i++;
	}
	return (1);
}


int	extract_word(const char *input, int i, char **val)
{
	int		start;
	char	quote;

	start = i;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] == quote)
				i++;
			else
				break;
		}
		else
			i++;
	}
	*val = hb_substr(input, start, i - start);
	return (i);
}

void	add_token(t_token **lst, char *value, t_token_type type, char *mask)
{
	t_token	*new;
	t_token	*tmp;

	new = (t_token *)ft_malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;
	new->mask = mask;
	if (!*lst)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

