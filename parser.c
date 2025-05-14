/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deepseeko <deepseeko@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 02:20:00 by ybouanan          #+#    #+#             */
/*   Updated: 2025/05/14 05:17:44 by deepseeko        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/lexer_token.h"
#include "ms.h"
#include "expand/expand.h"
#include <ctype.h>

int	fill_redir(t_cmd *cmd, t_token *tok);

void print_mask(char *mask)
{
	int i = 0;
	while (mask[i])
	{
		printf("%d", (unsigned char)mask[i]);
		if (mask[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

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
    int i = 0;
    int start = -1;
    while (token->value[i])
    {
        if (token->mask[i] & MASK_QUOTES)
        {
            start = i;
            i++;
            while (token->value[i] && !(token->mask[i] & MASK_QUOTES))
                i++;
            if (token->value[i] && (token->mask[i] & MASK_QUOTES))
            {
                int j = start;
                while (j <= i) {
                    token->mask[j] = MASK_QUOTES;
                    j++;
                }
                i++;
            }
        }
        else {
            i++;
        }
    }
}

void fix_mask_sq(t_token *token)
{
    int i = 0;
    int start = -1;
    while (token->value[i])
    {
        if (token->mask[i] & MASK_S_QUOTES)
        {
            start = i;
            i++;
            while (token->value[i] && !(token->mask[i] & MASK_S_QUOTES))
                i++;
            if (token->value[i] && (token->mask[i] & MASK_S_QUOTES))
            {
                int j = start;
                while (j <= i) {
                    token->mask[j] = MASK_S_QUOTES;
                    j++;
                }
                i++;
            }
        }
        else {
            i++;
        }
    }
}

static int is_inside_quotes(char mask) {
    return (mask & MASK_QUOTES) || (mask & MASK_S_QUOTES);
}

char **split_with_mask(t_token *token)
{
    int fully_quoted = 1;
    int len = hb_strlen(token->value);
    int i = 0;

    while (i < len) {
        if (!is_inside_quotes(token->mask[i]) && token->value[i] != ' ' &&
            !(i == 0 && token->value[i] == '"') &&
            !(i == len-1 && token->value[i] == '"')) {
            fully_quoted = 0;
            break;
        }
        i++;
    }

    if (fully_quoted) {
        char **args = (char **)ft_malloc(sizeof(char *) * 2);
        args[0] = hb_strdup(token->value);
        args[1] = NULL;
        return args;
    }

    int count = 0;
    i = 0;
    int start = 0;
    char **args;

    while (i < len) {
        while (i < len && is_space(token->value[i]) && !is_inside_quotes(token->mask[i]))
            i++;

        if (i >= len)
            break;

        start = i;
        while (i < len && (!is_space(token->value[i]) || is_inside_quotes(token->mask[i])))
            i++;

        count++;
    }

    args = (char **)ft_malloc(sizeof(char *) * (count + 1));
    i = 0;
    int idx = 0;

    while (i < len) {
        while (i < len && is_space(token->value[i]) && !is_inside_quotes(token->mask[i]))
            i++;

        if (i >= len)
            break;

        start = i;
        while (i < len && (!is_space(token->value[i]) || is_inside_quotes(token->mask[i])))
            i++;

        args[idx++] = hb_substr(token->value, start, i - start);
    }

    args[idx] = NULL;
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
	t_token *tok;

	expansion_loop(tokens, env);

	tok = tokens;
	while (tok) {
		if (tok->type == TOKEN_WORD) {
			int len = hb_strlen(tok->value);
			if (len >= 2) {
				if ((tok->value[0] == '"' && tok->value[len-1] == '"') ||
					(tok->value[0] == '\'' && tok->value[len-1] == '\'')) {
					tok->flag = 42;
				}
			}
		}

		tok = tok->next;
	}
	tok = tokens;
	while (tok) {
		if (tok->mask) {
			fix_mask_dq(tok);
			fix_mask_sq(tok);
		}
		tok = tok->next;
	}

	printf("\n\n");
	print_tokens(tokens);
	printf("\n\n");

	split_tokens_by_mask(tokens);
	cmd_head = new_cmd();
	parse_tokens_loop(cmd_head, tokens);
	return (cmd_head);
}
