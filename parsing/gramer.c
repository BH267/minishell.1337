/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gramer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 04:21:47 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 11:02:26 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"

static int	is_redir_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	check_pipe_and_redir(t_token *tok, int *expect_word)
{
	if (tok->type == TOKEN_PIPE)
	{
		if (!tok->next || tok->next->type == TOKEN_PIPE)
			return (0);
		*expect_word = 1;
	}
	else if (tok->type == TOKEN_WORD || (tok->type == TOKEN_HEREDOC && tok->next
			&& tok->next->type == TOKEN_WORD))
		*expect_word = 0;
	else if (is_redir_token(tok->type))
	{
		if ((!tok->next || tok->next->type != TOKEN_WORD))
			return (0);
	}
	return (1);
}

int	check_grammar(t_token *tok)
{
	int	expect_word;

	expect_word = 1;
	if (!tok || tok->type == TOKEN_PIPE)
		return (0);
	while (tok)
	{
		if (!check_pipe_and_redir(tok, &expect_word))
			return (0);
		if (tok->type == TOKEN_WORD && tok->value && tok->value[0] == '|'
			&& tok->value[1] == '\0')
			return (0);
		if (is_redir_token(tok->type))
			tok = tok->next;
		tok = tok->next;
	}
	if (expect_word)
		return (0);
	return (1);
}
