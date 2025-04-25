/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:41 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/25 17:18:40 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/token.h"
#include "../include/tokenizer.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

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
		if (input[i] == '\'' || input[i] == '"')
		{
			i = handle_quoted(input, i, &lst);
			if (i == -1)
				return (lst);
		}
		else if (is_operator(input[i]))
			i = handle_operator(input, i, &lst);
		else
			i = handle_word(input, i, &lst);
	}
	return (lst);
}
