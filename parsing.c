/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouanan <ybouanan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:44:04 by habenydi          #+#    #+#             */
/*   Updated: 2025/04/28 04:09:15 by ybouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms.h"
#include "header/lexer_token.h"

static void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("[type=%d, value='%s']\n", tok->type, tok->value);
		tok = tok->next;
	}
}

static void	print_redirects(t_redirect *redir)
{
	while (redir)
	{
		printf("  redirect: type=%d, value=%s\n", redir->type,
			redir->value ? redir->value : "(null)");
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

void	parsing2(char *cmdl)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = lexer(cmdl);
	if (!tokens)
		return;
	printf("Tokens:\n");
	print_tokens(tokens);
	cmds = parse_tokens(tokens);
	printf("\nParsed commands:\n");
	print_cmds(cmds);
}


t_cmd	*parsing(char *cmdl)
{
	t_token	*tokens;

	tokens = lexer(cmdl);
	return (parse_tokens(tokens));
}

