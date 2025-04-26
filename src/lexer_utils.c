/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:23:08 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:07:07 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/lexer_token.h"
#include "../libhb/libhb.h"
#include "../ft_malloc/ft_malloc.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	skip_spaces(const char *s, int i)
{
	while (s[i] && is_space(s[i]))
		i++;
	return (i);
}

int	get_op_len(const char *s)
{
	if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
		return (2);
	return (1);
}

t_token_type	get_operator_type(const char *s)
{
	if (s[0] == '|' && s[1] != '|')
		return (TOKEN_PIPE);
	if (s[0] == '<' && s[1] == '<')
		return (TOKEN_HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (TOKEN_APPEND);
	if (s[0] == '<')
		return (TOKEN_REDIR_IN);
	if (s[0] == '>')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}
