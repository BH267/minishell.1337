/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:11:16 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:11:17 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

int	extract_quoted(const char *input, int i, char **val)
{
	char	quote;
	int		start;

	quote = input[i];
	start = ++i;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] != quote)
		return (-1);
	*val = hb_substr(input, start, i - start);
	return (i + 1);
}

int	extract_word(const char *input, int i, char **val)
{
	int	start;

	start = i;
	while (input[i] && !is_space(input[i]) && !is_operator(input[i]))
		i++;
	*val = hb_substr(input, start, i - start);
	return (i);
}

void	add_token(t_token **lst, char *value, t_token_type type)
{
	t_token	*new;
	t_token	*tmp;

	new = (t_token *)ft_malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;
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
