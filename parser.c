/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/26 02:17:51 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/lexer_token.h"
#include "ft_malloc/ft_malloc.h"

static void	parse_args(t_cmd *cmd, t_token **tok)
{
	int argc;
	int i;

	argc = count_args(*tok);
	if (argc > 0)
	{
		cmd->args = tokens_to_args(*tok, argc);
		i = 0;
		while (i < argc && *tok)
		{
			*tok = (*tok)->next;
			i++;
		}
	}
}

static void	parse_redirs(t_cmd *cmd, t_token **tok)
{
	while (*tok && is_redir((*tok)->type))
	{
		fill_redir(cmd, *tok);
		*tok = (*tok)->next;
		if (*tok)
			*tok = (*tok)->next;
	}
}

static int	is_pipe(t_token *tok)
{
	return (tok && tok->type == TOKEN_PIPE);
}

static void	advance_pipe(t_cmd **cmd, t_token **tok)
{
	if (is_pipe(*tok))
	{
		(*cmd)->next = new_cmd();
		*cmd = (*cmd)->next;
		*tok = (*tok)->next;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd *cmd_head;
	t_cmd *cmd_curr;
	t_token *tok;

	cmd_head = new_cmd();
	cmd_curr = cmd_head;
	tok = tokens;
	while (tok)
	{
		parse_args(cmd_curr, &tok);
		parse_redirs(cmd_curr, &tok);
		advance_pipe(&cmd_curr, &tok);
	}
	return (cmd_head);
}
