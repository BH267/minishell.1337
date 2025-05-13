/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/12 21:30:13 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/lexer_token.h"
#include "ms.h"
#include "expand/expand.h"
#include <ctype.h>

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

int count_args_with_mask(char *mask)
{
	int		i;
	int		count;
	char	flag;

	i = 0;
	count = 0;
	flag = mask[0];
	while(mask[i])
	{
		while (mask[i] && ((mask[i] & MASK_QUOTES) || (mask[i] & MASK_S_QUOTES)) && mask[i] == flag)
			i++;
		flag = mask[i];
		count++;
		i++;
	}
	return (count);
}

void fix_mask_dq(t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(token->mask[i])
	{
		if (token->mask[i] & MASK_QUOTES)
		{
			j = i;
			while(!is_space(token->value[j]) && j >= 0)
			{
				token->mask[j] = token->mask[j] | MASK_QUOTES;
				j--;
			}
			while(!is_space(token->value[i]) && token->value[i])
			{
				token->mask[i] = token->mask[i] | MASK_QUOTES;
				i++;
			}
		}
		i++;
	}
}


void fix_mask_sq(t_token *token)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(token->mask[i])
	{
		if (token->mask[i] & MASK_S_QUOTES )
		{
			j = i;
			while(j >= 0 && !is_space(token->value[j]))
			{
				token->mask[j] = token->mask[j] | MASK_S_QUOTES;
				j--;
			}
			while(token->value[i] && !is_space(token->value[i]))
			{
				token->mask[i] = token->mask[i] | MASK_S_QUOTES;
				i++;
			}
		}
		i++;
	}
}

char **split_with_mask(t_token *token)
{
	int     count;
	char    **args;
	int     i;
	int     flag;
	int     start;
	int     index;

	index = 0;
	i = 0;
	fix_mask_dq(token);
	fix_mask_sq(token);
	count = count_args_with_mask(token->mask);
	args = (char **)ft_malloc(sizeof(char *) * (count + 1));
	while (token->value[i])
	{
		while (token->value[i] && is_space(token->value[i]))
			i++;
		if (!token->value[i])
			break;
		start = i;
		flag = token->mask[i] & (MASK_QUOTES | MASK_S_QUOTES);

		while (token->value[i])
		{
			if (is_space(token->value[i]) && !(token->mask[i] & (MASK_QUOTES | MASK_S_QUOTES)))
				break;
			if ((token->mask[i] & (MASK_QUOTES | MASK_S_QUOTES)) != flag)
				break;
			i++;
		}
		args[index++] = hb_substr(token->value, start, i - start);
	}
	args[index] = NULL;
	return args;
}

void add_token_ae(t_token **lst, char *value, t_token_type type, char *mask)
{
	t_token *new;

	new = (t_token *)ft_malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->mask = mask;
	new->next = NULL;

	if (*lst)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
	}
	else
		*lst = new;
}

void replace_args(t_token *tok, char **args)
{
	int i = 0;
	t_token_type type = tok->type;
	t_token *current = tok;
	t_token *next_orig = tok->next;

	if (!args || !args[0])
		return;
	current->value = args[i++];
	current->mask = NULL;
	while (args[i])
	{
		add_token_ae(&current, args[i], type, NULL);
		current = current->next;
		i++;
	}
	current->next = next_orig;
}

void split_tokens_by_mask(t_token *tokens)
{
	t_token *tok;
	char **args;

	tok = tokens;
	while(tok)
	{
		if (tok->flag == 42)
		{
			args = split_with_mask(tok);
			replace_args(tok,args);
		}
		tok = tok->next;
	}
}


t_cmd *parse_tokens(t_token *tokens , t_env *env)
{
	t_cmd *cmd_head;

	expansion_loop(tokens, env);
	//split_tokens_by_mask(tokens);
	cmd_head = new_cmd();
	parse_tokens_loop(cmd_head, tokens);
	return (cmd_head);
}
