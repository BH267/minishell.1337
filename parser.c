/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/11 14:28:30 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/lexer_token.h"

int	fill_redir(t_cmd *cmd, t_token *tok);

static void add_arg_to_cmd(t_cmd *cmd, char *value)
{
	int argc ;
	int i ;
	char **new_args;

	argc = 0;
	i = 0;
	if (cmd->args)
		while (cmd->args[argc])
			argc++;
	new_args = (char **)ft_malloc(sizeof(char *) * (argc + 2));
	if (cmd->args)
	{
		while (cmd->args[i])
		{
			new_args[i] = cmd->args[i];
			i++;
		}
	}
	new_args[i++] = value;
	new_args[i] = NULL;
	cmd->args = new_args;
}

static void handle_token(t_cmd *cmd, t_token *tok, int *redir_pending)
{
	if (*redir_pending)
	{
		add_redirect(&cmd->redirect_list, tok->value, (t_token_type)*redir_pending);
		*redir_pending = 0;
	}
	else
		add_arg_to_cmd(cmd, tok->value);
}

static void	handle_token_loop(t_cmd **cmd_curr, t_token **tok, int *redir_pending)
{
	if ((*tok)->type == TOKEN_PIPE)
	{
		(*cmd_curr)->next = new_cmd();
		*cmd_curr = (*cmd_curr)->next;
		*tok = (*tok)->next;
		*redir_pending = 0;
		return;
	}
	if (is_redir((*tok)->type))
	{
		*redir_pending = (*tok)->type;
		*tok = (*tok)->next;
		return;
	}
	if ((*tok)->type == TOKEN_WORD)
		handle_token(*cmd_curr, *tok, redir_pending);
	*tok = (*tok)->next;
}

static void	parse_tokens_loop(t_cmd *cmd_head, t_token *tokens)
{
	t_cmd *cmd_curr;
	t_token *tok;
	int redir_pending;

	cmd_curr = cmd_head;
	tok = tokens;
	redir_pending = 0;
	while (tok)
		handle_token_loop(&cmd_curr, &tok, &redir_pending);
}

t_cmd *parse_tokens(t_token *tokens)
{
	t_cmd *cmd_head;

	cmd_head = new_cmd();

	parse_tokens_loop(cmd_head, tokens);
	return (cmd_head);
}
