/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/20 00:20:15 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand/expand.h"
#include "header/lexer_token.h"
#include "ms.h"
#include <ctype.h>

int			fill_redir(t_cmd *cmd, t_token *tok);

void	print_mask(char *mask)
{
	int	i;

	i = 0;
	while (mask[i])
	{
		printf("%d", (unsigned char)mask[i]);
		if (mask[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

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
					(t_token_type)*redir_pending , tok->value);

		}
		else
			add_redirect(&cmd->redirect_list, tok->value,
				(t_token_type)*redir_pending , NULL);
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
		handle_token_loop(&cmd_curr, &tok, &redir_pending);
}

void	add_token_ae(t_token **lst, t_data_splited *data, int index)
{
	t_token	*new;

	new = (t_token *)ft_malloc(sizeof(t_token));
	new->value = data->args[index];
	new->type = TOKEN_WORD;
	new->mask = data->mask_args[index];
	new->next = NULL;
	new->flag = 42;
	if (*lst)
	{
		new->next = (*lst)->next;
		(*lst)->next = new;
	}
	else
		*lst = new;
}

void	replace_args(t_token *tok, t_data_splited *data)
{
	int		i;
	t_token	*current;
	t_token	*next_orig;

	i = 0;
	current = tok;
	next_orig = tok->next;
	if (!data || !data->args || !data->args[0])
		return ;
	current->mask = data->mask_args[i];
	current->value = data->args[i++];
	while (data->args[i])
	{
		add_token_ae(&current, data, i);
		current = current->next;
		i++;
	}
	current->next = next_orig;
}

void	split_tokens_by_mask(t_token *tokens)
{
	t_token			*tok;
	t_data_splited	*data;

	tok = tokens;
	while (tok)
	{
		if (tok->flag == 42)
		{
			data = split_args(tok);
			replace_args(tok, data);
		}
		tok = tok->next;
	}
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}
int	has_quotes_mask_zero(t_token *tok)
{
	int	i;

	i = 0;
	if (!tok || !tok->value || !tok->mask)
		return (0);
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
			return (1);
		i++;
	}
	return (0);
}

int	count_zeromask_quotes(t_token *tok)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
			count++;
		i++;
	}
	return (count);
}

void	delete_zeromask_quotes(t_token *tok)
{
	int		quote_count;
	char	*new_value;
	int		i;
	int		k;
	int		original_length;

	quote_count = count_zeromask_quotes(tok);
	if (quote_count == 0)
		return ;
	original_length = hb_strlen(tok->value);
	new_value = (char *)ft_malloc(sizeof(char) * (original_length - quote_count
				+ 1));
	if (!new_value)
		return ;
	i = 0;
	k = 0;
	while (tok->value[i])
	{
		if (is_quote(tok->value[i]) && (tok->mask[i] == 0))
		{
			i++;
			continue ;
		}
		new_value[k] = tok->value[i];
		k++;
		i++;
	}
	new_value[k] = '\0';
	tok->value = new_value;
}

void	clear_quotes(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok)
	{
		if (has_quotes_mask_zero(tok))
		{
			delete_zeromask_quotes(tok);
		}
		tok = tok->next;
	}
}

////  test ////
// static void	print_redirects(t_redirect *redir)
// {
// 	while (redir)
// 	{
// 		printf("  redirect: type=%d, value=", redir->type);
// 		if (redir->value)
// 			printf("%s\n", redir->value);
// 		else
// 			printf("(null)\n");
// 		redir = redir->next;
// 	}
// }

// static void	print_cmds(t_cmd *cmd)
// {
// 	int	i;

// 	while (cmd)
// 	{
// 		printf("Command:\n");
// 		if (cmd->args)
// 		{
// 			i = 0;
// 			while (cmd->args[i])
// 			{
// 				printf("  arg[%d]: %s\n", i, cmd->args[i]);
// 				i++;
// 			}
// 		}
// 		print_redirects(cmd->redirect_list);
// 		cmd = cmd->next;
// 	}
// }


t_cmd	*parse_tokens(t_token *tokens, t_env *env)
{
	t_cmd	*cmd_head;

	expansion_loop(tokens, env);
	split_tokens_by_mask(tokens);
	clear_quotes(tokens);
	cmd_head = new_cmd();
	parse_tokens_loop(cmd_head, tokens);
	////print_cmds(cmd_head);
	return (cmd_head);
}

