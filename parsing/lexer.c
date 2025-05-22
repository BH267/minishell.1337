/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:58:41 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 11:04:49 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"

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
