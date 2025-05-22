/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/22 10:56:21 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parscmd.h"

static void	add_arg_to_cmd(t_cmd *cmd, char *value)
{
	int		argc;
	int		i;
	char	**new_args;

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

static void	handle_token(t_cmd *cmd, t_token *tok, int *redir_pending)
{
	if (*redir_pending)
	{
		if (tok->flag == 404)
		{
			if (tok->value)
				add_redirect(&cmd->redirect_list, tok->value,
					(t_token_type) * redir_pending, tok->value);
		}
		else
			add_redirect(&cmd->redirect_list, tok->value,
				(t_token_type) * redir_pending, NULL);
		*redir_pending = 0;
	}
	else
		add_arg_to_cmd(cmd, tok->value);
}

static void	handle_token_loop(t_cmd **cmd_curr, t_token **tok,
		int *redir_pending)
{
	if ((*tok)->type == TOKEN_PIPE)
	{
		(*cmd_curr)->next = new_cmd();
		*cmd_curr = (*cmd_curr)->next;
		*tok = (*tok)->next;
		*redir_pending = 0;
		return ;
	}
	if (is_redir((*tok)->type))
	{
		*redir_pending = (*tok)->type;
		*tok = (*tok)->next;
		return ;
	}
	if ((*tok)->type == TOKEN_WORD)
		handle_token(*cmd_curr, *tok, redir_pending);
	*tok = (*tok)->next;
}

static void	parse_tokens_loop(t_cmd *cmd_head, t_token *tokens)
{
	t_cmd	*cmd_curr;
	t_token	*tok;
	int		redir_pending;

	cmd_curr = cmd_head;
	tok = tokens;
	redir_pending = 0;
	while (tok)
	{
		if (tok->value[0] != '\0')
			handle_token_loop(&cmd_curr, &tok, &redir_pending);
		else
			tok = tok->next;
	}
}

t_cmd	*parse_tokens(t_token *tokens, t_env *env)
{
	t_cmd	*cmd_head;

	expansion_loop(tokens, env);
	split_tokens_by_mask(tokens);
	clear_quotes(tokens);
	cmd_head = new_cmd();
	parse_tokens_loop(cmd_head, tokens);
	return (cmd_head);
}
