/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:44:04 by habenydi          #+#    #+#             */
/*   Updated: 2025/05/18 17:15:29 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include "expand/expand.h"

void	print_tokens(t_token *tok)
{
	int i;
	int len;

	while (tok)
	{
		printf("[type=%d, value='%s', mask=", tok->type, tok->value);
		if (tok->mask)
		{
			i = 0;
			len = hb_strlen(tok->value);
			while (i < len)
			{
				printf("%d", (unsigned char)tok->mask[i]);
				if (i < len - 1)
					printf(" ");
				i++;
			}
		}
		else
			printf("(null)");
		printf("]\n");
		tok = tok->next;
	}
}

static void	print_redirects(t_redirect *redir)
{
	while (redir)
	{
		printf("  redirect: type=%d, value=", redir->type);
		if (redir->value)
			printf("%s\n", redir->value);
		else
			printf("(null)\n");
		redir = redir->next;
	}
}

static void	print_cmds(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("Command:\n");
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("  arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		print_redirects(cmd->redirect_list);
		cmd = cmd->next;
	}
}

void	parsing2(char *cmdl , t_env *env)
{
	t_token *tokens;
	t_cmd *cmds;

	if (!check_balanced_quotes(cmdl))
	{
		hb_printerr("minishell: syntax error: unclosed quote\n");
		return ;
	}
	tokens = lexer(cmdl);
	if (!tokens)
		return;
	if (!check_grammar(tokens))
	{
		hb_printerr("minishell: syntax error\n");
		return;
	}
	printf("Tokens:\n");
	print_tokens(tokens);
	cmds = parse_tokens(tokens, env);
	printf("\nParsed commands:\n");
	print_cmds(cmds);
}

t_cmd	*parsing(char *cmdl, t_env *env )
{
	t_token *tokens;

	if (!check_balanced_quotes(cmdl))
	{
		hb_printerr("minishell: syntax error: unclosed quote\n");
		return NULL;
	}
	tokens = lexer(cmdl);
	if (!check_grammar(tokens))
	{
		hb_printerr("minishell: syntax error\n");
		return NULL;
	}
	return (parse_tokens(tokens, env));
}
