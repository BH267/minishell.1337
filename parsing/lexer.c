/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:41 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/08 13:46:50 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"

// Only handle_word should handle quoted and unquoted segments as a single word
// so we remove the direct call to handle_quoted here

t_token	*lexer(const char *input)
{
	int		i;
	t_token	*lst;

	i = 0;
	lst = NULL;
	while (input[i])
	{
		i = skip_spaces(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			i = handle_operator(input, i, &lst);
		else
			i = handle_word(input, i, &lst);
	}
	return (lst);
}
