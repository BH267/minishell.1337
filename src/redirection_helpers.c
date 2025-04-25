/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/04/25 17:19:15 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	handle_redir_in(t_cmd *cmd, t_token *tok)
{
	if (tok->next)
		cmd->infile = tok->next->value;
	else
		cmd->infile = NULL;
}

static void	handle_redir_out(t_cmd *cmd, t_token *tok, int append)
{
	if (tok->next)
		cmd->outfile = tok->next->value;
	else
		cmd->outfile = NULL;
	cmd->append = append;
}

int	fill_redir(t_cmd *cmd, t_token *tok)
{
	if (tok->type == TOKEN_REDIR_IN)
		handle_redir_in(cmd, tok);
	else if (tok->type == TOKEN_REDIR_OUT)
		handle_redir_out(cmd, tok, 0);
	else if (tok->type == TOKEN_APPEND)
		handle_redir_out(cmd, tok, 1);
	else if (tok->type == TOKEN_HEREDOC)
		handle_redir_in(cmd, tok);
	else
		return (0);
	return (1);
}

int	is_redir(t_token_type t)
{
	return (t == TOKEN_REDIR_IN || t == TOKEN_REDIR_OUT
		|| t == TOKEN_APPEND || t == TOKEN_HEREDOC);
}
